#ifndef BOARD_HPP
#define BOARD_HPP

#include <bitset>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

const size_t NSQUARES = 64;
enum Square : int {
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8,
	NO_SQUARE
};


class Board {
public:
    uint64_t blue_pawns = 0u;
    uint64_t red_pawns = 0u;
    uint64_t blue_blue_knight = 0u;
    uint64_t red_red_knight = 0u;
    uint64_t red_blue_knight = 0u;
    uint64_t blue_red_knight = 0u;
    uint64_t blocked_fields = 9295429630892703873u;
    
    bool turn;
    std::vector<std::vector<std::string>> board;

    Board(std::string fen);
    void fenBoard(std::string fen);
    void fenBitboard(std::string fen);
    std::vector<std::string> split(std::string str, char delimiter);
    
    void printBoard();
    void printBitBoard();
    void print_blockedfields();
};
#endif
