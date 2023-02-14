//
// Created by forma on 2023/2/13.
//

#ifndef SUDOKU_HELPER_H
#define SUDOKU_HELPER_H

#include <array>
#include "board.h"

namespace sudoku {
    using namespace std;

    void print_neighbor(array<array<uint8_t, NEIGHBOR>, N> board) {
        std::for_each(board.begin(), board.end(), [](const array<uint8_t, NEIGHBOR> &one_line) {
            std::for_each(one_line.begin(), one_line.end(), [](const uint8_t &i) { std::cout << +i << "|"; });

            std::cout << "\n" << "-------------------------" << std::endl;
        });
    }

    void print_board(array<uint8_t, N> board) {
        for (auto it = board.begin(); it != board.end(); it++) {
            auto index = it - board.begin();
            if (index % 9 == 0) {
                std::cout << "|";
            }
            std::cout <<+*it;

            if (index % 3 == 2) {
                std::cout << "|";
            } else {
                std::cout<<' ';
            }

            if (index % 9 == 8) {
                std::cout << "\n";
                if (index / 9 %3 == 2) {
                    std::cout<<"-------------------"<< "\n";
                }
            }
        }
    }
}
#endif //SUDOKU_HELPER_H
