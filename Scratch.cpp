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