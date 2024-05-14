#include "ai.hpp"
#include "board.hpp"
#include "moves.hpp"
#include "connect.hpp"

#include <string>
#include <cassert>
#include <chrono>
// Main function

/*
. Connect to Server  (TODO)
1a. Start Game (TODO)
2. Get FEN from Server (TODO)

3. Convert FEN to Board (DONE)
3a. Check if game is over (DONE)


4. Get legal moves from Board (DONE)
5. Choose a move from legal moves (TODO) (AI)
6. Send move to Server (TODO)
7. Repeat from 2 until game is over
8. Close connection
*/
std::vector<std::string> tests(){
    return {
    "b0b0b0b0b0b0/1b0b0b0b0b0b01/8/8/8/8/1r0r0r0r0r0r01/r0r0r0r0r0r0 r",
    "b0b0b0b0b0b0/1b0b0b0b0b0b01/8/8/8/8/r0r0r0r0r0r0r0r0/6 r",
    "6/1b06/1r03bb2/2r02b02/8/5r0r01/2r0r04/6 r",
    "6/1b0b0b0b0b0b01/1b0b0b0b0b0b01/8/8/1r0r0r0r0r0r01/1r0r0r0r0r0r01/6 b",
    "b0b01b0b0b0/1b0b02b0b01/3b0b03/2b05/3r04/2r05/1r01rr1r0r01/r0r02r0r0 b",
    "6/1bbbbbbbbbbbb1/8/8/8/1r0r0r0r0r0r01/8/r0r0r0r0r0r0 b",
    "6/2b02b02/2r02r02/8/8/2b02b02/2r02r02/6 b",
    "2b03/8/8/3b0b03/2b03b01/2r03r01/2r05/6 r",
    "b03b01/3bb2bb1/2bb1br3/1b06/5r02/2rr5/1r02rr3/r0r02rr1 b",
    "b03b01/3b02b01/r01b05/8/8/3rbb03/1r06/r03r01 b"
    };
}

std::vector<int> answers(){
    return {
        34,
        22,
        17,
        36,
        35,
        22,
        8,
        7,
        19,
        20
    };
}



int main(){
    std::vector<std::string> test = tests();
    std::vector<int> answer = answers();

    // full game loop with test[0]
    bitboard current_board;
    Moves moves;
    Ai ai;
    Board board(test[0], current_board);
    int i = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while(i < 10000) {
        /* auto start = std::chrono::high_resolution_clock::now();

          // generate legal moves
         if (legal_moves.empty()){
            break;
        }; // check if game is over
        uint16_t move = ai.negamax_handler(current_board); // choose a move
        current_board = moves.updateBoard(current_board, move); // update board
        //std:: cout << "Turn: " << current_board.turn << std::endl;
        // moves.printMoves({move});
        if(moves.gameOver(current_board, legal_moves)){
            break;
        }
       

        i++;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Elapsed time: " << elapsed.count() << " s\n";
         */
        // rate current_board
        ai.rate_board(current_board);
        // std::vector<uint16_t> legal_moves = moves.generateMoves(current_board);
        i++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    /*
    std::string fen = board.bitboardFen(current_board);
    std::cout << "Fen: " << fen << std::endl;
    std::cout << "Game Over: " << i << std::endl;
    */
    return 0;
}

/*
auto start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < 100000; i++){

}
   

*/



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

bit 15: Takes a piece


00 01 02 03 04 05 06 07
08 09 10 11 12 13 14 15
16 17 18 19 20 21 22 23
24 25 26 27 28 29 30 31
32 33 34 35 36 37 38 39
40 41 42 43 44 45 46 47
48 49 50 51 52 53 54 55
56 57 58 59 60 61 62 63
*/

/*

 for (size_t i = 0; i < test.size(); i++){
        bitboard bitboard;
        Board board(test[i], bitboard);
        Moves moves;
        Ai ai;
        std::vector<uint16_t> legal_moves = moves.generateMoves(bitboard);
        // rating of current board
        int rating = ai.rate_board(bitboard);
        uint16_t move = ai.negamax_handler(bitboard, legal_moves);
        bitboard = moves.updateBoard(bitboard, move);
        // new rating of board
        int new_rating = ai.rate_board(bitboard);

        std::cout << "Rating: " << rating << " New Rating:" << new_rating << " Turn: " << bitboard.turn << std::endl;
        // board.printBitboard(bitboard);
    }

*/