#include "ai.hpp"
#include "board.hpp"
#include "moves.hpp"
#include "connect.hpp"
#include "test.hpp"
#include "tt.hpp"
#include "milestone.hpp"

#include <climits>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include <chrono>
// Main function

int optimize_for_player(int player){
    if(player == 0) return 4;
    return 6;
}



//5. Choose a move from legal moves (TODO) (AI)

void mainloop(){
    bitboard current_board;
    Moves moves;
    Ai ai;
    Tt table;
    int depth = 8;

    srand(time(0));

    // Connect to server
    Network network("localhost", 5555);
    int player = std::stoi(network.getP());
    std::cout << "You are player " << player << std::endl;
    
    //depth = optimize_for_player(player);

    while(true){
        // Get game data from server
        
        std::string game_data = network.send(json("get").dump());
        auto game = json::parse(game_data);
        if(game["bothConnected"].get<bool>()){
            // if it is the players turn
            
            if((player == 0 && game["player1"].get<bool>()) || (player == 1 && game["player2"].get<bool>())){
                // Get the board from the server
                std::cout << "Reading Board" << std::endl;
                std::string board_fen = game["board"].get<std::string>();
                Board board(board_fen, current_board);

                // Generate Response
                std::cout << "Generating Response" << std::endl;
                uint16_t move = ai.alphabeta_handler(current_board, depth, table);
                std::string response = moves.translateMoves(move);
                std::cout << "Move: " << response << std::endl;
                
                // Send move to server
                std::cout << "Sending Move" << std::endl;
                network.send(json(response).dump());
                
                // Update board
                board.flushBoard(current_board);
            }
        }
    }
}



int main(){


    mainloop();
    

    //Test test;
    //test.test_alpha_beta(10);
    //test.test_game(8, "b0b0b0b0b0b0/1b0b0b0b0b0b01/8/8/8/8/1r0r0r0r0r0r01/r0r0r0r0r0r0 b");
}




/*




Moves are stored as an 16 bit Integer

bits:0-5 End Position {0,...,63} \ {0, 7, 56, 63}
bits 6-11 Start Position {0,...,63} \ {0, 7, 56, 63}
bits 12-14 Type of Piece
bit 15: Capture

        000: blue_pawns 0
        100: red_pawns 4
        001: blue_blue_knights 1
        101: red_red_knights 5
        010: red_blue_knight 2
        110: blue_red_knigts 6


"A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8",
"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
"A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
"A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
"A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1"
        

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





Minor Test function:
    for (int i = 0; i < 64; i++) {
        uint64_t blue_pawns = UINT64_MAX - uint64_t(pow(2, i));
        std::cout << i << " " << std::endl;

        for(auto pawn : getBits(blue_pawns)){
            std::cout << pawn << " ";
        }
        std::cout << "\n";
    }


std::vector<uint16_t> getBits(uint64_t board){
    std::vector<uint16_t> ans;
    //ans.reserve(64);
    while(board){
        uint16_t bit = __builtin_ctzll(board);
        ans.push_back(bit);
        board &= board - 1;
    }
    return ans;
}


*/