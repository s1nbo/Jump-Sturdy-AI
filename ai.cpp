#include "ai.hpp"
#include "board.hpp"
#include <climits>
#include <cstdlib>
#include <utility>



int value(int pos, bool turn){
    // get fields of the pawns, to close to the edge the more valuable

    // blue wants vlaues close to 0-7, red wants values close to 56-63
    // blue gets * 7 for 0-7, red gets * 7 for 56-63
    // blue gets * 6 for 8-15, red gets * 6 for 48-55
    // blue gets * 5 for 16-23, red gets * 5 for 40-47
    // blue gets * 4 for 24-31, red gets * 4 for 32-39
    // blue gets * 3 for 32-39, red gets * 3 for 24-31
    // blue gets * 2 for 40-47, red gets * 2 for 16-23
    // blue gets * 1 for 48-55, red gets * 1 for 8-15
    // blue gets * 1 for 56-63, red gets * 1 for 0-7
    if(turn) return pos < 16 ? 6 : pos < 24 ? 5 : pos < 32 ? 4 : pos < 40 ? 3 : pos < 48 ? 2 : pos < 56 ? 1 : 1;
    return pos < 8 ? 1 : pos < 16 ? 1 : pos < 24 ? 2 : pos < 32 ? 3 : pos < 40 ? 4 : pos < 48 ? 5 : pos < 56 ? 6 : 7;

}

