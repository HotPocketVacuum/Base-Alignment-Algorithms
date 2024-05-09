#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <cstring>
#include <cuda.h>
#include <cuda_runtime.h>
using namespace std;

// Optimal Block Size (Number of threads per block, higher is better for older GPUs)
const long int GRID_SIZE = 1024; // Number of blocks on the grid (X dimension)
const int BLOCK_SIZE = 1024; // Number of threads on each block

// Get sequence from File
string getSeq(string fName){
    ifstream infile(fName);
    if (!infile){
        cerr << "Could not open file: " << fName << "\n";
    }
    string seq;
    infile >> seq;
    infile.close();
    return seq;
}

// Convert characters to numerical form
vector<int> convSeq(string seq){
    vector<int> result;
    for (char ch : seq) {
        switch (base) {
            case 'A':
                result.push_back(base - '0');
                break;
            case 'T':
                result.push_back(base - '1');
                break;
            case 'C':
                result.push_back(base - '2');
                break;
            case 'G':
                result.push_back(base - '3');
                break;
            case '-':
                result.push_back(base - '4');
                break;
            default:
                result.push_back(base - '0');
                break;
        }
    }

    return result;
}

// Find next start xy for diagonal filling
std::vector<int> getNextXY(std::vector<int> prev, int r, int c, int t){
    // r and c start from 1, they denote the literal number of rows and columns

    // Find raw expected start xy
    int px = prev[0];
    int py = prev[1];
    int rawExpX = px - t;
    int rawExpY = py + t;

    // If raw expected xy is out of bounds of the array
    if ((rawExpX < 0) || (rawExpY > r - 1)){

        // If past the corner of the array, set as -1, -1 and return
        if ((px == c - 1) && (py == r - 1)){
            std::vector<int> result = {-1, -1};

            return result;
        }

        // Snap the raw expected xy to the start of the next diagonal
        rawExpX = px + py + 1;
        rawExpY = 0;
        if (rawExpX > c - 1){
            rawExpY = rawExpX - (c - 1);
            rawExpX = c - 1;
        }

        // Get the amount of diagonal overshoot used in the previous kernel run
        int prevAllowedOS = prev[1] - rawExpY;
        if (prevAllowedOS < 0){
            prevAllowedOS = 0;
        }
        int rawYint = px + py - 1;
        if (rawYint > r - 1){
            rawYint = r - 1;
        }
        int expectedOS = t - (1 + rawYint - py);
        int actualOS = std::min(expectedOS, prevAllowedOS);

        // Add any overshoot to the raw expected xy
        int nextX = rawExpX - actualOS;
        int nextY = rawExpY + actualOS;

        std::vector<int> result = {nextX, nextY};
        return result;

    } else {
        std::vector<int> result = {rawExpX, rawExpY};
        return result;
    }
}

// Calculate the score of a cell on the distance matrix
__device__ calcDistMat(float* sparse_distm, int x, int y, vector<int>* seq1, vector<int>* seq2, int gap, int match, int mismatch){
    if ((seq1[y - 1] == 0) || (seq2[x - 1] == 0)) {
        score = maxPrevValue + gap;
    } else if (seq1[y - 1] == seq2[x - 1]){
        score = maxPrevValue + match;
    } else {
        score = maxPrevValue + mismatch;
    }
    sparse_distm[(y) * c + (x)] = score;
    return;
}


// !!!UNUSED DEVICE FUNTION!!!
// Determine and record the traceback directions for a cell in the distance matrix
__device__ calcDirectionMatrix(float* sparse_distm, float* direction_mat, int x, int y, int m){
    // Get the values of the previous 3 cells
    int t = sparse_distm[(cellY - 1) * c + (cellX)];
    int d = sparse_distm[(cellY - ) * c + (cellX - 1)];
    int l = sparse_distm[(cellY) * c + (cellX - 1)];

    // Records the traceback directions in direction matrix

    // Handle no ties
    if ((m == t) && (m != d) && (m != l)){
        direction_mat[(cellY) * c + (cellX)] = 001;
    } else if ((m == d) && (m != t) && (m != l)){
        direction_mat[(cellY) * c + (cellX)] = 010;
    } else if ((m == l) && (m != d) && (m != t)){
        direction_mat[(cellY) * c + (cellX)] = 100;

    // Handle partial ties (Tie between 2)
    } else if ((m == t) && (m == d) && (m != l)){
        direction_mat[(cellY) * c + (cellX)] = 011;
    } else if ((m == d) && (m == l) && (m != t)){
         direction_mat[(cellY) * c + (cellX)] = 110;       
    } else if ((m == l) && (m == t) && (m != d)){
         direction_mat[(cellY) * c + (cellX)] = 101;  

    // Handle full tie (Tie with 3)
    } else {
        direction_mat[(cellY) * c + (cellX)] = 111;
    }
    return;
}


