#include "ai.hpp"

int Ai::rate_board(bitboard &board){

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

    for(auto i : getBits(board.blue_pawns)) blue_score += 100 * (8 - (i / 8));
    for(auto i : getBits(board.blue_blue_knight)) blue_score += 120 * (8 - (i / 8));
    for(auto i : getBits(board.red_blue_knight)) blue_score += 120 * (8 - (i / 8));

    for(auto i : getBits(board.red_pawns)) red_score += 100 * (i / 8);
    for(auto i : getBits(board.red_red_knight)) red_score += 120 * (i / 8);
    for(auto i : getBits(board.blue_red_knight)) red_score += 120 * (i / 8);
  
    int score =  blue_score - red_score;

    return score*turn;
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


// Alpha Beta with Iterative Deepening
uint16_t Ai::alphabeta_handler(bitboard &board, int search_depth, Tt &table){
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int best_value = INT_MIN;
    std::uint16_t best_move = 0;
    Moves m;
    analyzed_nodes = 0;
    auto hash = table.zorbist_hash(board);

    // add iterative deepening
    if(table.probe(hash, board.turn)) return table.probe(hash, board.turn);
    auto childNodes = m.generateMoves(board);
    for(int cur_depth = 1; cur_depth <= search_depth; cur_depth++){
        for (size_t i = 0; i < childNodes.size(); i++){
            uint16_t move_made = m.updateBoard(board, childNodes[i]);
            int value = alphabetaMin(cur_depth-1, alpha, beta, board, m, table);
            m.undoMove(board, childNodes[i], move_made);
            auto hash = table.zorbist_hash(board);
            if(value > best_value){
                best_value = value;
                best_move = i;
                table.store(hash, best_move);
            }
            alpha = std::max(best_value, alpha);

            if(alpha >= beta) break;
        }
        // take best move and put it in the front of childNodes
        std::swap(childNodes[0], childNodes[best_move]);
        
    }
    return best_move;
};

int Ai::alphabetaMax(int depth, int alpha, int beta, bitboard &board, Moves &m, Tt &table){
    analyzed_nodes++;
    if(depth == 0) return rate_board(board);
    auto hash = table.zorbist_hash(board);
    uint16_t best_move = 0;
    if(table.probe(hash, board.turn)) return table.probe(hash, board.turn);
    for(auto child : m.generateMoves(board)){
        uint16_t move_made = m.updateBoard(board, child);
        int score = alphabetaMin(depth-1, alpha, beta, board, m, table);

        m.undoMove(board, child, move_made);

        if(score >= beta){
            table.store(hash, child, board.turn);
            return beta;
        }
        if(score > alpha){
            best_move = child;
            alpha = score;
        }
    }
    table.store(hash, best_move, board.turn);
    return alpha;
};

int Ai::alphabetaMin(int depth, int alpha, int beta, bitboard &board, Moves &m, Tt &table){
    analyzed_nodes++;
    if(depth == 0) return -rate_board(board);
    auto hash = table.zorbist_hash(board);
    if(table.probe(hash, board.turn)) return table.probe(hash, board.turn);
    uint16_t best_move = 0;
    if(table.probe(hash, board.turn)) return table.probe(hash, board.turn);
    for(auto child : m.generateMoves(board)){
        uint16_t move_made = m.updateBoard(board, child);
        int score = alphabetaMax(depth-1, alpha, beta, board, m, table);
        m.undoMove(board, child, move_made);
        if(score <= alpha){
            table.store(hash, child, board.turn);
            return alpha;
        }
        if(score < beta){
            beta = score;
            best_move = child;
        }
    }
    table.store(hash, best_move, board.turn);
    return beta;
};


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


