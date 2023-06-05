
#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <random>
#include <chrono>

using namespace std;

void test_indexing()
{
    // vec_heap is actually usually faster for indexing, as long as
    // a copy of made of it and then that is used.
    
    // If the other vec_heap_counter +=... line is used later in this function,
    // then vec_heap is slower (likely because dereferencing on every
    // loop is expensive).

    // Not sure why vec_heap is usually faster (after using the copy) than vec_stack. Both vectors'
    // underlying arrays are stored on the heap after all.
    
    int size_of_vectors = 1000000;
    int range_of_values = 10000;
    int indexing_sample_size = 100000;
    
    vector<int>* vec_heap = new vector<int>;
    vector<int> vec_stack;
    
    for (int i = 0; i < size_of_vectors; ++i) {
        vec_heap->push_back(rand() % range_of_values);
        vec_stack.push_back(rand() % range_of_values);
    }
    
    int vec_heap_counter = 0;
    int vec_stack_counter = 0;
    
    vector<int> vec_heap_indices_to_index;
    vector<int> vec_stack_indices_to_index;
    
    for (int i = 0; i < indexing_sample_size; ++i) {
        vec_heap_indices_to_index.push_back(rand() % size_of_vectors);
        vec_stack_indices_to_index.push_back(rand() % size_of_vectors);
    }
    
    vector<int> copy_of_vec_heap = *vec_heap;
    
    std::chrono::steady_clock::time_point begin_heap = std::chrono::steady_clock::now();
    
    for (int i = 0; i < indexing_sample_size; ++i) {
        // vec_heap_counter += (*vec_heap)[vec_heap_indices_to_index[i]];
        vec_heap_counter += copy_of_vec_heap[vec_heap_indices_to_index[i]];
    }
    
    std::chrono::steady_clock::time_point end_heap = std::chrono::steady_clock::now();
    
    std::chrono::steady_clock::time_point begin_stack = std::chrono::steady_clock::now();
    
    for (int i = 0; i < indexing_sample_size; ++i) {
        vec_stack_counter += vec_stack[vec_stack_indices_to_index[i]];
    }
    
    std::chrono::steady_clock::time_point end_stack = std::chrono::steady_clock::now();
    
    cout << "vector on heap total time for indexing: " << "Time difference = ";
    cout << std::chrono::duration_cast<std::chrono::microseconds>(end_heap - begin_heap).count() << "[µs]" << std::endl;
    
    cout << "vector on stack total time for indexing: " << "Time difference = ";
    cout << std::chrono::duration_cast<std::chrono::microseconds>(end_stack - begin_stack).count() << "[µs]" << std::endl;
    
    cout << (vec_heap_counter > vec_stack_counter ? "\n" : "\n\n");
}

void test_references(string& parameter) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    string& s_ref = parameter;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]" << std::endl;
    
    begin = std::chrono::steady_clock::now();
    string s = parameter;
    end = std::chrono::steady_clock::now();
    
    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]" << std::endl;
    
    s_ref[5] = '2';
}

int main() {
    srand(time(NULL));

    // The reference test here tests assigning a huge string parameter to a string& and string.
    // The assignment to string& is far faster, since it's just assigning a reference, not 100 million characters.
    
    string s(100000000, '1');
    cout << s[5] << "\n";
    test_references(s);
    cout << s[5] << "\n";
    
    test_indexing();
}