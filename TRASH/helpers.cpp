#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <string>
#include <cstring>
#include "helpers.hpp"
//#include <cuda.h>
//#include <cuda_runtime.h>
using namespace std;

// Find next start xy for diagonal filling
vector<int> getNextXY(vector<int> prev, int r, int c, int t){
    // r and c start from 1, they denote the literal number of rows and columns

    // Find raw expected start xy
    int px = prev[0];
    int py = prev[1];
    int rawExpX = px - t;
    int rawExpY = py + t;

    // If raw expected xy is out of bounds of the array
    if ((rawExpX < 0) || (rawExpY >= r)){

        // Snap the raw expected xy to the start of the next diagonal
        rawExpX = px + py + 1;
        rawExpY = 0;
        if (rawExpX > c - 1){
            rawExpY = rawExpX - c;
            rawExpX = c;
        }

        // Get the amount of diagonal overshoot used in the previous kernel run
        int prevAllowedOS = prev[1] - rawExpY;
        int rawYint = px + py;
        if (rawYint > r - 1){
            rawYint = r;
        }
        int expectedOS = t - (rawYint - py);
        int actualOS = min(expectedOS, prevAllowedOS);

        // Add any overshoot to the raw expected xy
        int NextX = rawExpX - actualOS;
        int NextY = rawExpY + actualOS;

        vector<int> result = {NextX, NextY};

        return result;

    } else {
        
        vector<int> result = {px - t, px + t};

        return result;

    }

}
