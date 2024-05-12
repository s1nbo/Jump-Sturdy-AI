#include "moves.hpp"


Moves::Moves(){}


bool Moves::gameOver(bitboard &board){
    uint64_t red = board.red_pawns | board.red_red_knight | board.red_blue_knight;
    uint64_t blue = board.blue_pawns |board.red_blue_knight | board.blue_blue_knight;
    // if one player has piece on the last row
    if(red & 0xff00000000000000 || blue & 0xff){
        return true;
    }
    // if one player has no moves left
    if(moves[0] == 0){
        generateMoves(board);
    }
    if(moves.size() == 0){
        return true;
    }
    return false;
}

std::vector<uint16_t> Moves::generateMoves(bitboard &board){
    // reset moves vector
    moves.clear();

    if(board.turn){ // generate moves for blue
        uint64_t pawn_diagonal = board.red_pawns | board.red_red_knight | board.blue_red_knight; // fields blue pawn can move to diagonally
        uint64_t pawn_not_diagonal = !(board.red_pawns | board.red_red_knight | board.red_blue_knight | board.blue_blue_knight | board.blue_red_knight | board.blocked_fields); // fields blue pawn can move to not diagonally
        uint64_t knight = board.blue_blue_knight | board.red_blue_knight; // knight can move to any field that is not a blocked field or another knight
        
        // generate moves for blue pawns

        // generate moves for blue knights

        




    } else { // generate moves for red
        uint64_t pawn_diagonal = board.blue_pawns | board.blue_blue_knight | board.red_blue_knight; // fields red pawn can move to diagonally
        uint64_t pawn_not_diagonal = !(board.blue_pawns | board.blue_red_knight | board.blue_blue_knight | board.red_blue_knight | board.red_red_knight | board.blocked_fields); // fields red pawn can move to not diagonally
        uint64_t knight = board.red_red_knight | board.blue_red_knight | board.blocked_fields; // knight can move to any field that is not a blocked field or another knight

        // generate moves for red pawns

        // generate moves for red knights

    }
    return moves;
}

std::vector<uint16_t> Moves::pawnMovesDiagonal(uint64_t start, uint64_t valid, bool turn){
    std::vector<uint16_t> ans;
    if(turn){
        std::vector<int> bits = getBits(start); // every pawn position
        std::vector<uint64_t> moves;
        for(auto bit : bits){
            uint64_t move_left = (start << 7) & valid;
            uint64_t move_right = (start << 9) & valid;
            if(move_left) moves.push_back(move_left);
            if(move_right) moves.push_back(move_right);
        }
        for(auto move : moves) ans.push_back(generateMove(start, move, 0));
    } else {
        std::vector<int> bits = getBits(start); // every pawn position
        std::vector<uint64_t> moves;
        for(auto bit : bits){
            uint64_t move_left = (start >> 7) & valid;
            uint64_t move_right = (start >> 9) & valid;
            if(move_left) moves.push_back(move_left);
            if(move_right) moves.push_back(move_right);
        }
        for(auto move : moves) ans.push_back(generateMove(start, move, 4));
    }
    return ans;
}

std::vector<uint16_t> Moves::pawnMoves(uint64_t start, uint64_t blocked, bool turn){
    std::vector<uint16_t> ans;
    if(turn){
        std::vector<int> bits = getBits(start); // every pawn position
        std::vector<uint64_t> moves;
        for(auto bit : bits){
            uint64_t move = (start << 8) & ~blocked; // move one field forward
            uint64_t move_left = (start << 1) & ~blocked; // move one field left
            uint64_t move_right = (start >> 1) & ~blocked; // move one field right
            if(move) moves.push_back(move);
            if(move_left) moves.push_back(move_left);
            if(move_right) moves.push_back(move_right);
        }
        for(auto move : moves) ans.push_back(generateMove(start, move, 0));
    } else {
        std::vector<int> bits = getBits(start); // every pawn position
        std::vector<uint64_t> moves;
        for(auto bit : bits){
            uint64_t move = (start >> 8) & ~blocked;
            uint64_t move_left = (start << 1) & ~blocked; // move one field left
            uint64_t move_right = (start >> 1) & ~blocked; // move one field right
            if(move) moves.push_back(move);
            if(move_left) moves.push_back(move_left);
            if(move_right) moves.push_back(move_right);
        }
        for(auto move : moves) ans.push_back(generateMove(start, move, 4));
    } 
    return ans;
}

