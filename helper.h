#ifndef SUDOKU_HELPER_H
#define SUDOKU_HELPER_H

#include <array>
#include "board.h"
#include <fstream>
#include <iostream>


namespace sudoku {
    using namespace std;
    std::string filename = "log.txt";
    std::ofstream ostrm(filename);
//    std::ostream ostrm(std::cout.rdbuf());
    void print_neighbor(const array<array<uint8_t, NEIGHBOR>, N> &board) {
        std::for_each(board.begin(), board.end(), [](const array<uint8_t, NEIGHBOR> &one_line) {
            std::for_each(one_line.begin(), one_line.end(), [](const uint8_t &i) { ostrm << +i << "|"; });

            ostrm << "\n" << "-------------------------" <<"\n";
        });
    }

    void print_board(const array<uint8_t, N> &board) {
        ostrm << "-------------------" << "\n";
        for (auto it = board.begin(); it != board.end(); it++) {
            auto index = it - board.begin();
            if (index % 9 == 0) {
                ostrm << "|";
            }
            ostrm << +*it;

            if (index % 3 == 2) {
                ostrm << "|";
            } else {
                ostrm << ' ';
            }

            if (index % 9 == 8) {
                ostrm << "\n";
                if (index / 9 % 3 == 2) {
                    ostrm << "-------------------" << "\n";
                }
            }
        }
        ostrm<<std::endl;
    }
}
#endif //SUDOKU_HELPER_H
