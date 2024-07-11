#ifndef TEST_HPP
#define TEST_HPP

#include "board.hpp"
#include "moves.hpp"
#include "ai.hpp"
#include "tt.hpp"

#include <vector>
#include <string>
#include <array>
#include <chrono>


class Test {
public:
    Test() = default;

    void test_make_unmake_move(); // test make and unmake move

    // Milestone 1
    void test_game(int depth, std::string board_number); // play a game with test[0] AI vs AI
    void test_move_generation(bool print_moves); // unit test different position and the move generation
    void test_move_generation_performance(int amount, int board_number); // test move generation, time taken per moves generation
    
    
    // Milestone 2
    void test_rate_board(int amount, int board_number); // test rate_board, time taken per rate_board
    void test_search_depth_minimax(int depth, int board_number); // search depth performance for minimax
    void test_search_depth_alphabeta(int depth, int board_number, Tt &table); // search depth performance for alphabeta
    void show_results();
    void test_search_depth_minimax_performance(int depth, int board_number, int amount); // search depth performance for minimax
    void test_search_depth_alphabeta_performance(int depth, int board_number, int amount, Tt &table); // search depth performance for alphabeta
    
    // look at position per second
    // * Saved time with Alphabeta pruning

    // Data 
    const std::array<std::string, 14> test = {
    "b0b0b0b0b0b0/1b0b0b0b0b0b01/8/8/8/8/1r0r0r0r0r0r01/r0r0r0r0r0r0 b",
    "b0b0b0b0b0b0/1b0b0b0b0b0b01/8/8/8/8/r0r0r0r0r0r0r0r0/6 r",
    "6/1b06/1r03bb2/2r02b02/8/5r0r01/2r0r04/6 r",
    "6/1b0b0b0b0b0b01/1b0b0b0b0b0b01/8/8/1r0r0r0r0r0r01/1r0r0r0r0r0r01/6 b",
    "b0b01b0b0b0/1b0b02b0b01/3b0b03/2b05/3r04/2r05/1r01rr1r0r01/r0r02r0r0 b",
    "6/1bbbbbbbbbbbb1/8/8/8/1r0r0r0r0r0r01/8/r0r0r0r0r0r0 b",
    "6/2b02b02/2r02r02/8/8/2b02b02/2r02r02/6 b",
    "2b03/8/8/3b0b03/2b03b01/2r03r01/2r05/6 r",
    "b03b01/3bb2bb1/2bb1br3/1b06/5r02/2rr5/1r02rr3/r0r02rr1 b",
    "b03b01/3b02b01/r01b05/8/8/3rbb03/1r06/r03r01 b",
    "3b02/2bb2b02/5b0bb1/2r0b04/2rb3b01/1rr1rr2r0r0/5r02/2rr3 b",
    "6/2b02b02/2r02r02/8/8/2b02b02/2r02r02/6 b",
    "1bb4/1b0b05/b01b0bb4/1b01b01b02/3r01rr2/b0r0r02rr2/4r01rr1/4r0r0 b",
    "6/4bbb02/b02b01b02/1b02b03/2b01rrrr2/6r01/r01r0r0r03/5r0 r"
    };

    const std::array<int, 14> answer = {
        34,
        22,
        17,
        36,
        35,
        22,
        8,
        7,
        19,
        20,
        24,
        8,
        25,
        24
    };

    int minimax_score = 0;
    int alphabeta_score = 0;

};

#endif