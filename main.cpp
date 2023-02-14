#include <iostream>
#include <array>
#include "board.h"
#include "helper.h"

namespace sudoku {
    using namespace std;

//    static array<array<uint8_t, NEIGHBOR>, N> neighbors;

    void solver(Board board) {
    };
}

int main() {
    sudoku::Board board = {};
//    sudoku::generate_neighbors();
    sudoku::print_neighbor(sudoku::neighbors);
    sudoku::print_board(sudoku::Board {});
//    sudoku::solver(board);
}
