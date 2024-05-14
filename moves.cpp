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
    moves.reserve(64);
    
    if(board.turn){ // generate moves for blue
        uint64_t opponent = board.red_pawns | board.red_red_knight | board.blue_red_knight; // fields blue pawn can move to diagonally
        uint64_t pawn_not_diagonal = ~(board.red_pawns | board.red_red_knight | board.red_blue_knight | board.blue_blue_knight | board.blue_red_knight | board.blocked_fields); // fields blue pawn can move to not diagonally
        uint64_t knight = ~(board.blue_blue_knight | board.red_blue_knight | board.blocked_fields); // knight can move to any field that is not a blocked field or another knight
        
        std::vector<uint16_t> pawn_moves = pawnMoves(board.blue_pawns, pawn_not_diagonal, opponent, board.turn); // generate moves for blue pawns
        std::vector<uint16_t> knight_moves = knightMoves(board.blue_blue_knight, board.red_blue_knight, knight, opponent, board.turn); // generate moves for blue knights
        
        moves.insert(moves.end(), pawn_moves.begin(), pawn_moves.end());
        moves.insert(moves.end(), knight_moves.begin(), knight_moves.end());

    } else { // generate moves for red
        uint64_t opponent = board.blue_pawns | board.blue_blue_knight | board.red_blue_knight; // fields red pawn can move to diagonally
        uint64_t pawn_not_diagonal = ~(board.blue_pawns | board.blue_red_knight | board.blue_blue_knight | board.red_blue_knight | board.red_red_knight | board.blocked_fields); // fields red pawn can move to not diagonally
        uint64_t knight = ~(board.red_red_knight | board.blue_red_knight | board.blocked_fields); // knight can move to any field that is not a blocked field or another knight
        
        std::vector<uint16_t> pawn_moves = pawnMoves(board.red_pawns, pawn_not_diagonal, opponent, board.turn); // generate moves for red pawns
        std::vector<uint16_t> knight_moves = knightMoves(board.red_red_knight, board.blue_red_knight, knight, opponent, board.turn); // generate moves for red knights

        moves.insert(moves.end(), pawn_moves.begin(), pawn_moves.end());
        moves.insert(moves.end(), knight_moves.begin(), knight_moves.end());
    }
    return moves;
}

std::vector<uint16_t> Moves::pawnMoves(uint64_t start, uint64_t valid, uint64_t diagonal, bool turn){
    std::vector<uint16_t> ans;
    ans.reserve(64);
    std::vector<uint16_t> bits = getBits(start);
    std::vector<std::vector<uint16_t>> moves;
    moves.reserve(64);
   
    if (turn){
        for(uint16_t bit : bits){
            std::array<uint16_t, 3> move = bluePawnTable[bit];
            std::array<uint16_t, 2> move_diagonal = bluePawnDiagonalTable[bit];
            for(auto mov : move) if(valid >> mov & 1) ans.push_back(generateMove(bit, mov, 0, 0));
            for(auto mov : move_diagonal) if(diagonal >> mov & 1) ans.push_back(generateMove(bit, mov, 0, 1));
        }
    } else {
        for(uint16_t bit : bits){
            std::array<uint16_t, 3> move = redPawnTable[bit];
            std::array<uint16_t, 2> move_diagonal = redPawnDiagonalTable[bit];
            for(auto mov : move) if(valid >> mov & 1) ans.push_back(generateMove(bit, mov, 4, 0));
            for(auto mov : move_diagonal) if(diagonal >> mov & 1) ans.push_back(generateMove(bit, mov, 4, 1));
        }
    }
    return ans;
}

