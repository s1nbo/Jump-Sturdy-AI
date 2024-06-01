#include "tt.hpp"

// zorbist hash the board
uint64_t Tt::zorbist_hash(bitboard &board) {
    uint64_t hash = 0;
    hash ^= board.blue_pawns;
    hash ^= board.red_pawns;
    hash ^= board.blue_blue_knight;
    hash ^= board.red_red_knight;
    hash ^= board.red_blue_knight;
    hash ^= board.blue_red_knight;
    return hash;
}

// store the zorbist hash and the value of the board
void Tt::store(uint64_t zorbist_hash, uint16_t best_move, bool turn) {
    if(turn) transposition_table_blue[zorbist_hash] = best_move;
    else transposition_table_red[zorbist_hash] = best_move;
}

// probe the transposition table for the zorbist hash
uint16_t Tt::probe(uint64_t zorbist_hash, bool turn){
    if (turn) return transposition_table_blue.contains(zorbist_hash) ? transposition_table_blue[zorbist_hash] : 0;
    return transposition_table_red.contains(zorbist_hash) ? transposition_table_red[zorbist_hash] : 0;
}