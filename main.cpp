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
    std::string fen = "6/1bbbbbbbbbbbb1/8/8/8/1r0r0r0r0r0r01/8/r0r0r0r0r0r0 r";
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

    //uint16_t move = legal_moves[0];
    //bitboard = moves.updateBoard(bitboard, move);
    //board.printBitboard(bitboard);

    return 0;
}



/*

import dummy_ai as da
import string_conversion as sc

import legal_moves as lm
from translate_moves import translate_move

import time 
from sys import argv
import json


if __name__ == '__main__':
    strings = ["1b04/2b03b01/b01rr5/r02b01b02/1b06/1r02b03/8/1r01r0r0r0 b"]

    
    for str in strings:
        try:
            board = sc.fen_board(str)
            moves = lm.legal_moves(board)

            print(len(moves))
            for move in moves:
                print(translate_move(move), end=" ")
            # move_rating = da.move_rating(board, moves)
           