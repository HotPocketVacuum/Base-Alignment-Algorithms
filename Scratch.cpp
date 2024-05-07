class distm{
    private:
        size_t rowNum;
        size_t colNum;

        // 2d array
        vector<vector<int>> data_;

        // Vector of mutexes
        vector<mutex> mutex_;

    public:
    // Constructor
        distm(size_t rows, size_t cols){

        }

};

class Cell{

    private:

        // To represent horizontal, vertically, and diagonally previous cell values
        int hv;
        int vv;
        int dv;

        // To represent match, mismatch, and gap scores
        int match;
        int mismatch;
        int gap;

    public:

        // To represent this cell instance's row position, column position, and value
        int rpos;
        int cpos;
        int cval;

        // Constructor
        Cell(int y, int x, int ma, int mi, int g, int h, int v, int d){
            setRPos(y);
            setCPos(x);
            setMatch(ma);
            setMismatch(mi);
            setGap(g);
            setPreRowVal(v);
            setPreColVal(h);
            setPreDiagVal(d);
        }

        // Set functions
        void setRPos(int a){
            rpos = a;
        }

        void setCPos(int a){
            cpos = a;
        }

        void setCVal(int a){ // CHECK IF CVAL IS NEEDED IN CONSTRUCTOR
            cval = a;
        }

        void setMatch(int a){
            match = a;
        }

        void setMismatch(int a){
            mismatch = a;
        }

        void setGap(int a){
            gap = a;
        }
        
        void setPreRowVal(int a){
            vv = a;
        }

        void setPreColVal(int a){
            hv = a;
        }

        void setPreDiagVal(int a){
            dv = a;
        }
       
       // Get functions
        int getRowPos(){
            return rpos;
        }
        
        int getColPos(){
            return cpos;
        }

        int getCellVal(){
            return cval;
        }

        // Progress Function:
        // Check if the prior horizontal, vertical, and diagnonal values are filled
        void progress(){

        }

        // Write to Array function:
        void write(){

        }

        // Create new instance in the next column
        void createNextColCell(){

        }

        // Create new instance in the next row
        void createNextRowCell(){

        }

        // Create new instance in the next diagonal (CALL RUN FUNCTION - SLOWER BUT IS MORE STABLE)
        void createNextDiagCell(){

        }

};

class Path{

    public:

};

// Determine the # of blocks from the max threads per block and needed threads
// long long neededThreads = ceil(static_cast<double>(maxThreadCalc(seq1l, seq2l, THREAD_MAX_PER_MS)));
// int numBlocks = static_cast<int>(ceil(static_cast<double>(neededThreads / BLOCK_SIZE)));
// long long neededThreads = ceil(static_cast<double>(seq1l * seq2l));
// int numBlocks = static_cast<int>(ceil(static_cast<double>(neededThreads / BLOCK_SIZE)));

long long calcIncDiagSum(int n, int m){

    int fullSegments =  n / m;
    int remainder = n % m;

    long long sum = (fullSegments * ceil(1 / m));

    for (int n = fullSegments * m + 1; n <= y; ++n){
        sum += ceil(static_cast<double>(n) / m)
    }

    return sum;
}

long long maxThreadCalc(int s1l, int s2l, int maxThreads){

    if (s1l >= s2l){
        x = s1l;
        y = s2l;
    } else {
        y = s1l;
        x = s2l;
    }

    // Calculate # of threads for consecutive incrementing-length diagonals on either side of the matrix
    incDiagThreads = 2 * calcIncDiagSum(x - y - 1, maxThreads);

    // Calculate # of threads for the middle constant-length diagonals
    staticDiagThreads = (x - y + 1) * y;

    return staticDiagThreads;
}


