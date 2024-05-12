#include "moves.hpp"


Moves::Moves(){}

bool Moves::gameOver(bitboard &board, std::vector<uint16_t> moves){
    uint64_t red = board.red_pawns | board.red_red_knight | board.red_blue_knight;
    uint64_t blue = board.blue_pawns |board.red_blue_knight | board.blue_blue_knight;
    // if one player has piece on the last row
    if(red & 0xff00000000000000 || blue & 0xff){
        return true;
    }
    if(moves.size() == 0){
        return true;
    }
    return false;
}

std::vector<uint16_t> Moves::generateMoves(bitboard &board){
    std::vector<uint16_t> moves;
    if(board.turn){ // generate moves for blue
        uint64_t pawn_diagonal = board.red_pawns | board.red_red_knight | board.blue_red_knight; // fields blue pawn can move to diagonally
        uint64_t pawn_not_diagonal = ~(board.red_pawns | board.red_red_knight | board.red_blue_knight | board.blue_blue_knight | board.blue_red_knight | board.blocked_fields); // fields blue pawn can move to not diagonally
        uint64_t knight = ~(board.blue_blue_knight | board.red_blue_knight | board.blocked_fields); // knight can move to any field that is not a blocked field or another knight
        
        // generate moves for blue pawns
        std::vector<uint16_t> pawn_diagonal_moves = pawnMovesDiagonal(board.blue_pawns, pawn_diagonal, board.turn);
        std::vector<uint16_t> pawn_not_diagonal_moves = pawnMoves(board.blue_pawns, pawn_not_diagonal, board.turn);
        moves.insert(moves.end(), pawn_diagonal_moves.begin(), pawn_diagonal_moves.end());
        moves.insert(moves.end(), pawn_not_diagonal_moves.begin(), pawn_not_diagonal_moves.end());

        // generate moves for blue knights
        std::vector<uint16_t> knight_moves = knightMoves(board.blue_blue_knight, knight, board.turn);
        std::vector<uint16_t> knight_moves2 = knightMoves(board.red_blue_knight, knight, board.turn);
        moves.insert(moves.end(), knight_moves.begin(), knight_moves.end());
        moves.insert(moves.end(), knight_moves2.begin(), knight_moves2.end());

    } else { // generate moves for red
        uint64_t pawn_diagonal = board.blue_pawns | board.blue_blue_knight | board.red_blue_knight; // fields red pawn can move to diagonally
        uint64_t pawn_not_diagonal = ~(board.blue_pawns | board.blue_red_knight | board.blue_blue_knight | board.red_blue_knight | board.red_red_knight | board.blocked_fields); // fields red pawn can move to not diagonally
        uint64_t knight = ~(board.red_red_knight | board.blue_red_knight | board.blocked_fields); // knight can move to any field that is not a blocked field or another knight
        
        // generate moves for red pawns
        std::vector<uint16_t> pawn_diagonal_moves = pawnMovesDiagonal(board.red_pawns, pawn_diagonal, board.turn);
        std::vector<uint16_t> pawn_not_diagonal_moves = pawnMoves(board.red_pawns, pawn_not_diagonal, board.turn);
        
        moves.insert(moves.end(), pawn_diagonal_moves.begin(), pawn_diagonal_moves.end());
        moves.insert(moves.end(), pawn_not_diagonal_moves.begin(), pawn_not_diagonal_moves.end());

        // generate moves for red knights
        std::vector<uint16_t> knight_moves = knightMoves(board.red_red_knight, knight, board.turn);
        std::vector<uint16_t> knight_moves2 = knightMoves(board.blue_red_knight, knight, board.turn);
        moves.insert(moves.end(), knight_moves.begin(), knight_moves.end());
        moves.insert(moves.end(), knight_moves2.begin(), knight_moves2.end());
    }
    return moves;
}

std::vector<uint16_t> Moves::pawnMovesDiagonal(uint64_t start, uint64_t valid, bool turn){
    
    std::vector<uint16_t> ans = {};
    /*
    std::vector<uint64_t> bits = getBits(start);
    std::vector<uint16_t> moves;
    if(turn){
        for(uint16_t bit : bits){
            uint16_t move_left = (bit << 7) & valid;
            uint16_t move_right = (bit << 9) & valid;
            if(move_left) moves.push_back(move_left);
            if(move_right) moves.push_back(move_right);
        }
        for(auto move : moves) ans.push_back(generateMove(start, move, 0));
    } else {
        for(uint16_t bit : bits){
            uint16_t move_left = (bit >> 7) & valid;
            uint16_t move_right = (bit >> 9) & valid;
            if(move_left) moves.push_back(move_left);
            if(move_right) moves.push_back(move_right);
        }
        for(auto move : moves) ans.push_back(generateMove(start, move, 4));
    }
    */
    return ans;
    
}


