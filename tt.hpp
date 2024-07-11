#ifndef TT_HPP
#define TT_HPP


#include "board.hpp"


#include <unordered_map>

// Transposition table class


class Tt{
public:
    Tt() = default;
    std::unordered_map<uint64_t, uint16_t> transposition_table_blue;
    std::unordered_map<uint64_t, uint16_t> transposition_table_red;

    uint64_t zorbist_hash(bitboard &board);

    void store(uint64_t zorbist_hash, uint16_t value, bool turn);
    uint16_t probe(uint64_t zorbist_hash, bool turn);
};

#endif