if (phase == 0){

    // Get Y value of current cell
    int cellR = threadIdx.x + (blockWidth * (numBlocks - 1) - ((numBlock - (blockNum + 1)) * blockWidth));

    // Get X value of current cell
    int cellC = threadIdx.y + (blockWidth * (numBlocks - 1) - (blockNum * blockWidth));
    
} else if (phase == 1){

    if (rows > cols){
        // Means rows is minsql
        // Get Y value of current cell
        int cellR = threadIdx.x + (blockWidth * (numBlocks - 1) - ((numBlock - (blockNum + 1)) * blockWidth)) + blockWidth * (diag - floor(cols / blockWidth));

        // Get X value of current cell
        int cellC = threadIdx.y + (blockWidth * (numBlocks - 1) - (blockNum * blockWidth));

    } else if (rows < cols){
        // Means cols is minsql
        // Get Y value of current cell
        int cellR = threadIdx.x + (blockWidth * (numBlocks - 1) - ((numBlock - (blockNum + 1)) * blockWidth));

        // Get X value of current cell
        int cellC = threadIdx.y + (blockWidth * (numBlocks - 1) - (blockNum * blockWidth)) + blockWidth * (diag - floor(rows / blockwidth));

    } else if (phase == 2){

        // Get Y value of current cell
        int cellR = threadIdx.x + (blockWidth * (numBlocks - 1) - ((numBlock - (blockNum + 1)) * blockWidth));

        // Get X value of current cell
        int cellC = threadIdx.y + (blockWidth * (numBlocks - 1) - (blockNum * blockWidth));

    }

} else {
    
    // Get Y value of current cell
    int cellY = ;

    // Get X value of current cell
    int cellX = ;
    
}


// Functions diagToCartesianX and Y
// Takes in a pointer to array of size x*y, 
// And the number of the diagonal perpendicular to 0,0
// And the number of the cell on the diagonal
// Then returns that cell's cartesian coordinates
__device__ int diagToCartX(x, y, d, c){

    

}}

__device__ int diagToCartY(){

}

// GPU Kernel function to fill distance matrix
global__ void fillBlock(float *distm, int rows, int cols, int phase, int minSql, int maxSql, int diag, int numBlocks, float *result){
    // Assign each thread to a cell
    int tx = threadIdx.x;
    int ty = threadIdx.y * 
    int inBlockIndex = tx + ty * blockDim.x;

    // Assign min and max for sequences

    int min;
    int max;
    
    min = minSql;
    max = maxSql;

    // Convert block ID to block #
    int blockNum = (gridDim.x * blockIdx.y) + blockIdx.x;
    int blockWidth = sqrt(blockSize);

    


    // If block ID is 0, put the corner cell at the corresponding cell on the diagonal

    // If the cell is out of bounds of the matrix, do nothing and return;

    // If the cell is is the first row only or first column only and NOT in 0,0 , add the gap value and return;

    // If the cell is at 0,0 , add 0 and return

    // Else
        // Empty while loop if distm[previous diagonal] or distm[previous horizontal] or distm[previous vertical] is null
            // __Call threadfence_system();
        // Complete computation
}

// GPU Kernel function to fill distance matrix
global__ void fillBlock(float *distm, float *result){
    // Assign each thread to a cell
    int tx = threadIdx.x;
    int ty = threadIdx.y * 
    int inBlockIndex = tx + ty * blockDim.x;

    // Assign min and max for sequences

    int min;
    int max;
    
    min = minSql;
    max = maxSql;

    // Convert block ID to block #
    int blockNum = (gridDim.x * blockIdx.y) + blockIdx.x;
    int blockWidth = sqrt(blockSize);

    


    // If block ID is 0, put the corner cell at the corresponding cell on the diagonal

    // If the cell is out of bounds of the matrix, do nothing and return;

    // If the cell is is the first row only or first column only and NOT in 0,0 , add the gap value and return;

    // If the cell is at 0,0 , add 0 and return

    // Else
        // Empty while loop if distm[previous diagonal] or distm[previous horizontal] or distm[previous vertical] is null
            // __Call threadfence_system();
        // Complete computation
}

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
    int numBlocks;
    int phase;

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
            phase = 0;
        } else if ((i >= minSeql) && (i <= maxSeql)){
            numBlocks == ceil(minSeql / sqrt(BLOCK_SIZE));
            phase = 1;
        } else {
            numBlocks == numDiags - i;
            phase = 2;
        }

        // Synchronize so that next threads wait
        cudaDeviceSynchronize();

        // Rows and Cols arg for kernels should be seq1l + 1 or seq2l + 2 for example

    }