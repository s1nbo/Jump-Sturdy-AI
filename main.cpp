#include "ai.hpp"
#include "board.hpp"
#include "moves.hpp"
#include "connect.hpp"

#include <string>
// Main function

/*
. Connect to Server  (TODO)
1a. Start Game (TODO)
2. Get FEN from Server (TODO)

3. Convert FEN to Board (DONE)
3a. Check if game is over (DONE)


4. Get legal moves from Board (DONE)
5. Choose a move from legal moves (DONE)
6. Send move to Server (TODO)
7. Repeat from 2 until game is over
8. Close connection
*/


int main(){
    // class board with 6/1bbbbbbbbbbbb1/8/8/8/1r0r0r0r0r0r01/8r0r0r0r0r0r0 b
    std::string fen = "6/1bbbbbbbbbbbb1/8/3r04/8/1r0r0r0r0r0r01/8/r0r0r0r0r0r0 b";
    bitboard bitboard;

    Moves moves;
    Board board(fen, bitboard);
    // std::cout << fen << std::endl;
    // std::cout << board.bitboardFen(bitboard) << std::endl;
    // board.printBitboard(bitboard);
    // which turn is it?
    std::vector<uint16_t> legal_moves = moves.generateMoves(bitboard);
    std::cout << "Game Over: " << moves.gameOver(bitboard, legal_moves) << std::endl;

    moves.printMoves(legal_moves);
    

    return 0;
}

/*
Moves are stored as an 16 bit Integer

bits:0-5 End Position {0,...,63} \ {0, 7, 56, 63}
bits 6-11 Start Position {0,...,63} \ {0, 7, 56, 63}
bits 12-14 Type of Piece

        000: blue_pawns 0
        100: red_pawns 4
        001: blue_blue_knights 1
        101: red_red_knights 5
        010: red_blue_knight 2
        110: blue_red_knigts 6

bit 15: Empty (Can be filled later)

00 01 02 03 04 05 06 07
08 09 10 11 12 13 14 15
16 17 18 19 20 21 22 23
24 25 26 27 28 29 30 31
32 33 34 35 36 37 38 39
40 41 42 43 44 45 46 47
48 49 50 51 52 53 54 55
56 57 58 59 60 61 62 63
*/