std::vector<uint16_t> Moves::knightMoves(uint64_t start, uint64_t mixed_start, uint64_t valid, uint64_t opponent, bool turn){
    std::vector<uint16_t> ans;
    ans.reserve(64);
    std::vector<uint16_t> bits = getBits(start);
    std::vector<uint16_t> mixed_bits = getBits(mixed_start);
    std::vector<std::vector<uint16_t>> moves;
    moves.reserve(64);
    if(turn){
        for (uint16_t bit : bits){
            std::array<uint16_t, 4> move = blueKnightTable[bit];
            for(auto mov : move){
                if(valid >> mov & 1) {
                    if (opponent >> mov & 1) ans.push_back(generateMove(bit, mov, 1, 1));
                    else ans.push_back(generateMove(bit, mov, 1, 0));
                }
            }
        }
        for (uint16_t bit : mixed_bits){
            std::array<uint16_t, 4> move = blueKnightTable[bit];
            for(auto mov : move){
                if(valid >> mov & 1) {
                    if (opponent >> mov & 1) ans.push_back(generateMove(bit, mov, 2, 1));
                    else ans.push_back(generateMove(bit, mov, 2, 0));
                }
            }
        }
    } else {
        for (uint16_t bit : bits){
            std::array<uint16_t, 4> move = redKnightTable[bit];
            for(auto mov : move){
                if(valid >> mov & 1) {
                    if (opponent >> mov & 1) ans.push_back(generateMove(bit, mov, 5, 1));
                    else ans.push_back(generateMove(bit, mov, 5, 0));
                }
            }
        }
        for (uint16_t bit : mixed_bits){
            std::array<uint16_t, 4> move = redKnightTable[bit];
            for(auto mov : move){
                if(valid >> mov & 1) {
                    if (opponent >> mov & 1) ans.push_back(generateMove(bit, mov, 6, 1));
                    else ans.push_back(generateMove(bit, mov, 6, 0));
                }
            }
        }
    }
    return ans;
}

// Save move in 16 bit integer
uint16_t Moves::generateMove(uint16_t start, uint16_t end, uint16_t type, bool take){
    // Format: 0-5 end, 6-11 start, 12-14 type, 15 take
    return ((end & 0x3f) | ((start & 0x3f) << 6) | ((type & 0x7) << 12) | ((take & 0x1) << 15));
}

// return every 1 bit in bitboard fast way
std::vector<uint16_t> Moves::getBits(uint64_t board){
    std::vector<uint16_t> ans;
    ans.reserve(64);
    while(board){
        uint16_t bit = __builtin_ctzll(board);
        ans.push_back(bit);
        board &= board - 1;
    }
    return ans;
}

