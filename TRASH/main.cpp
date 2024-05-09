#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <cstring>
//#include "nw.hpp"
//#include <cuda.h>
//#include <cuda_runtime.h>
using namespace std;

int main(int argc, char*argv[]) {
    
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








    for (int i = 0; i < seq1l; i++){
        delete[] distm[i];
    }
    delete[] distm;

    return 0;

}