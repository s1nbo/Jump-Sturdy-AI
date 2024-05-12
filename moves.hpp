

#ifndef MOVES_HPP
#define MOVES_HPP

#include "board.hpp"

#include <vector>
#include <cstdint>
#include <array>

class Moves {
public:
    Moves();

    bool gameOver(bitboard &board, std::vector<uint16_t> moves);

    std::vector<uint16_t> generateMoves(bitboard &board);

    std::vector<uint16_t> pawnMovesDiagonal(uint64_t start, uint64_t valid, bool turn);
    std::vector<uint16_t> pawnMoves(uint64_t start, uint64_t valid, bool turn);
    std::vector<uint16_t> knightMoves(uint64_t start, uint64_t blocked, bool turn);

    bitboard updateBoard(bitboard board, uint16_t move);

    
    // fill from bottom left to top right
    const std::array<uint64_t, 64> redKnightTable = {
    };
    const std::array<uint64_t, 64> blueKnightTable = {
    };
    const std::array<uint64_t, 64> redPawnTable = {
    };
    const std::array<uint64_t, 64> bluePawnTable = {
    };
    const std::array<uint64_t, 64> bluePawnDiagonalTable = {
    };
    const std::array<uint64_t, 64> redPawnDiagonalTable = {
    };

    // Helper
    std::vector<uint16_t> getBits(uint64_t board);
    uint16_t generateMove(uint16_t start, uint16_t end, uint16_t type);
    void printMoves(std::vector<uint16_t> moves);
    
};


#endif