// CUDA kernel, each instance of the kernel (1 kernel = 1 GPU thread)
// fills out a cell on the distance and direction matrices
__global__ void fillCell(float* sparse_distm, //float* direction_mat, 
int r, int c, vector<int> curr, vector<int>* seq1, vector<int>* seq2, int match, int mismatch, int gap){

    // Get thread ID (Start from 0, 1, 2, ... # threads - 1)
    int cellNum = blockIdx.x * blockDim.x + threadIdx.x;

    // Calculate raw expected cell index
    int expCellX = curr[0] - cellNum;
    int expCellY = curr[1] + cellNum;
    
    // If the expected cell is out of bounds
    if ((expCellX < 0) || (expCellY > r - 1)){

        // If past the bottom right corner of the array, kill
        if ((cellNum != 0) && (curr[1] >= (r + c - 2) - curr[0])){
            // KILLCODE
            return;
        }

        // Snap the raw expected xy to the start of the next diagonal
        expCellX = prev[0] + prev[1] + 1;
        expCellY = 0;
        if (expCellX > c - 1){
            expCellY = expCellX - (c - 1);
            expCellX = c - 1;
        }

        // Get the amount of diagonal overshoot used in the previous kernel run
        int rawYint = px + py - 1;
        if (rawYint > r - 1){
            rawYint = r - 1;
        }
        int expectedOS = t - (1 + rawYint - py);

        // Add any overshoot to the raw expected xy
        int cellX = rawExpX - expectedOS;
        int cellY = rawExpY + expectedOS;

        // If the overshoot goes past the allowed overshoot, kill
        if (cellY >= curr[1]){
            //  KILLCODE
            return;
        }

    } else {
        
        int cellX = rawExpX - expectedOS;
        int cellY = rawExpY + expectedOS;
    }

    // Handle first row and first column
    if ((cellX == 0) && (cellY == 0)){
        sparse_distm[(cellY) * c + (cellX)] = 0;
        direction_mat[(cellY) * c + (cellX)] = 0;
        return;
    } else if (cellX == 0){
        sparse_distm[(cellY) * c + (cellX)] = gap;
        direction_mat[(cellY) * c + (cellX)] = 0;
        return;
    } else if (cellY == 0){
        sparse_distm[(cellY) * c + (cellX)] = gap;
        direction_mat[(cellY) * c + (cellX)] = 0;
        return;
    }

    // Calculate max previous value
    int maxPrevValue = max(sparse_distm[(cellY - 1) * c + 
    (cellX)], sparse_distm[(cellY) * c + 
    (cellX - 1)], sparse_distm[(cellY - 1) * c + (cellX - 1)]);

    // Calculate new value in distance matrix
    calcDistMat(sparse_mat, cellX, cellY, seq1, seq2, maxPrevValue, gap, match, mismatch);

    // !!! UNUSED !!!
    // Calculate direction matrix
    // 000, 1st digit = left, 2nd digit = diag, 3rd digit = top
    // calcDirectionMatrix(sparse_distm, direction_mat, cellX, cellY, maxPrevValue);
    

}

int main2(int argc, char*argv[]) {
    
    // Handle incorrect number of arguments
    if (argc != 6){
        cout << "Needs these arguments: <filename 1> <filename 2> <match score> <mismatch score> <gap score>" << "\n";
        return 0;
    }

    cout << "Opening Files" << "\n";

    // Open files and read contents to string
    string seq1a;
    string seq2a;
    seq1a = getSeq(argv[1]);
    seq2a = getSeq(argv[2]);

    // cout << "Reading strings: " << seq1 << ", " << seq2 << "\n";

    // Get lengths of strings
    int seq1l;
    int seq2l;
    seq1l = seq1a.size();
    seq2l = seq2a.size();

    // Convert strings to numerical form
    // A = 1, T = 2, C = 3, G = 4, gap = 0
    vector<int> seq1;
    vector<int> seq2;   
    seq1 = convSeq(seq1a);
    seq2 = convSeq(seq2a);

    // cout << "Getting lengths: " << seq1l << ", " << seq2l << "\n";

    // Create distance matrix
    int** distm = new int*[seq1l + 1];

    for (int i = 0; i < seq1l + 1; i++){
        distm[i] = new int[seq2l + 1];
    }

    cout << "Creating matrix: " << "\n";

    // Get gap score
    int gap;
    gap = stoi(argv[5]);

    cout << "Getting gap score: " << gap << "\n";
    
    // Initialize first row and columns with gap scores
    for (int i = 0; i < seq1l + 1; i++){
        distm[i][0] = gap;
    }

    for (int i = 0; i < seq2l + 1; i++){
        distm[0][i] = gap;
    }

    // Initialize top-left cell as zero
    distm[0][0] = 0;

    // Sanity check
    cout << distm[0][0] << "\n";
    cout << distm[1][0] << "\n";
    cout << distm[0][1] << "\n";
    cout << "rows: " << seq1l << "\n";
    cout << "columns: " << seq2l << "\n";

    // start next xy at 0,0
    // Allocate memory for 

    // for loop until
    // set current xy = next xy
    // calculate next xy


    // Get the lengths of the past 2 diagonals
    // Create sparse matrix that only copies these 2 prior diagonals
    // Allocate memory for a sparse array
    // Allocate memory for the sparse direction array
    // run kernel
    // Copy sparse matrix back to host and add computed cells to the main array





    // In the traceback, for each cell on a path
    // Reverse its score calculation via comparing seq1[xy] <> seq2[xy]
    // Get the prior 3 cells
    // Check with cells are a match,
        // If there is just one match, continue
        // If there is more than one match, 
            // recursively spawn 1 more thread for the topmost direction (can be top or diag) 
            // with current thread's path memory + (cell xy pointed to by direction)
            // append the cell xy of the leftmost direction (can be left or diag) to current thread's path
        // If all match
            // recursively spawn 2 more threads for the topmost directions with current thread's path memory
            // with current thread's path memory + (cell xy pointed to by direction)
            // append the cell xy of the leftmost direction to current thread's path
    // Synchronize threads so they wait before finishing
    // Then when they are all finished, pool their paths into an array of array of vectors

    // Convert to alignments and write to file


    for (int i = 0; i < seq1l; i++){
        delete[] distm[i];
    }
    delete[] distm;

    return 0;

}