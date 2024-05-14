#ifndef AI_HPP
#define AI_HPP

#include "moves.hpp"
#include "board.hpp"

#include <cstdint>
#include <vector>
#include <iostream>

class Ai{
public:
    Ai();
    std::uint16_t best_move = 0;
    uint16_t choose_move(bitboard &board);
    int rate_board(bitboard &board);
    std::vector<uint16_t> getBits(uint64_t board);
    int max(int depth, int alpha, int beta, bitboard &board, Moves &m);
    int min(int depth, int alpha, int beta, bitboard &board, Moves &m);
};

#endif