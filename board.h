#include <iostream>
#include <array>
#include <algorithm>

#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

//https://blog.csdn.net/Solstice/article/details/2096209

//0  1  2  3  4  5  6  7  8
//9  10 11 12 13 14 15 16 17
//18 19 20 21 22 23 24 25 26
//27 28 29 30 31 32 33 34 35
//36 37 38 39 40 41 42 43 44
//45 46 47 48 49 50 51 52 53
//54 55 56 57 58 59 60 61 62
//63 64 65 66 67 68 69 70 71
//72 73 74 75 76 77 78 79 80
namespace sudoku {

    using namespace std;
    static constexpr uint8_t N = 81;
    static constexpr uint8_t NEIGHBOR = 20;

    using ValueType = uint8_t;
    using BoardType = array<ValueType, N>;
    using NeighborLineType = array<size_t, NEIGHBOR>;
    using NeighborType = array<NeighborLineType, N>;
    using AvailableType = array<array<int8_t, 9>, N>;
    using DOFType = std::array<int8_t, N>; //Degrees of freedom


    constexpr bool is_in_neighbour(const NeighborLineType &neighbor, const ValueType &j) {
        return std::find(neighbor.begin(), neighbor.end(), j) != neighbor.end();
    }

    constexpr auto generate_neighbors() {
        NeighborType neighbors{};
        for (auto i = 0; i < N; i++) {
            size_t n = 0;
            for (auto j = 0; j < N; j++) {
                if ((i / 9 == j / 9 or (i % 9 == j % 9) or ((i / 9 / 3 == j / 9 / 3) and (i % 9 / 3 == j % 9 / 3))) and
                    (!is_in_neighbour(neighbors[i], j)) and
                    (i != j)) {
                    neighbors[i][n++] = j;
                }
            }
        }
        return neighbors;
    }

    constexpr auto generate_available() {
        AvailableType available{};
        for (auto &i: available) {
            for (auto &j: i) {
                j = 1;
            }
        }
        return available;
    }

    constexpr auto generate_dof() {
        DOFType dof{};
        std::fill(dof.begin(), dof.end(), 9);
        return dof;
    }

    static constexpr const NeighborType neighbors = generate_neighbors();
    static constexpr const AvailableType const_available = generate_available();
    static constexpr auto const_dof = generate_dof();

    class Solver {
    public:
        Solver() = default;
        ~Solver() = default;
        bool set_board(BoardType board);
        BoardType get_board();
        bool solve();
    private:
        BoardType board_{};
        AvailableType available_ = const_available;
        DOFType dof = const_dof;
        bool init();
        void increase_available(size_t fill_area, ValueType value);
        void decrease_available(size_t fill_area, ValueType value);
        size_t find_area();
    };
}

#endif //SUDOKU_BOARD_H
