#include "milestone.hpp"


void milestone12(){

    Tt table;
    Test test;
    
    // Milestone 1
    bitboard current_board;
    Board board("6/3b0b03/3r02bb1/b0b03bb2/rrrr1bb2rr1/3b0b01r01/2r01r02r0/4r01 r", current_board);
    Moves moves;
    auto legal = moves.generateMoves(current_board);
    moves.printMoves(legal);
    board.printBitboard(current_board);
    // 6/3b0b03/3r02bb1/b0b03bb2/rrrr1bb2rr1/3r0b01r01/2r04r0/4r01 b
    std::cout << "Milestone 1\n" << "Test Ai vs Ai\n";
    test.test_game(6,"b0b0b0b0b0b0/1b0b0b0b0b0b01/8/8/8/8/1r0r0r0r0r0r01/r0r0r0r0r0r0 b");

    // test updateBoard and undoMove

    
   
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
    test.test_search_depth_alphabeta(3, 0, table);
    test.show_results();
    test.test_search_depth_minimax(3, 0);
    test.test_search_depth_alphabeta(3, 0, table);
    test.show_results();
    test.test_search_depth_minimax(3, 10);
    test.test_search_depth_alphabeta(3, 10, table);
    test.show_results();
    test.test_search_depth_minimax(3, 11);
    test.test_search_depth_alphabeta(3, 11, table);
    test.show_results();
    std::cout << "Test Search Depth 4\n";
    test.test_search_depth_minimax(4, 0);
    test.test_search_depth_alphabeta(4, 0, table);
    test.show_results();
    test.test_search_depth_minimax(4, 10);
    test.test_search_depth_alphabeta(4, 10, table);
    test.show_results();
    test.test_search_depth_minimax(4, 11);
    test.test_search_depth_alphabeta(4, 11, table);
    test.show_results();
    std::cout << "Test Search Depth 5\n";
    test.test_search_depth_minimax(5, 0);
    test.test_search_depth_alphabeta(5, 0, table);
    test.show_results();
    test.test_search_depth_minimax(5, 10);
    test.test_search_depth_alphabeta(5, 10, table);
    test.show_results();
    test.test_search_depth_minimax(5, 11);
    test.test_search_depth_alphabeta(5, 11, table);
    test.show_results();
    std::cout << "Test Search Depth 6\n";
    test.test_search_depth_alphabeta(6, 0, table);

    std::cout << "Test Search Depth Performance 3\n";
    test.test_search_depth_minimax_performance(3, 0, 1000);
    test.test_search_depth_alphabeta_performance(3, 0, 1000, table);
    test.test_search_depth_minimax_performance(3, 10, 1000);
    test.test_search_depth_alphabeta_performance(3, 10, 1000, table);
    test.test_search_depth_minimax_performance(3, 11, 1000);
    test.test_search_depth_alphabeta_performance(3, 11, 1000, table);

    std::cout << "Test Search Depth Performance 4\n";
    test.test_search_depth_minimax_performance(4, 0, 1000);
    test.test_search_depth_alphabeta_performance(4, 0, 1000, table);
    test.test_search_depth_minimax_performance(4, 10, 1000);
    test.test_search_depth_alphabeta_performance(4, 10, 1000, table);
    test.test_search_depth_minimax_performance(4, 11, 1000);
    test.test_search_depth_alphabeta_performance(4, 11, 1000, table);

    std::cout << "Test Search Depth Performance 5\n";
    test.test_search_depth_alphabeta_performance(5, 0, 1000, table);
    test.test_search_depth_alphabeta_performance(5, 10, 1000, table);
    test.test_search_depth_alphabeta_performance(5, 11, 1000, table);
}

void ubuntuTestsAlphaBeta(){
    std::string inital_board = "b0b0b0b0b0b0/1b0b0b0b0b0b01/8/8/8/8/1r0r0r0r0r0r01/r0r0r0r0r0r0 b";

    //inital_board = "6/4bbb02/b02b01b02/1b02b03/2b01rrrr2/6r01/r01r0r0r03/6 r";
    Test test;
    test.test_make_unmake_move();
    test.test_game(5, inital_board);

    


}