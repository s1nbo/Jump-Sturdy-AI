#include "test.hpp"





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

    auto start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < 100000; i++){

}
   
*/


/*
    // full game loop with test[0]
    int i = 0;
    auto start = std::chrono::high_resolution_clock::now();

       auto start = std::chrono::high_resolution_clock::now();

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
    
        // rate current_board
        ai.rate_board(current_board);
        // std::vector<uint16_t> legal_moves = moves.generateMoves(current_board);
        i++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
   
    std::string fen = board.bitboardFen(current_board);
    std::cout << "Fen: " << fen << std::endl;
    std::cout << "Game Over: " << i << std::endl;
    
    

    */

