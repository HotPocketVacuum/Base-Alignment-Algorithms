// Read in sequences

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
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
        cerr << "Could not open file: " << fname << "\n";
        return 1;
    }
    string seq;
    infile >> seq;
    infile.close();
    return seq;
}

// Convert characters to numerical form
string convSeq(string *seq){
    string result;
    for (char base : *seq) {
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
vector<int> getNextXY(vector<int> *prev, int *r, int *c, long long int *t){
    // Get b of y=-x+b that runs through previous start xy
    b = prev[1] + prev[0];

    // Find where y=-x+b intercepts the bounds
    int y1 = -c + b;
    int x1 = b - y1;
    int y2 = 0;
    int x2 = b;
    if ((x2 > x1) && (y2 < y1)){
        minX = x1;
        maxY = y1;
    } else if ((y2 = y1) && (x2 = x1)){
        minX = x1;
        maxY = y1;
    } else {
        minX = x2;
        maxY = y2;
    }

    // Get number of out of bound threads
    vector<int> exp = {prev[0] + t, prev[1] + t};
}



// Assume dismt is a reference to a 2d array in linear form
__global__ void fillCell(float *distm, int rows, int cols, int start, int *seq){
    int cellNum = blockIdx.x * blockDim.x + threadIdx.x;


    //

}



int main(int argc, char*argv[]) {
    
    // Handle incorrect number of arguments
    if (argc != 6){
        cerr << "Needs these arguments: <filename 1> <filename 2> <match score> <mismatch score> <gap score>" << "\n";
        return 1;
    }

    cout << "Opening Files" << "\n";

    // Open files and read contents to string
    string* seq1a = new string;
    string* seq2a = new string;
    *seq1a = getSeq(argv[1]);
    *seq2a = getSeq(argv[2]);

    // cout << "Reading strings: " << seq1 << ", " << seq2 << "\n";

    // Get lengths of strings
    int seq1l;
    int seq2l;
    seq1l = seq1a.length();
    seq2l = seq2a.length();

    // Convert strings to numerical form
    // A = 1, T = 2, C = 3, G = 4, gap = 0
    string* seq1 = new string;
    string* seq2 = new string;   
    *seq1 = convSeq(seq1a);
    *seq2 = convSeq(seq2a);
    delete seq1a;
    delete seq2a;

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




    for (int i = 0; i < seq1l; i++){
        delete[] distm[i];
    }
    delete[] distm;
    delete seq1;
    delete seq2;

    return 0;

}