std::vector<uint16_t> Moves::pawnMoves(uint64_t start, uint64_t valid, bool turn){
    std::vector<uint16_t> ans;
    std::vector<uint16_t> bits = getBits(start);
    std::vector<std::vector<uint16_t>> moves;
    
    uint16_t pawn = turn ? 0 : 4;
    uint16_t sign = turn ? -1 : 1;

    for(uint16_t bit : bits){
        uint16_t move = bit+8*sign;
        uint16_t move_left = bit-1;
        uint16_t move_right = bit+1; 
        
        if(move < 64 && move > 0 && ((valid >> move) & 1)) moves.push_back({move, bit});
        if(move_left < 64 && move_left > 0 && ((valid >> move_left) & 1)) moves.push_back({move_left, bit});
        if(move_right < 64 && move_right > 0 && ((valid >> move_right) & 1)) moves.push_back({move_right, bit});
    }
    for(auto move : moves) ans.push_back(generateMove(move[1], move[0], pawn));
    return ans;
}

/*
std::vector<uint16_t> Moves::pawnMoves(uint64_t start, uint64_t valid, bool turn){
    std::vector<uint16_t> ans;
    std::vector<uint16_t> bits = getBits(start); // every pawn position
    std::vector<std::vector<uint16_t>> moves;
    if(turn){
       return ans;
    } else {
        for(uint16_t bit : bits){
            // move one field forward
            uint16_t move = bit+8;
            if(move < 64 && move > 0 && ((valid >> move) & 1)){
                moves.push_back({move, bit});
            }

            uint16_t move_left = bit-1;
            // check if move_left bit is 0 or 1 in valid
            if(move_left < 64 && move_left > 0 && ((valid >> move_left) & 1)){
                moves.push_back({move_left, bit});
               

            }
            uint16_t move_right = bit+1;
            if(move_right < 64 && move_right > 0 && ((valid >> move_right) & 1)){
                moves.push_back({move_right, bit});
               
            }
        }
        for(auto move : moves) ans.push_back(generateMove(move[1], move[0], 4));
    }
    return ans;
}
*/

std::vector<uint16_t> Moves::knightMoves(uint64_t start, uint64_t valid, bool turn){
    std::vector<uint16_t> ans;
    std::vector<uint16_t> bits = getBits(start); // every knight position
    std::vector<uint16_t> moves;
    if(turn){
        for(uint16_t bit : bits){
            uint16_t move_up_left = (bit << 15) & valid;
            uint16_t move_up_right = (bit << 17) & valid;
            uint16_t move_left_up = (bit << 6) & valid;
            uint16_t move_right_up = (bit << 10) & valid;
            if(move_up_left) moves.push_back(move_up_left);
            if(move_up_right) moves.push_back(move_up_right);
            if(move_left_up) moves.push_back(move_left_up);
            if(move_right_up) moves.push_back(move_right_up);
        }
        for(auto move : moves) ans.push_back(generateMove(start, move, 1));
    } else {
        for(uint16_t bit : bits){
            uint16_t move_down_left = (bit >> 15) & valid;
            uint16_t move_down_right = (bit >> 17) & valid;
            uint16_t move_left_down = (bit >> 6) & valid;
            uint16_t move_right_down = (bit >> 10) & valid;
            if(move_down_left) moves.push_back(move_down_left);
            if(move_down_right) moves.push_back(move_down_right);
            if(move_left_down) moves.push_back(move_left_down);
            if(move_right_down) moves.push_back(move_right_down);
        }
        for(auto move : moves) ans.push_back(generateMove(start, move, 5));
    }
    return ans;
}

uint16_t Moves::generateMove(uint16_t start, uint16_t end, uint16_t type){
    // Format: 0-5 end, 6-11 start, 12-14 type, 15 = 0
    return (end & 0x3f) | ((start & 0x3f) << 6) | ((type & 0x7) << 13) | (0 << 15);
}

// return every 1 bit in bitboard fast way - This Works
std::vector<uint16_t> Moves::getBits(uint64_t board){
    std::vector<uint16_t> ans;
    while(board){
        uint16_t bit = __builtin_ctzll(board);
        ans.push_back(bit);
        board &= board - 1;
    }
    std::cout << "Bits: " << ans.size() << std::endl;
    return ans;
}

// TODO: update board
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
    std::cout << "Number of Moves: " << moves.size() << std::endl;
    // print in A1 - H8 format
    for(auto move : moves){
        int start = (move >> 6) & 0x3f;
        int end = move & 0x3f;
        int figure = (move >> 13) & 0x7;
        std::cout << "Move: " << start << " -> " << end << " Type: " << figure << std::endl;
    }
}