std::vector<uint16_t> Moves::knightMoves(uint64_t start, uint64_t blocked, bool turn){
    std::vector<uint16_t> ans;
    if(turn){
        // can only go up and left or up and right
        // left and right and up
        // How many moves in total? 4
        std::vector<int> bits = getBits(start); // every knight position
        std::vector<uint64_t> moves;
        for(auto bit : bits){
            uint64_t move_up_left = (start << 15) & ~blocked;
            uint64_t move_up_right = (start << 17) & ~blocked;
            uint64_t move_left_up = (start << 6) & ~blocked;
            uint64_t move_right_up = (start << 10) & ~blocked;
            if(move_up_left) moves.push_back(move_up_left);
            if(move_up_right) moves.push_back(move_up_right);
            if(move_left_up) moves.push_back(move_left_up);
            if(move_right_up) moves.push_back(move_right_up);
        }
        for(auto move : moves) ans.push_back(generateMove(start, move, 1));
    } else {
        // can only go down and left or down and right
        // left and right and down
        // How many moves in total? 4
        std::vector<int> bits = getBits(start); // every knight position
        std::vector<uint64_t> moves;
        for(auto bit : bits){
            uint64_t move_down_left = (start >> 15) & ~blocked;
            uint64_t move_down_right = (start >> 17) & ~blocked;
            uint64_t move_left_down = (start >> 6) & ~blocked;
            uint64_t move_right_down = (start >> 10) & ~blocked;
            if(move_down_left) moves.push_back(move_down_left);
            if(move_down_right) moves.push_back(move_down_right);
            if(move_left_down) moves.push_back(move_left_down);
            if(move_right_down) moves.push_back(move_right_down);
        }
        for(auto move : moves) ans.push_back(generateMove(start, move, 5));
    }
    return ans;
}

uint16_t Moves::generateMove(int start, int end, int type){
    return (end & 0x3f) | ((start & 0x3f) << 6) | ((type & 0x7) << 12);
}

// return every 1 bit in bitboard fast way
std::vector<int> Moves::getBits(uint64_t board){
    std::vector<int> ans;
    while(board){
        int bit = __builtin_ctzll(board);
        ans.push_back(bit);
        board &= board - 1;
    }
    return ans;
}


bitboard Moves::updateBoard(bitboard board, uint16_t move){
    // create new board
    bitboard new_board = board;

    // update move on new board
    // Read bits 12-14
    int type = (move >> 12) & 0x7;
    // Read bits 6-11
    int start = (move >> 6) & 0x3f;
    // Read bits 0-5
    int end = move & 0x3f;

    
    
    switch (type)
    {
    case 0:
        // blue_pawns
        new_board.blue_pawns &= ~(1ull << start);
        new_board.blue_pawns |= (1ull << end);
        break;
    case 1:
        // blue_blue_knights
        new_board.blue_blue_knight &= ~(1ull << start);
        new_board.blue_blue_knight |= (1ull << end);
        break;
    case 2:
        // blue_red_knights
        new_board.blue_red_knight &= ~(1ull << start);
        new_board.blue_red_knight |= (1ull << end);
        break;
    case 4:
        // red_pawns
        new_board.red_pawns &= ~(1ull << start);
        new_board.red_pawns |= (1ull << end);
        break;
    case 5:
        // red_red_knights
        new_board.red_red_knight &= ~(1ull << start);
        new_board.red_red_knight |= (1ull << end);
        break;
    case 6:
        // red_blue_knights
        new_board.red_blue_knight &= ~(1ull << start);
        new_board.red_blue_knight |= (1ull << end);
        break;
    default:
        break;
    }

    // update turn
    new_board.turn = !board.turn;
    return new_board;
}

void Moves::printMoves(std::vector<uint16_t> moves){
    for(auto move : moves){
        std::cout << "Move: " << move << std::endl;
    }
    std::cout << "Number of Moves: " << moves.size() << std::endl;
    // print in A1 - H8 format
    for(auto move : moves){
        int start = (move >> 6) & 0x3f;
        int end = move & 0x3f;
        std::cout << "Move: " << start << " -> " << end << std::endl;
    }
}