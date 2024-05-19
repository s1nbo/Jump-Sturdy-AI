#include "test.hpp"

void Test::test_game(int depth, std::string board_number){
    bitboard current_board;
    Board board(board_number, current_board);
    Moves moves;
    Ai ai;

    float move_count = 0;
    auto start = std::chrono::high_resolution_clock::now();
        
    while(move_count < 100) {
        std::vector<uint16_t> legal_moves = moves.generateMoves(current_board);
        uint16_t move = ai.alphabeta_handler(current_board, depth);
        std::cout << " Move: " << move << " ";
        move_count++;
        moves.printMoves({move});
        moves.updateBoard(current_board, move);
        if(moves.gameOver(current_board, legal_moves)) break;
        
    }
    board.printBitboard(current_board);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    
    std::cout << "Game with depth: " << depth << " Total moves: " << move_count <<  " Elapsed time: " << elapsed.count() << " s\n";
    std::cout << "Moves per second: " << move_count / elapsed.count() << "\n";
    std::cout << "\n";
    std::cout << "\n";
}

void Test::test_move_generation(bool print_moves){
    for(size_t i = 0; i < test.size(); i++){
        bitboard bitboard;
        Board board(test[i], bitboard);
        Moves moves;
        
        std::vector<uint16_t> legal_moves = moves.generateMoves(bitboard);
        std::cout << "Fen: " << test[i] << "\n";
        std::cout << "Legal Moves: " << legal_moves.size() << " Answer: " << answer[i] << "\n";
        if(print_moves) moves.printMoves(legal_moves);
        std::cout << "\n";
    }
}

void Test::test_move_generation_performance(int amount, int board_number){
    bitboard bitboard;
    Board board(test[board_number], bitboard);
    Moves moves;
    
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < amount; i++) moves.generateMoves(bitboard);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Generated " << amount << " times moves from board " << test[board_number] << " in " << elapsed.count() << "s\n";
    std::cout << "Boards per second: " << amount / elapsed.count() << "\n";
    std::cout << "Seconds per board: " <<  elapsed.count() / amount << "\n";
    std::cout << "\n";
}

void Test::test_rate_board(int amount, int board_number){
    bitboard bitboard;
    Board board(test[board_number], bitboard);
    Ai ai;
    
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < amount; i++) ai.rate_board(bitboard);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Rated " << amount << " times the board " << test[board_number] << " in " << elapsed.count() << " s\n";
    std::cout << "Boards rated per second: " << amount / elapsed.count() << "\n";
    std::cout << "Seconds per board: " <<  elapsed.count() / amount << "\n";
    std::cout << "\n";
    
}

void Test::test_search_depth_minimax(int depth, int board_number){
    bitboard bitboard;
    Board board(test[board_number], bitboard);
    Moves moves;
    Ai ai;
    auto start = std::chrono::high_resolution_clock::now();
    uint16_t best_move = ai.minimax_handler(bitboard, depth);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Runtime: " << elapsed.count() << " s\n";
    std::cout << "Nodes analyzed: " << ai.analyzed_nodes << "\n";
    std::cout << "Nodes per second: " << ai.analyzed_nodes / elapsed.count() << "\n";
    std::cout << "Best move: ";
    moves.printMoves({best_move});
    std::cout << "\n";
    minimax_score = ai.analyzed_nodes;
}

void Test::test_search_depth_minimax_performance(int depth, int board_number, int amount){
    bitboard bitboard;
    Board board(test[board_number], bitboard);
    Ai ai;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < amount; i++) ai.minimax_handler(bitboard, depth);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Runtime: " << elapsed.count() << " s\n";
    std::cout << "Runtime per move: " << elapsed.count() / amount << " s\n";
    std::cout << "Nodes per second: " << ai.analyzed_nodes / elapsed.count() << "\n";
    std::cout << "\n";
}

void Test::test_search_depth_alphabeta_performance(int depth, int board_number, int amount){
    bitboard bitboard;
    Board board(test[board_number], bitboard);
    Ai ai;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < amount; i++) ai.alphabeta_handler(bitboard, depth);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Runtime: " << elapsed.count() << " s\n";
    std::cout << "Runtime per move: " << elapsed.count() / amount << " s\n";
    std::cout << "Nodes per second: " << ai.analyzed_nodes / elapsed.count() << "\n";
    std::cout << "\n";
}

void Test::test_search_depth_alphabeta(int depth, int board_number){
    bitboard bitboard;
    Board board(test[board_number], bitboard);
    Moves moves;
    Ai ai;
    auto start = std::chrono::high_resolution_clock::now();
    uint16_t best_move = ai.alphabeta_handler(bitboard, depth);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Runtime: " << elapsed.count() << " s\n";
    std::cout << "Nodes analyzed: " << ai.analyzed_nodes << "\n";
    std::cout << "Nodes per second: " << ai.analyzed_nodes / elapsed.count() << "\n";
    std::cout << "Best move: ";
    moves.printMoves({best_move});
    std::cout << "\n";
    alphabeta_score = ai.analyzed_nodes;
}

void Test::show_results(){
    std::cout << "Minimax: " << minimax_score << " Nodes\n";
    std::cout << "Alphabeta: " << alphabeta_score << " Nodes\n";
    float improvement = minimax_score / alphabeta_score;
    std::cout << "Improvement: " << improvement << "\n"; 
    std::cout << "\n";
    alphabeta_score = 0;
    minimax_score = 0;
}