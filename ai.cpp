#include "ai.hpp"


Ai::Ai(){}
uint16_t Ai::choose_move(bitboard &board){
    int search_depth = 2;
    // alpha beta
    int alpha = -1000;
    int beta = 1000;
    
    Moves m;
    if(board.turn == 1){ // Blue turn max player
        max(search_depth, alpha, beta, board, m);
    } else { // Red turn min player
        min(search_depth, alpha, beta, board, m);
    }
    return best_move;
}
    

int Ai::max(int depth, int alpha, int beta, bitboard &board, Moves &m){
    // generate moves
    std::vector<uint16_t> moves = m.generateMoves(board);
    if(depth == 0 or moves.size() == 0) return rate_board(board);
    int max_score = alpha;
    for(auto move : moves){
        bitboard new_board = m.updateBoard(board, move);
        int score = min(depth-1, max_score, beta, new_board, m);
        if(score > max_score){
            max_score = score;
            best_move = move;
        }
        if(max_score >= beta) return max_score;
    }
    return max_score;
}

int Ai::min(int depth, int alpha, int beta, bitboard &board, Moves &m){
    // generate moves
    std::vector<uint16_t> moves = m.generateMoves(board);
    if(depth == 0 or moves.size() == 0) return rate_board(board);
    int min_score = beta;
    for(auto move : moves){
        bitboard new_board = m.updateBoard(board, move);
        int score = max(depth-1, alpha, min_score, new_board, m);
        if(score < min_score){
            min_score = score;
        }
        if(min_score <= alpha) return min_score;
    }
    return min_score;
}



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

