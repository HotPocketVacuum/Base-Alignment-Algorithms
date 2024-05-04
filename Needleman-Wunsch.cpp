// Read in sequences

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
    int** distm = new int*[seq1l];

    for (int i = 0; i < seq1l; i++){
        distm[i] = new int[seq2l];
    }

    cout << "Creating matrix: " << "\n";

    // Get gap score
    int gap;
    gap = stoi(argv[5]);

    cout << "Getting gap score: " << gap << "\n";
    
    // Initialize first row and columns with gap scores
    for (int i = 0; i < seq1l; i++){
        distm[i][0] = gap;
    }

    for (int i = 0; i < seq2l; i++){
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

    // Fill the matrix

    for (int i = 0; i < seq1l; i++){
        delete[] distm[i];
    }
    delete[] distm;

    return 0;

}