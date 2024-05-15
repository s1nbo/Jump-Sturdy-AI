#ifndef AI_HPP
#define AI_HPP

#include "moves.hpp"
#include "board.hpp"

#include <cstdint>
#include <vector>
#include <iostream>

class Ai{
public:
    Ai() = default;
    
    int analyzed_nodes = 0;
    
    int rate_board(bitboard &board);
    std::vector<uint16_t> getBits(uint64_t board);

    uint16_t negamax_handler(bitboard &board, int search_depth);
    int negamax(uint16_t move, int depth, int alpha, int beta, bitboard &board, Moves m);
    uint16_t minimax_handler(bitboard &board, int search_depth);
    int minimax(uint16_t move, int depth, bitboard &board, Moves m);
    uint16_t alphabeta_handler(bitboard &board, int search_depth);
    int alphabeta(uint16_t move, int depth, int alpha, int beta, bitboard &board, Moves m);

};

#endif
