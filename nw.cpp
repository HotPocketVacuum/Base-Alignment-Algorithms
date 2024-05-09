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
string convSeq(string seq){
    string result;
    for (char base : seq) {
        switch (base) {
            case 'A':
                result += '1';
                break;
            case 'T':
                result += '2';
                break;
            case 'C':
                result += '3';
                break;
            case 'G':
                result += '4';
                break;
            case '-':
                result += '0';
                break;
            case ' ':
                result += '0';
                break;
            default:
            // To handle unrecognized characters
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
        int NextX = rawExpX - actualOS;
        int NextY = rawExpY + actualOS;

        std::vector<int> result = {NextX, NextY};

        return result;

    } else {
        
        std::vector<int> result = {rawExpX, rawExpY};

        return result;

    }

}


// Assume dismt is a reference to a 2d array in linear form
__global__ void fillCell(float *distm, int rows, int cols, int start, int next, int *seq){

    // Get thread ID (Start from 0, 1, 2, ... # threads - 1)
    int cellNum = blockIdx.x * blockDim.x + threadIdx.x;




    // If overshot and has >= to previous start's y, kill
    // If out of bounds, kill

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
    string seq1;
    string seq2;   
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

    // for loop until
    // set current xy = next xy
    // calculate next xy
    // run kernel





    for (int i = 0; i < seq1l; i++){
        delete[] distm[i];
    }
    delete[] distm;

    return 0;

}