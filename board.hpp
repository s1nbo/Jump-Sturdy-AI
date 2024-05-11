#ifndef BOARD_HPP
#define BOARD_HPP

#include <bitset>
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>


struct bitboard{ 
    uint64_t blue_pawns = 0u;
    uint64_t red_pawns = 0u;
    uint64_t blue_blue_knight = 0u;
    uint64_t red_red_knight = 0u;
    uint64_t red_blue_knight = 0u;
    uint64_t blue_red_knight = 0u;
    uint64_t blocked_fields = 9295429630892703873u;
    bool turn;
};

class Board {
public:
    
    static constexpr int order[60] = {
        57, 58, 59, 60, 61, 62,
    48, 49, 50, 51, 52, 53, 54, 55, 
    40, 41, 42, 43, 44, 45, 46, 47, 
    32, 33, 34, 35, 36, 37, 38, 39, 
    24, 25, 26, 27, 28, 29, 30, 31, 
    16, 17, 18, 19, 20, 21, 22, 23, 
    8, 9, 10, 11, 12, 13, 14, 15, 
        1, 2, 3, 4, 5, 6};
    
    

    Board(std::string fen, bitboard &board);
    void fenBitboard(std::string fen, bitboard &board);

    void printBitboard(bitboard &board);
    void print_blockedfields(bitboard &board);
    std::string bitboardFen(bitboard &board);
    std::string addCounter(int &counter);
};



#endif


    
