#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <chrono>

using namespace std;

struct two_int {
    int row;
    int col;
};

void test_string_vs_2D_vector() {
    vector<vector<char>> vec;
    string str = "";
    char arr[42];
    for (int r = 0; r < 6; r++) {
        vector<char> row;
        for (int c = 0; c < 7; c++) {
            int remainder = rand() % 3;
            char chosen_char = ((remainder == 0) ? 'C' : (remainder == 1 ? 'U' : ' '));
            row.push_back(chosen_char);
            str += chosen_char;
            arr[c * 6 + r] = chosen_char;
        }
        vec.push_back(row);
    }
    vector<two_int> vec_indices;
    vector<two_int> str_indices;
    vector<two_int> arr_indices;
    for (int i = 0; i < 1000000; i++) {
        vec_indices.push_back({rand() % 6, rand() % 7});
        str_indices.push_back({rand() % 6, rand() % 7});
        arr_indices.push_back({rand() % 6, rand() % 7});
    }

    int vec_sum = 0;
    int str_sum = 0;
    int arr_sum = 0;

    chrono::steady_clock::time_point begin_arr = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000000; i++) {
        arr_sum += arr[arr_indices[i].col * 6 + arr_indices[i].row];
    }
    chrono::steady_clock::time_point end_arr = std::chrono::steady_clock::now();

    chrono::steady_clock::time_point begin_vec = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000000; i++) {
        vec_sum += vec[vec_indices[i].row][vec_indices[i].col];
    }
    chrono::steady_clock::time_point end_vec = std::chrono::steady_clock::now();

    chrono::steady_clock::time_point begin_str = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000000; i++) {
        str_sum += str[str_indices[i].col * 6 + str_indices[i].row];
    }
    chrono::steady_clock::time_point end_str = std::chrono::steady_clock::now();

    cout << "Time for str = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end_str - begin_str).count() << "[ns]" << std::endl;
    cout << "Time for 2D vec = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end_vec - begin_vec).count() << "[ns]" << std::endl;
    cout << "Time for arr = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end_arr - begin_arr).count() << "[ns]" << std::endl;

    cout << "str_sum: " << str_sum << " vec_sum: " << vec_sum << " arr_sum: " << arr_sum << "\n";
}

int main()
{
    srand(time(NULL));
    test_string_vs_2D_vector();
}