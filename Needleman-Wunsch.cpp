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
const int BLOCK_SIZE = 1024;
const int THREAD_MAX_PER_MS = 8000;

// GPU Kernel function to fill distance matrix
global__ void fillBlock(float *distm, int rows, int cols, int minSql, int maxSql, int diag, int numBlocks, float *result){
    // Assign each thread to a cell
    int tx = threadIdx.x;
    int ty = threadIdx.y * 
    int inBlockIndex = tx + ty * blockDim.x;

    // Assign min and max for sequences

    int min;
    int max;
    
    min = minSeql;
    max = maxSeql;


    if (i < min){

        // Convert block ID to block #
        int blockNum = (gridDim.x * blockIdx.y) + blockIdx.x;

        // Get Y value of current cell
        int zeroCellY = threadIdx.x + (sqrt(blockSize) * (numBlocks - 1) - ((numBlock - (blockNum + 1)) * blockSize));

        // Get X value of current cell
        int zeroCellX = threadIdx.y + (sqrt(blockSize) * (numBlocks - 1) - (blockNum * blockSize));























        sqrt(blockSize * blockIDx.x)
        
    } else if ((i >= min) && (i <= max)){
        
    } else {
        
    }


    // Find the x and y from the block ID
        // When nblocks = diag
        // When nblocks > diag
        // When nblocks 


    (sqrt(blockSize) * (diag + 1)) - (sqrt(blockSize) * (blockIdx.y))

    // If block ID is 0, put the corner cell at the corresponding cell on the diagonal

    // If the cell is out of bounds of the matrix, do nothing and return;

    // If the cell is is the first row only or first column only and NOT in 0,0 , add the gap value and return;

    // If the cell is at 0,0 , add 0 and return

    // Else
        // Empty while loop if distm[previous diagonal] or distm[previous horizontal] or distm[previous vertical] is null
            // __Call threadfence_system();
        // Complete computation
}












int main(int argc, char*argv[]) {
    
    // Handle incorrect number of arguments
    if (argc != 6){
        cerr << "Needs these arguments: <filename 1> <filename 2> <match score> <mismatch score> <gap score>" << "\n";
        return 1;
    }

    cout << "Opening Files" << "\n";

    // Open files
    ifstream infile1(argv[1]);
    ifstream infile2(argv[2]);

    if (!infile1 or !infile2){
        cerr << "Could not open files" << "\n";
        return 1;
    }

    // Read file contents to string
    string seq1;
    string seq2;
    infile1 >> seq1;
    infile2 >> seq2;

    // Close files
    infile1.close();
    infile2.close();

    cout << "Reading strings: " << seq1 << ", " << seq2 << "\n";

    // Get lengths of strings
    int seq1l;
    int seq2l;
    seq1l = seq1.length();
    seq2l = seq2.length();

    cout << "Getting lengths: " << seq1l << ", " << seq2l << "\n";

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

    // Allocate memory on GPU for matrix (matrices on GPU are linear in structure)
    // Allocate memory on GPU for result matrix
    // Use float for GPU compatability/optimization
    float *g_res;
    float *g_mat;
    cudaMalloc(&g_mat, (seq1l + 1) * (seq2l + 1) * sizeof(float));
    cudaMalloc(&g_res, (seq1l + 1) * (seq2l + 1) * sizeof(float));

    // Copy matrix to GPU
    cudaMemcpy(g_mat, distm, seq1l * seq1l * sizeof(float), cudaMemcpyHostToDevice);

    // Sequentially call diagonals of blocks
        // Calculate the number of blocks for the current diagonal of blocks

        // For each diagonal, call a kernel function to process the diagonal in blocks

        // Synchronize globally between each diagonal block call

        // For loop within for loop to handle max number of blocks processing part of a diagonal


    int numDiags = ceil((seq1l + seq2l - 1) / sqrt(BLOCK_SIZE));
    int minSeql;
    int maxSeql;

    if (seq1l >= seq2l){
        minSeql = seq2l;
    } else {
        minSeql = seq1l
    }

    if (seq1l >= seq2l){
        maxSeql = seq1l;
    } else {
        maxSeql = seq2l
    }

    for (i = 0; i < numDiags; i++){
        // Calculate number of blocks for each diagonal
        if (i < minSeql){
            numBlocks = i + 1;
        } else if ((i >= minSeql) && (i <= maxSeql)){
            numBlocks == ceil(minSeql / sqrt(BLOCK_SIZE));
        } else {
            numBlocks == numDiags - i;
        }

        // Synchronize so that next threads wait
        cudaDeviceSynchronize();

    }
























    for (int i = 0; i < seq1l; i++){
        delete[] distm[i];
    }
    delete[] distm;

    return 0;

}