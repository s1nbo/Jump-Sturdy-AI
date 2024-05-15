#ifndef TEST_HPP
#define TEST_HPP

#include "board.hpp"
#include "moves.hpp"
#include "ai.hpp"

#include <vector>
#include <string>
#include <array>
#include <chrono>


class Test {
public:
    Test() = default;

    // Milestone 1
    void test_game(int depth); // play a game with test[0] AI vs AI
    void test_move_generation(bool print_moves); // unit test different position and the move generation
    void test_move_generation_performance(int amount, int board_number); // test move generation, time taken per moves generation
    
    
    // Milestone 2
    void test_rate_board(int amount, int board_number); // test rate_board, time taken per rate_board
    void test_search_depth_minimax(int depth, int board_number); // search depth performance for minimax
    void test_search_depth_alphabeta(int depth, int board_number); // search depth performance for alphabeta
    void show_results();

    // look at position per second
    // * Saved time with Alphabeta pruning

    // Data 
    const std::array<std::string, 12> test = {
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
    "6/2b02b02/2r02r02/8/8/2b02b02/2r02r02/6 b"
    };

    const std::array<int, 12> answer = {
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
        8
    };

    int minimax_score = 0;
    int alphabeta_score = 0;

};

#endif