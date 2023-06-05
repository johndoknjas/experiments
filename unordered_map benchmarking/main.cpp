#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <chrono>

using namespace std;

int main()
{
    srand(time(NULL));
    string board = "";
    for (int i = 0; i < 42; i++) {
        board += ' ';
    }
    vector<string> different_boards;
    for (int i = 0; i < 50000; ++i) {
        int index_in_string = rand() % board.size();
        int coin_flip = rand() % 2;
        if (board[index_in_string] == ' ') {
            board[index_in_string] = coin_flip ? 'C' : 'U';
        }
        else if (board[index_in_string] == 'C') {
            board[index_in_string] = coin_flip ? 'U' : ' ';
        }
        else {
            board[index_in_string] = coin_flip ? 'C' : ' ';
        }
        different_boards.push_back(board);
    }
    std::unordered_map<std::string,int> my_map;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    for (const string& board: different_boards) {
        my_map.insert({board, rand() % 100});
    }
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    
}