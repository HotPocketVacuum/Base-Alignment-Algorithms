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