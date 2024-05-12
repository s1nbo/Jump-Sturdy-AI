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
        std::vector<uint16_t> knight_moves = knightMoves(board.blue_blue_knight, knight, board.turn, false);
        std::vector<uint16_t> knight_moves2 = knightMoves(board.red_blue_knight, knight, board.turn, true);
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
        std::vector<uint16_t> knight_moves = knightMoves(board.red_red_knight, knight, board.turn, false);
        std::vector<uint16_t> knight_moves2 = knightMoves(board.blue_red_knight, knight, board.turn, true);
        moves.insert(moves.end(), knight_moves.begin(), knight_moves.end());
        moves.insert(moves.end(), knight_moves2.begin(), knight_moves2.end());
    }
    return moves;
}

std::vector<uint16_t> Moves::pawnMovesDiagonal(uint64_t start, uint64_t valid, bool turn){
    std::vector<uint16_t> ans = {};
    std::vector<uint16_t> bits = getBits(start);
    std::vector<std::vector<uint16_t>> moves;

    if(turn){
        for (uint16_t bit : bits){
            std::array<uint16_t, 2> move = bluePawnDiagonalTable[bit];
            for(auto mov : move) if(valid >> mov & 1) ans.push_back(generateMove(bit, mov, 0));
        }
    } else {
        for (uint16_t bit : bits){
            std::array<uint16_t, 2> move = redPawnDiagonalTable[bit];
            for(auto mov : move) if(valid >> mov & 1) ans.push_back(generateMove(bit, mov, 4));
        }
    }
    return ans;
}

std::vector<uint16_t> Moves::pawnMoves(uint64_t start, uint64_t valid, bool turn){
    std::vector<uint16_t> ans;
    std::vector<uint16_t> bits = getBits(start);
    std::vector<std::vector<uint16_t>> moves;
   
    if (turn){
        for(uint16_t bit : bits){
            std::array<uint16_t, 3> move = bluePawnTable[bit];
            for(auto mov : move) if(valid >> mov & 1) ans.push_back(generateMove(bit, mov, 0));
        }
    } else {
        for(uint16_t bit : bits){
            std::array<uint16_t, 3> move = redPawnTable[bit];
            for(auto mov : move) if(valid >> mov & 1) ans.push_back(generateMove(bit, mov, 4));
        }
    }
    return ans;
}

std::vector<uint16_t> Moves::knightMoves(uint64_t start, uint64_t valid, bool turn, bool mixed){
    std::vector<uint16_t> ans;
    std::vector<uint16_t> bits = getBits(start);
    std::vector<std::vector<uint16_t>> moves;

    if(turn){
        for (uint16_t bit : bits){
            std::array<uint16_t, 4> move = blueKnightTable[bit];
            for(auto mov : move) if(valid >> mov & 1) ans.push_back(generateMove(bit, mov, 1+mixed));
        }
    } else {
        for (uint16_t bit : bits){
            std::array<uint16_t, 4> move = redKnightTable[bit];
            for(auto mov : move) if(valid >> mov & 1) ans.push_back(generateMove(bit, mov, 5+mixed));
        }
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
    // Chess board format
    std::vector<std::string> format = {
        "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
        "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
        "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
        "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
        "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
        "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
        
    };
    std::vector<std::string> figures = {
        "blue_pawns", "blue_blue_knights", "red_blue_knight", "error", "red_pawns", "red_red_knights", "red_blue_knights"
    };
    
    for(auto move : moves){
        int start = (move >> 6) & 0x3f;
        int end = move & 0x3f;
        int figure = (move >> 13) & 0x7;
        std::cout << format[start] << " -> " << format[end] << " Type: " << figures[figure] << std::endl;
    }
    
}