int Ai::rate_board(bitboard &board){

    // Check if game is over
    uint64_t red = board.red_pawns | board.red_red_knight | board.blue_red_knight;
    uint64_t blue = board.blue_pawns |board.red_blue_knight | board.blue_blue_knight;

    if (board.turn == 1){
        if(blue & 0xff || red == 0) return INT_MAX;
        if(red & 0xff00000000000000 || blue == 0) return INT_MIN;
    } else {
        if(red & 0xff00000000000000 || blue == 0) return INT_MAX;
        if(blue & 0xff || red == 0) return INT_MIN;
    }
    // Check if moves are possible

    
    // Multiply by 1 if blue, -1 if red
    int who2Move = board.turn ? 1 : -1;

    int materialScore = 0;
    int mobilityScore = 0;

    int pawnWt = 100;
    int knightWt = 220;


    auto blue_pawns = getBits(board.blue_pawns);
    auto red_pawns = getBits(board.red_pawns);

    for(auto pawn : blue_pawns)materialScore += pawnWt * value(pawn, board.turn);
    for(auto pawn : red_pawns)materialScore -= pawnWt * value(pawn, board.turn);

    // get fields of the knights, to close to the edge the more valuable
    auto blue_blue_knight = getBits(board.blue_blue_knight);
    auto red_red_knight = getBits(board.red_red_knight);

    for(auto knight : blue_blue_knight)materialScore += knightWt * value(knight, board.turn);
    for(auto knight : red_red_knight)materialScore -= knightWt * value(knight, board.turn);

    // get fields of the knights, to close to the edge the more valuable
    auto blue_red_knight = getBits(board.blue_red_knight);
    auto red_blue_knight = getBits(board.red_blue_knight);

    for(auto knight : red_blue_knight)materialScore += knightWt * value(knight, board.turn);
    for(auto knight : blue_red_knight) materialScore -= knightWt * value(knight, board.turn);

    return (materialScore + mobilityScore) * who2Move;
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

// Alpha Beta with Iterative Deepening
uint16_t Ai::alphabeta_handler(bitboard &board, int search_depth, Tt &table){
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int best_value = INT_MIN;
    int best_move_pos = 0;
    Moves m;
    analyzed_nodes = 0;
    // auto hash = table.zorbist_hash(board);
    
    // if(table.probe(hash, board.turn)) return table.probe(hash, board.turn); // Transposition table
    auto childNodes = m.generateMoves(board);
    
    for(int cur_depth = 1; cur_depth <= search_depth; cur_depth++){ // iterative deepening
       for (size_t i = 0; i < childNodes.size(); i++) {
            
            auto move_made = m.updateBoard(board, childNodes[i]);
            int value = alphabetaMin(cur_depth-1, alpha, beta, board, m, table);
            
            m.undoMove(board, childNodes[i], move_made);
            //int value = 0;

            // check if temp board is the same as the current board

            
            if(value > best_value) {
                best_value = value;
                best_move_pos = i;
                // table.store(hash, best_move, board.turn);
            }
            alpha = std::max(best_value, alpha);
            if(alpha >= beta) break;
        }
        std::swap(childNodes[0], childNodes[best_move_pos]);
        //alpha = INT_MIN;
        //beta = INT_MAX;
    }
    //return childNodes[rand() % childNodes.size()];
    return childNodes[0];
};

int Ai::alphabetaMax(int depth, int alpha, int beta, bitboard &board, Moves &m, Tt &table){
    analyzed_nodes++;
    if(depth == 0) return rate_board(board);
    for(auto child : m.generateMoves(board)){
        uint16_t move_made = m.updateBoard(board, child);
        int score = alphabetaMin(depth-1, alpha, beta, board, m, table);
        m.undoMove(board, child, move_made);

        if(score >= beta){
            return beta;
        }
        if(score > alpha){
            alpha = score;
        }
    }
    return alpha;
};

int Ai::alphabetaMin(int depth, int alpha, int beta, bitboard &board, Moves &m, Tt &table){
    analyzed_nodes++;
    if(depth == 0) return -rate_board(board);
    for(auto child : m.generateMoves(board)){
        
        uint16_t move_made = m.updateBoard(board, child);
        int score = alphabetaMax(depth-1, alpha, beta, board, m, table);
        m.undoMove(board, child, move_made);
        
        if(score <= alpha){
            return alpha;
        }
        if(score < beta){
            beta = score;
        }
    }
    return beta;
};



/* ------------------------- For testing purposes -------------------------  */

// Negamax with Iterative Deepening
uint16_t Ai::negamax_handler(bitboard &board, int search_depth){
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int best_value = INT_MIN;
    std::uint16_t best_move = 0;
    Moves m;
    analyzed_nodes = 0;
    auto childNodes = m.generateMoves(board);

    for(int cur_depth = 1; cur_depth <= search_depth; cur_depth++){
        for (size_t i = 0; i < childNodes.size(); i++){
            uint16_t move_made = m.updateBoard(board, childNodes[i]); // make a move
            int value = negamax(search_depth-1, alpha, beta, board, m); // go into the tree
            m.undoMove(board, childNodes[i], move_made); // undo the move
            if(value > best_value){ // if the value is better than the best value
                best_value = value;
                best_move = i;
            }
            alpha = std::max(best_value, alpha);
            if(alpha >= beta) break;
        }
        // take best move and put it in the front of childNodes
        std::swap(childNodes[0], childNodes[best_move]);
    }
    return best_move;
}

int Ai::negamax(int depth, int alpha, int beta, bitboard &board, Moves m){
    analyzed_nodes++;
    if(depth == 0) return rate_board(board);
    auto childNodes = m.generateMoves(board);
    int value = INT_MIN;

    for(size_t i = 0; i < childNodes.size(); i++) {
        uint16_t move_made = m.updateBoard(board, childNodes[i]); // make a move
        value = std::max(value, -negamax(depth-1, -beta, -alpha, board, m));
        m.undoMove(board, childNodes[i], move_made); // undo the move
        alpha = std::max(alpha, value);
        if(alpha >= beta) break;
    }
    return value;
}


// Not as important, does not have Iterative deepening
uint16_t Ai::minimax_handler(bitboard &board, int search_depth){
    int best_value = INT_MIN;
    uint16_t best_move = 0;
    Moves m;
    analyzed_nodes = 0;
    auto childNodes = m.generateMoves(board);

    for(auto child : childNodes){
        uint16_t move_made = m.updateBoard(board, child);
        int value = maxi(search_depth-1, board, m);
        m.undoMove(board, child, move_made);
        if(value > best_value){
            best_value = value;
            best_move = child;
        }
    }
    return best_move;
};

int Ai::maxi(int depth, bitboard &board, Moves m){
    analyzed_nodes++;
    if (depth == 0) return rate_board(board);
    int max = INT_MIN;
    for(auto child : m.generateMoves(board)){
        uint16_t move_made = m.updateBoard(board, child);
        max = std::max(max, mini(depth-1, board, m));
        m.undoMove(board, child, move_made);
    }
    return max;
};

int Ai::mini(int depth, bitboard &board, Moves m){
    analyzed_nodes++;
    if (depth == 0) return -rate_board(board);
    int min = INT_MAX;
    for(auto child : m.generateMoves(board)){
        uint16_t move_made = m.updateBoard(board, child);
        min = std::min(min, maxi(depth-1, board, m));
        m.undoMove(board, child, move_made);
    }
    return min;
};




/*
    // if blue pawn in row 1 return Max
    // if red pawn in row 8 return Min
    uint64_t red = board.red_pawns | board.red_red_knight | board.blue_red_knight;
    uint64_t blue = board.blue_pawns |board.red_blue_knight | board.blue_blue_knight;
    int turn = board.turn ? 1 : -1;
    // if one player has piece on the last row
    if(blue & 0xff) return 10000000*turn;
    if(red & 0xff00000000000000) return -10000000*turn;
    
    int blue_score = 0;
    int red_score = 0;
    // store temporary board to later assert
    
    for(auto i : getBits(board.blue_pawns)) blue_score += 100 * (8 - (i / 8));
    for(auto i : getBits(board.blue_blue_knight)) blue_score += 120 * (8 - (i / 8));
    for(auto i : getBits(board.red_blue_knight)) blue_score += 120 * (8 - (i / 8));

    for(auto i : getBits(board.red_pawns)) red_score += 100 * (i / 8);
    for(auto i : getBits(board.red_red_knight)) red_score += 120 * (i / 8);
    for(auto i : getBits(board.blue_red_knight)) red_score += 120 * (i / 8);
    
    // New rating system
    for(auto i : getBits(board.blue_pawns)) blue_score += 100;
    for(auto i : getBits(board.blue_blue_knight)) blue_score += 200;
    for(auto i : getBits(board.red_blue_knight)) blue_score += 200;

    for(auto i : getBits(board.red_pawns)) red_score += 100;
    for(auto i : getBits(board.red_red_knight)) red_score += 200;
    for(auto i : getBits(board.blue_red_knight)) red_score += 200;
  
    int score =  red_score - red_score;

    // check if temp board is the same as the current board
    // Instead of flipping the entire score based on the turn, adjust the interpretation of the score
    if (!board.turn) { // Assuming 0 is for blue and 1 is for red
        return score; // For blue, a positive score is good
    } else {
        return -score; // For red, a positive score (which is now negative) is good
    }


*/