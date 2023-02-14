#include <iostream>
#include <array>
#include "board.h"
#include "helper.h"

namespace sudoku {
    using namespace std;
    constexpr uint8_t DUMMY_FULL = 100;
    constexpr uint8_t DUMMY_ERROR = 101;

    class Solver {
    public:
        Solver() = default;

        ~Solver() = default;

        bool set_board(BoardType board) {
            board_ = board;
//            board_[1] = 1;
//            board_[2] = 2;
            return init();
        }

        BoardType get_board() {
            return board_;
        }

        bool init() {
            available_ = const_available;
            for (size_t i = 0; i < N; i++) {
                if (board_[i] != 0)
                    for (auto n: neighbors[i]) {
                        available_[n][board_[i] - 1] = 0;
                    }
            }
            return true;
        }

        bool solve() {
            print_board(board_);
            const size_t fill_area = find_area();
            if (fill_area == DUMMY_FULL) {
                return true;
            }

            for (size_t i = 1; i <= 9; i++) {
                if (available_[fill_area][i - 1] > 0) {
                    board_[fill_area] = i;
                    decrease_available(fill_area, i);

                    if (solve()) return true;

                    board_[fill_area] = 0;
                    increase_available(fill_area, i);
                }
            }
            return false;
        };

    private:
        BoardType board_{};
        AvailableType available_ = const_available;
        DOFType dof = const_dof;

        void increase_available(size_t fill_area, ValueType value) {
            for (const auto &j: neighbors[fill_area]) {
                bool before = available_[j][value - 1] <= 0;
                available_[j][value - 1]++;
                bool after = available_[j][value - 1] > 0;
                if (before && after) {
                    dof[j]++;
                }
            }
        }

        void decrease_available(size_t fill_area, ValueType value) {
            for (const auto &j: neighbors[fill_area]) {
                bool before = available_[j][value - 1] > 0;
                available_[j][value - 1]--;
                bool after = available_[j][value - 1] <= 0;
                if (before && after) {
                    dof[j]--;
                }
            }
        }

        uint8_t find_area() {
            for (int i = 0; i < N; i++) {
                if (board_[i] == 0)
                    return i;
            }
            return DUMMY_FULL;
        }
    };

}

int main() {
    sudoku::BoardType board = {};
    auto solver = sudoku::Solver();
    solver.set_board({});
    auto end = solver.solve();
    sudoku::print_board(solver.get_board());
    std::cout << end << std::endl;
}
