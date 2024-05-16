#include "ai.hpp"
#include "board.hpp"
#include "moves.hpp"
#include "connect.hpp"
#include "test.hpp"

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




int main(){
    Test test;
    // Milestone 1
    std::cout << "Milestone 1\n" << "Test Ai vs Ai\n";
    test.test_game(6);
    std::cout << "Test Move Generation\n";
    test.test_move_generation(false);
    std::cout << "Test Move Generation Performance\n";
    test.test_move_generation_performance(10000, 0);
    test.test_move_generation_performance(10000, 10);
    test.test_move_generation_performance(10000, 11);

    // Milestone 2
    std::cout << "Milestone 2\n" << "Test Rate Board\n";
    test.test_rate_board(10000, 0);
    test.test_rate_board(10000, 10);
    test.test_rate_board(10000, 11);
    std::cout << "Test Search Depth 3\n";
    test.test_search_depth_minimax(3, 0);
    test.test_search_depth_alphabeta(3, 0);
    test.show_results();
    std::cout << "Test Search Depth 4\n";
    test.test_search_depth_minimax(4, 0);
    test.test_search_depth_alphabeta(4, 0);
    test.show_results();
    std::cout << "Test Search Depth 5\n";
    test.test_search_depth_minimax(5, 0);
    test.test_search_depth_alphabeta(5, 0);
    test.show_results();
    std::cout << "Test Search Depth 6\n";
    test.test_search_depth_alphabeta(6, 0);
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

bit 15: Does the move capture a piece (take)


00 01 02 03 04 05 06 07
08 09 10 11 12 13 14 15
16 17 18 19 20 21 22 23
24 25 26 27 28 29 30 31
32 33 34 35 36 37 38 39
40 41 42 43 44 45 46 47
48 49 50 51 52 53 54 55
56 57 58 59 60 61 62 63

"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
*/