// TODO: update knight
/*
When a knight moves, it splits into two pawns.
The first pawn stays on the field the knight was before.
The second pawn moves to the field the knight moves to.



*/
bitboard Moves::updateBoard(bitboard board, uint16_t move){
    bitboard new_board = board;

    // update move on new board
    // Read bits 12-14
    uint16_t type = (move >> 12) & 0x7;
    // Read bits 6-11
    uint16_t start = (move >> 6) & 0x3f;
    // Read bits 0-5
    uint16_t end = move & 0x3f;
    // take
    bool take = (move >> 15) & 0x1;


    switch (type)
    {
    case 0: // blue_pawns
        new_board.blue_pawns &= ~(1ull << start);
        if (take){
            if(new_board.red_pawns >> end & 1){
                new_board.red_pawns &= ~(1ull << end);
                new_board.blue_pawns |= (1ull << end);
            } else if(new_board.red_red_knight >> end & 1){
                new_board.red_red_knight &= ~(1ull << end);
                new_board.red_blue_knight |= (1ull << end);
            } else if(new_board.blue_red_knight >> end & 1){
                new_board.blue_red_knight &= ~(1ull << end);
                new_board.blue_blue_knight |= (1ull << end);
            }
        } else {
            if(new_board.blue_pawns >> end & 1){
                new_board.blue_pawns &= ~(1ull << end);
                new_board.blue_blue_knight |= (1ull << end);
            } else {
                new_board.blue_pawns |= (1ull << end);
            }
        }
        break;
    case 1: // blue_blue_knights
        new_board.blue_blue_knight &= ~(1ull << start);
        new_board.blue_pawns |= (1ull << start);
        if (take){
            if(new_board.red_pawns >> end & 1){
                new_board.red_pawns &= ~(1ull << end);
                new_board.blue_pawns |= (1ull << end);
            } else if(new_board.red_red_knight >> end & 1){
                new_board.red_red_knight &= ~(1ull << end);
                new_board.red_blue_knight |= (1ull << end);
            } else if(new_board.blue_red_knight >> end & 1){
                new_board.blue_red_knight &= ~(1ull << end);
                new_board.blue_blue_knight |= (1ull << end);
            }
        } else {     
            if(new_board.blue_pawns >> end & 1){      
                new_board.blue_pawns &= ~(1ull << end);
                new_board.blue_blue_knight |= (1ull << end);
            } else {
                new_board.blue_pawns |= (1ull << end);
            }
        }
        break;
    case 2: // red_blue_knight
        new_board.red_blue_knight &= ~(1ull << start);
        new_board.red_pawns |= (1ull << start);
        if (take){
            if(new_board.red_pawns >> end & 1){
                new_board.red_pawns &= ~(1ull << end);
                new_board.blue_pawns |= (1ull << end);
            } else if(new_board.red_red_knight >> end & 1){
                new_board.red_red_knight &= ~(1ull << end);
                new_board.red_blue_knight |= (1ull << end);
            } else if(new_board.blue_red_knight >> end & 1){
                new_board.blue_red_knight &= ~(1ull << end);
                new_board.blue_blue_knight |= (1ull << end);
            }
        } else {
            if(new_board.blue_pawns >> end & 1){
                new_board.blue_pawns &= ~(1ull << end);
                new_board.blue_blue_knight |= (1ull << end);
            } else {
                new_board.blue_pawns |= (1ull << end);
            }
        }
        break;
    case 4: // red_pawns
        new_board.red_pawns &= ~(1ull << start);
        if (take){
            if(new_board.blue_pawns >> end & 1){
                new_board.blue_pawns &= ~(1ull << end);
                new_board.red_pawns |= (1ull << end);
            } else if(new_board.blue_blue_knight >> end & 1){
                new_board.blue_blue_knight &= ~(1ull << end);
                new_board.blue_red_knight |= (1ull << end);
            } else if(new_board.red_blue_knight >> end & 1){
                new_board.red_blue_knight &= ~(1ull << end);
                new_board.red_red_knight |= (1ull << end);
            }
        } else {
            if(new_board.red_pawns >> end & 1){
                new_board.red_pawns &= ~(1ull << end);
                new_board.red_red_knight |= (1ull << end);
            } else {
                new_board.red_pawns |= (1ull << end);
            }
        }
        break;
    case 5: // red_red_knights
        new_board.red_red_knight &= ~(1ull << start);
        new_board.red_pawns |= (1ull << start);
        if (take){
            if(new_board.blue_pawns >> end & 1){
                new_board.blue_pawns &= ~(1ull << end);
                new_board.red_pawns |= (1ull << end);
            } else if(new_board.blue_blue_knight >> end & 1){
                new_board.blue_blue_knight &= ~(1ull << end);
                new_board.blue_red_knight |= (1ull << end);
            } else if(new_board.red_blue_knight >> end & 1){
                new_board.red_blue_knight &= ~(1ull << end);
                new_board.red_red_knight |= (1ull << end);
            }
        } else {
            if(new_board.red_pawns >> end & 1){
                new_board.red_pawns &= ~(1ull << end);
                new_board.red_red_knight |= (1ull << end);
            } else {        
                new_board.red_pawns |= (1ull << end);
            }
        }
        break;
    case 6: // blue_red_knights
        new_board.blue_red_knight &= ~(1ull << start);
        new_board.blue_pawns |= (1ull << start);
        if (take){
            if(new_board.blue_pawns >> end & 1){
                new_board.blue_pawns &= ~(1ull << end);
                new_board.red_pawns |= (1ull << end);
            } else if(new_board.blue_blue_knight >> end & 1){
                new_board.blue_blue_knight &= ~(1ull << end);
                new_board.blue_red_knight |= (1ull << end);
            } else if(new_board.red_blue_knight >> end & 1){
                new_board.red_blue_knight &= ~(1ull << end);
                new_board.red_red_knight |= (1ull << end);
            }
        } else {
            if(new_board.red_pawns >> end & 1){
                new_board.red_pawns &= ~(1ull << end);   
                new_board.red_red_knight |= (1ull << end);
            } else {
                new_board.red_pawns |= (1ull << end);
            }
        }
        break;
    default: // error
        break;
    }

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
        int figure = (move >> 12) & 0x7;
        int take = (move >> 15) & 0x1;
        std::cout << format[start] << " -> " << format[end] << " Type: " << figures[figure] << " Take: " << take << std::endl;
    }
    
}