#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <chrono>

using namespace std;

int main()
{
    srand(time(NULL));
    int vec_size = 100000; // For timing indexing elements in vectors of different sizes, 
                           // just change this value.
    vector<int> vec(vec_size);
    for (int& i: vec) {
        i = rand() % 10;
    }
    int sum = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100; i++) {
        int index = rand() % vec_size;
        sum += vec[index] > 5 ? 1 : -1;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    cout << sum;
}