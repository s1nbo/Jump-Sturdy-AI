#include "ai.hpp"


Ai::Ai(){}

int Ai::rate_board(bitboard &board){
    // blue pawn = 1 * position from bottom to top
    // red pawn = -1 * position from top to bottom
    // blue_blue knight = 3 * position from bottom to top
    // red_red knight = -3 * position from top to bottom
    // red_blue knight = 2 * position from bottom to top
    // blue_red knight = -2 * position from top to bottom
    int score = 0;

    auto blue_pawn = getBits(board.blue_pawns);
    auto red_pawn = getBits(board.red_pawns);
    auto blue_blue_knight = getBits(board.blue_blue_knight);
    auto red_red_knight = getBits(board.red_red_knight);
    auto red_blue_knight = getBits(board.red_blue_knight);
    auto blue_red_knight = getBits(board.blue_red_knight);
    // get bits returns values from 0 to 63
    // row 0 is the top row
    // row 7 is the bottom row
    // we want the row as a score
    // exmaple if bit 0-7 score is 7
    // if bit 8-15 score is 6
    // if bit 56-63 score is 0

    for(auto bit : blue_pawn) score += 7 - bit/8;
    for(auto bit : red_pawn) score -= bit/8+1;
    for(auto bit : blue_blue_knight) score += 3 * (7 - bit/8);
    for(auto bit : red_red_knight) score -= 3 * (bit/8+1);
    for(auto bit : red_blue_knight) score += 2 * (7 - bit/8);
    for(auto bit : blue_red_knight) score -= 2 * (bit/8+1);
    // if a blue  figure is on the top row, it is worth 100 points
    // if a red  figure is on the bottom row, it is worth -100 points
    if((board.blue_pawns | board.blue_blue_knight | board.red_blue_knight) & 0xFF){
        score += 100;
    }
    if((board.red_pawns | board.red_red_knight | board.blue_red_knight) & 0xFF00000000000000){
        score -= 100;
    }
    return score;
}

std::vector<uint16_t> Ai::getBits(uint64_t board){
    std::vector<uint16_t> ans;
    ans.reserve(64);
    while(board){
        uint16_t bit = __builtin_ctzll(board);
        ans.push_back(bit);
        board &= board - 1;
    }
    return ans;
}

uint16_t Ai::negamax_handler(bitboard &board){
    int search_depth = 6;
    int alpha = -1000;
    int beta = 1000;
    int best_value = -1000;
    std::uint16_t best_move = 0;
    Moves m;
    auto childNodes = m.generateMoves(board);

    for (auto child : childNodes){
        int value = -negamax(child, search_depth-1, -beta, -alpha, board, m);
        if(value > best_value){
            best_value = value;
            best_move = child;
        }
        alpha = std::max(best_value, alpha);
        if(alpha >= beta){
            break;
        }
    }
    return best_move;
}

int Ai::negamax(uint16_t move, int depth, int alpha, int beta, bitboard &board, Moves m){
    bitboard updated_board = m.updateBoard(board, move);
    if(depth == 0){
        return rate_board(updated_board);
    }
    auto childNodes = m.generateMoves(updated_board);
    int value = -1000;
    for(auto child : childNodes){
        value = std::max(value, -negamax(child, depth-1, -beta, -alpha, updated_board, m));
        alpha = std::max(alpha, value);
        if(alpha >= beta){
            break;
        }
    }
    return value;
}


    



uint16_t Ai::minimax_handler(bitboard &board){}

int Ai::minimax(uint16_t move, int depth, bitboard &board, Moves m){}

uint16_t Ai::alphabeta_handler(bitboard &board){}

int Ai::alphabeta(uint16_t move, int depth, int alpha, int beta, bitboard &board, Moves m){}

