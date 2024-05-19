#include "ai.hpp"


int Ai::rate_board(bitboard &board){

    // if blue pawn in row 1 return Max
    // if red pawn in row 8 return Min
    uint64_t red = board.red_pawns | board.red_red_knight | board.blue_red_knight;
    uint64_t blue = board.blue_pawns |board.red_blue_knight | board.blue_blue_knight;
    // if one player has piece on the last row
    //if(blue & 0xff) return board.turn ? 10000000 : -10000000;
    //if(red & 0xff00000000000000) return board.turn ? -10000000 : 10000000;
    

    int blue_score = 0;
    int red_score = 0;


    for(auto i : getBits(board.blue_pawns)) blue_score += 100 * (8 - (i / 8));
    for(auto i : getBits(board.blue_blue_knight)) blue_score += 120 * (8 - (i / 8));
    for(auto i : getBits(board.red_blue_knight)) blue_score += 120 * (8 - (i / 8));

    for(auto i : getBits(board.red_pawns)) red_score += 100 * (i / 8);
    for(auto i : getBits(board.red_red_knight)) red_score += 120 * (i / 8);
    for(auto i : getBits(board.blue_red_knight)) red_score += 120 * (i / 8);

    //std::cout << "Blue score: " << blue_score << "\n";
    //std::cout << "Red score: " << red_score << "\n";
  
    int score = 0;
    if (board.turn) score =  blue_score - red_score;
    else score = red_score - blue_score;
    
    //
    //int turn = board.turn ? 1 : -1;
    
    // std::cout << "Score: " << score << " Score*turn: " << score * turn << " Turn: " << turn << "\n";



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

uint16_t Ai::negamax_handler(bitboard &board, int search_depth){
    int alpha = -1000;
    int beta = 1000;
    int best_value = -1000;
    std::uint16_t best_move = 0;
    Moves m;
    analyzed_nodes = 0;
    auto childNodes = m.generateMoves(board);

    for (auto child : childNodes){
        // make a move
        int value = -negamax(child, search_depth-1, -beta, -alpha, board, m);
        // undo the move
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

    analyzed_nodes++;
    if(depth == 0){
        return rate_board(board);
    }
    auto childNodes = m.generateMoves(board);
    int value = -1000;
    for(auto child : childNodes){
        // make a move
        value = std::max(value, -negamax(child, depth-1, -beta, -alpha, board, m));
        // undo the move
        alpha = std::max(alpha, value);
        if(alpha >= beta){
            break;
        }
    }
    return value;
}


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


uint16_t Ai::alphabeta_handler(bitboard &board, int search_depth){
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int best_value = INT_MIN;
    std::uint16_t best_move = 0;
    Moves m;
    analyzed_nodes = 0;
    bool max_player = board.turn;

    auto childNodes = m.generateMoves(board);
    for (auto child : childNodes){
        uint16_t move_made = m.updateBoard(board, child);
        int value = alphabetaMin(search_depth-1, alpha, beta, board, m, max_player);
        m.undoMove(board, child, move_made);
        if(value > best_value){
            best_value = value;
            best_move = child;
        }
        alpha = std::max(best_value, alpha);
        if(alpha >= beta){
            break;
        }
    }
    std::cout << "Best value: " << best_value << "\n";
    return best_move;
};



int Ai::alphabetaMax(int depth, int alpha, int beta, bitboard &board, Moves &m, bool max_player){

    analyzed_nodes++;
    if(depth == 0) return rate_board(board);

    for(auto child : m.generateMoves(board)){
        uint16_t move_made = m.updateBoard(board, child);
        int score = alphabetaMin(depth-1, alpha, beta, board, m, max_player);
        m.undoMove(board, child, move_made);
        if(score >= beta) return beta;
        alpha = std::max(alpha, score);
    }
    return alpha;
};

int Ai::alphabetaMin(int depth, int alpha, int beta, bitboard &board, Moves &m, bool max_player){

    analyzed_nodes++;
    if(depth == 0) return -rate_board(board);

    for(auto child : m.generateMoves(board)){
        uint16_t move_made = m.updateBoard(board, child);
        int score = alphabetaMax(depth-1, alpha, beta, board, m, max_player);
        m.undoMove(board, child, move_made);
        if(score <= alpha) return alpha;
        beta = std::min(beta, score);
    }
    return beta;
   
};

