#include <iostream>
#include <array>
#include "board.h"
#include "helper.h"

namespace sudoku {
    using namespace std;
    constexpr uint8_t DUMMY_FULL = 100;
    constexpr uint8_t DUMMY_ERROR = 101;

    bool Solver::set_board(BoardType board) {
        board_ = board;
        return init();
    }

    BoardType Solver::get_board() {
        return board_;
    }

    bool Solver::solve() {
        print_board(board_);
        const size_t fill_area = find_area();
        if (fill_area == DUMMY_FULL) {
            return true;
        }

//        auto tmp_dof = 0;
        for (size_t i = 1; i <= 9; i++) {
            if (available_[fill_area][i - 1] > 0) {
                auto tmp_dof = dof[fill_area];
                board_[fill_area] = i;
                decrease_available(fill_area, i);
                dof[fill_area] = 0;

                if (solve()) return true;

                board_[fill_area] = 0;
                increase_available(fill_area, i);
                dof[fill_area] = tmp_dof;
            }
        }
        return false;
    };


    bool Solver::init() {
        available_ = const_available;
        dof = const_dof;
        for (size_t i = 0; i < N; i++) {
            if (board_[i] != 0) {
                decrease_available(i, board_[i]);
                dof[i] = 0;
            }
//                for (auto neighbor: neighbors[i]) {
//                    decrease_available(neighbor,board_[i]);
//                    available_[neighbor][board_[i] - 1] = 0;
//                }
        }
        return true;
    }

    void Solver::increase_available(size_t fill_area, ValueType value) {
        for (const auto &j: neighbors[fill_area]) {
            bool before = available_[j][value - 1] <= 0;
            available_[j][value - 1]++;
            bool after = available_[j][value - 1] > 0;
            if (before && after) {
                dof[j]++;
            }
        }
    }

    void Solver::decrease_available(size_t fill_area, ValueType value) {
        for (const auto &neighbor: neighbors[fill_area]) {
            bool before = available_[neighbor][value - 1] > 0;
            available_[neighbor][value - 1]--;
            bool after = available_[neighbor][value - 1] <= 0;
            if (before && after) {
                dof[neighbor]--;
            }
        }
    }

    size_t Solver::find_area() {
//        auto it = std::min_element(dof.begin(), dof.end(),
//                                   [](auto a, auto b) {
//            return (a < b && a > 0) || b <= 0;
//        });
//        auto fill_area = it - dof.begin();
//        if (board_[fill_area] != 0) {
//            return DUMMY_FULL;
//        }
//        return fill_area;
        for (int i = 0; i < N; i++) {
            if (board_[i] == 0)
                return i;
        }
        return DUMMY_FULL;
    }
}
