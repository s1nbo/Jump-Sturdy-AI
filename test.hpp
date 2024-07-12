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
#include <cassert>


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
    void test_alpha_beta(int depth);
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


    const std::array<std::string, 57> ab_data = {
        "1bb4/1b0b05/b01b0bb4/1b01b01b02/3r01rr2/b0r0r02rr2/4r01rr1/4r0r0 b",
        "1bb4/1b0b05/b01b0bb4/1b01b01b02/3r01rr2/b0r0r02rr2/4r01rr1/4r0r0 r",
        "6/3b0b03/3r02bb1/b0b03bb2/rrrr1bb2rr1/2b01b03/2r01r01r0r0/4r01 b",
        "6/3b0b03/3r02bb1/b0b03bb2/rrrr1bb2rr1/2b01b01r01/2r01r02r0/4r01 r",
        
        "1b0b0b02/8/3b04/3b04/r0r06/2b05/5r0r01/6 b",
        "6/4bb3/8/8/4b0r0b01/8/8/6 b",

        "6/8/8/8/b0b02b0b0/2b05/2r0r0r0r02/6 b",
        "3b01b0/3bb1b02/8/8/8/2r0b0r02/8/0r04r0 b",

        "6/4b01b01/8/5b01b0/2b04r0/1b04r01/5r01rr/1r04 b",
        "3bb2/b02b02b01/3b02bbb0/1b06/1r0r02r01r0/6r01/5r0r0r0/6 b",

        "2b03/1b0b05/6b01/3bb2r01/3r02r01/2b05/2r03r01/3r02 b",
        "2b03/1b0b05/6b01/3b02r01/1b01r02r01/2b05/2r03r01/3r02 b",

        "6/8/6r01/2b01r0r02/1r03r02/8/8/6 r",
        "1b02b0b0/1r06/1b04b01/8/2r02b02/1r01r01r02/5r0r01/r0r01r011 b",
        "3b0b01/8/1b0b01b0b02/2r01b01b01/8/2rr2r02/1r06/2r03 r",

        "6/1bb1b0bbb0b01/r02b04/2b01b0b02/2r02r02/1r02rrr02/6rr1/2r01r01 r",
        "3b02/1bb6/1r0b02r02/2r05/4r03/8/2r03r01/6 r",

       "3b02/5b02/8/1b06/4bb3/6r01/1r06/1r0r03 b",
       "6/1b06/5b02/2b05/2b05/4r03/2r05/6 b",

       "6/8/2b01b03/6b0r0/4b03/8/r07/6 b",
       "6/8/8/8/8/1r0b0r0b0r02/4r03/3rr2 b",

       "2b03/r07/3r04/6rr1/4bb3/2b04bb/3rr1rr2/5r0 b",
       "6/3b01b02/4bb3/1bb6/3rr1r02/8/4r03/6 r",

       "3b01b0/3b04/3bb4/2r05/rbbr5rb/4rr3/br4r02/6 b",
       "1b01b01b0/bb6bb/3bb4/2rr5/r0r01r03r0/1br3rr2/8/6 r",

       "1bbb01b0b0/4b03/4r01b01/2b01r0b02/5r02/1r06/3r02r01/1rrr01r01 r",
       "b0b02b01/3b01b0b01/2r01r02b0/4r0b02/r07/3b04/5r02/rr3rr1 r",

       "1b0b0b0b0b0/1b06/8/2bb5/8/3rr4/1r03r0r01/r0r0r0r0r0r0 b",
       "2b01bbb0/2b0r0b03/4b03/2bbb04/3r04/5r02/1r03r02/r0r0r0r0r0r0 r",

       "b02b01b0/4r03/1b02r03/1bb6/8/4r0b02/1r03r02/r01r02r0 r",
       "1b01b01b0/1b06/3b04/8/4b0r02/2b03r01/3r0r03/r03r01 b",

       "b0b01bb2/6b01/3bb4/4b0b02/3r04/3r04/1r0r05/1r0rrrr2 b",
       "b04b0/8/7r0/1b03b02/1rr5r0/4r0b02/b07/4r01 b",

       "1bb4/1b0b01r03/b01b0bb4/1b01b01b02/3r01r02/b0r0r02rr2/4r01rr1/4r0r0 b",
       "1bb4/1b0b05/b01b0bb4/1b01b01b02/3r01rr2/1r0r02rr2/b03r01rr1/2r01r0r0 r",

       "6/1bb1b02b01/8/2r05/3r01b02/5r0r01/2rr1r03/6 b",
       "3b02/5r02/3r04/8/8/2b02b02/2r05/6 b",

       "b05/1r03r02/2b01b03/2r01r03/1b06/8/3b02b01/r04r0 b",
       "b05/1r03r02/2b01b03/2r01r03/1b06/8/3b02b01/r04r0 b",

       "b05/1r03r02/2b01b03/2r01r03/1b06/8/3b02b01/r04r0 b",
       "6/3b0b03/8/1rrr02bb2/6b01/2b05/3r04/5r0 b",

       "1b01b02/8/3b04/1rbr05/6bb1/1r02r03/2rr5/8 b",
       "6/4b03/1b01b01bb2/r02r04/8/br01/2r02r02/6 r",

       "2b03/3bb4/1b02b03/4br3/3r02bb1/1rr2rr3/2r03rr1/6 b",
       "6/4bb3/5b02/r03b03/1b02r01r0b0/1rr2r02r0/8/6 r",

       "6/6b01/8/2b02rr2/8/8/6r01/6 r",
       "2b03/8/8/1b03b02/3rr4/8/8/6 b",

       "6/8/5bb2/8/6b01/8/r07/6 b",
       "6/4r03/8/8/8/8/4b03/6 r",

       "b0b01b0b0b0/8/4b0b02/3br4/6b01/2rr3rb1/4rr3/r0r02r0r0 r",
       "b0b0b0b0b0b0/8/5b01b0/5r0b01/3b04/4r0rr1rb/3r04/r0r0r0r01r0 b",

       "b0b0b0b0b01/1b01b02b01/2r05/2r01b03/1r06/3bb4/2r0r02r01/r01r0r0r0r0 b",
       "b01b03/4b03/1b03r02/3rbb03/1bb4r01/8/2r02r02/1r0r02r0 r",

       "1b04/1bb2b0bb2/2bb1b03/3rr4/2r02b01r0/1b02r0rr1b0/1rr2r03/6 r",
       "6/8/8/3b04/3b04/8/2r01r03/6 b",

       "1b04/2b03b01/b01rr5/r02b01b02/1b06/1r02b03/8/1r01r0r0r0 r",
       "b02b01b0/3b01b02/b02b02b01/b01b05/5r02/1r02r02r0/2rrr02r01/r03r01 b"
    };
    //const std::array<int, 14> ab_answer = {};

};

#endif