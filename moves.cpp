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
    // find fields that have red pieces on them
    
    // find fields that have blue pieces on them
    if(board.turn){ // generate moves for blue
        uint64_t pawn_diagonal = board.red_pawns | board.red_red_knight | board.blue_red_knight; // fields blue pawn can move to diagonally
        uint64_t pawn_not_diagonal = !(board.red_pawns | board.red_red_knight | board.red_blue_knight | board.blue_blue_knight | board.blue_red_knight | board.blocked_fields); // fields blue pawn can move to not diagonally
        // knight can move to any field that is not a blocked field
        moves 
        // generate moves for blue pawns

        




    } else { // generate moves for red
        uint64_t pawn_diagonal = board.blue_pawns | board.blue_blue_knight | board.red_blue_knight; // fields red pawn can move to diagonally
        uint64_t pawn_not_diagonal = !(board.blue_pawns | board.blue_red_knight | board.blue_blue_knight | board.red_blue_knight | board.red_red_knight | board.blocked_fields); // fields red pawn can move to not diagonally
        // knight can move to any field that is not a blocked field

    }
    return moves;
}


std::vector<uint16_t> Moves::pawnMoves(uint64_t pawn_diagonal, uint64_t pawn_not_diagonal, uint64_t pawn, bool turn){
    std::vector<uint16_t> ans;
    return ans;
}

std::vector<uint16_t> Moves::knightMoves(uint64_t knight, bool turn){
    std::vector<uint16_t> ans;
    if(turn){
        // find every blue knight and generate moves
         square_of_first_knight = pop_LSB(&knight_bb);
    

        
    } else {
        // red knight
    }
    return ans;
}

uint16_t Moves::generateMove(int start, int end, int type){
    return (end & 0x3f) | ((start & 0x3f) << 6) | ((type & 0x7) << 12);
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

/*
Moves are stored as an 16 bit Integer

bits:0-5 End Position {0,...,63} \ {0, 7, 56, 63}
bits 6-11 Start Position {0,...,63} \ {0, 7, 56, 63}
bits 12-14 Type of Piece
        000: blue_pawns
        100: red_pawns
        001: blue_blue_knights
        101: red_red_knights
        010: blue_red_knights
        110: red_blue_knigts
bit 15: Empty (Can be filled later)
*/

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