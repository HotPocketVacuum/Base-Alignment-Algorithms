// tests/helper_tests.cpp


#include <iostream>
#include <vector>
#include <cassert>
#include "nw.cpp"

int main(){

    using namespace std::this_thread;
    using namespace std::chrono_literals;
    using std::chrono::system_clock;

    assert(getNextXY(std::vector<int>{4, 1}, 6, 9, 4) == (std::vector<int>{0, 5}));
    std::cout << "1/4 Passed!" << "\n";
    assert(getNextXY(std::vector<int>{2, 2}, 6, 9, 5) == (std::vector<int>{3, 2}));
    std::cout << "2/4 Passed!" << "\n";
    assert(getNextXY(std::vector<int>{5, 4}, 6, 9, 3) == (std::vector<int>{7, 3}));
    std::cout << "3/4 Passed!" << "\n";
    assert(getNextXY(std::vector<int>{5, 4}, 6, 9, 6) == (std::vector<int>{6, 4}));
    std::cout << "4/4 Passed!" << "\n";

    return 0;

}

