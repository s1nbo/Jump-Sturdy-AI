#ifndef AI_HPP
#define AI_HPP

#include "tt.hpp"
#include "moves.hpp"
#include "board.hpp"

#include <cstdint>
#include <vector>
#include <iostream>
#include <limits.h>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <utility>

class Ai{
public:
    Ai() = default;
    
    int analyzed_nodes = 0;
    // zoorist hash zorbist_table
    uint64_t zorbist_table[64][2];
    
    int rate_board(bitboard &board);
    std::vector<uint16_t> getBits(uint64_t board);

    uint16_t negamax_handler(bitboard &board, int search_depth);
    int negamax(int depth, int alpha, int beta, bitboard &board, Moves m);

    uint16_t alphabeta_handler(bitboard &board, int search_depth, Tt &table);
    int alphabetaMax(int depth, int alpha, int beta, bitboard &board, Moves &m, Tt &table);
    int alphabetaMin(int depth, int alpha, int beta, bitboard &board, Moves &m, Tt &table);

    uint16_t minimax_handler(bitboard &board, int search_depth);
    int maxi(int depth, bitboard &board, Moves m);
    int mini(int depth, bitboard &board, Moves m);

   
};

#endif
