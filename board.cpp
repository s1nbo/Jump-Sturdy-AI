#include "board.hpp"

Board::Board(std::string fen, bitboard &board) {
    fenBitboard(fen, board);

}
void Board::fenBitboard(std::string fen, bitboard &board){

    board.turn = (fen[fen.size()-1] == 'b');
    std::string fen_new = fen.substr(0, fen.size()-2);
    int pos = 0;
    
    for (size_t i = 0; i < fen_new.length(); i++) {
        char c = fen_new[i];

        if (isdigit(c)) {
            pos += std::stoi(std::string(1, c));
        } else if (c == 'b') {
            char temp = fen_new[++i];
            if (temp == 'b') {
                board.blue_blue_knight |= 1ull << order[pos];
            } else if (temp == 'r') {
                board.blue_red_knight |= 1ull << order[pos];
            } else if (temp == '0') {
                board.blue_pawns |= 1ull << order[pos];
            }
            pos++;
        } else if (c == 'r') {
            char temp = fen_new[++i];
            if (temp == 'b') {
                board.red_blue_knight |= 1ull << order[pos];
            } else if (temp == 'r') {
                board.red_red_knight |= 1ull << order[pos];
            } else if (temp == '0') {
                board.red_pawns |= 1ull << order[pos];
            }
            pos++;
        }
    }
}


void Board::printBitboard(bitboard board){

    std::cout << "Red Pawns: " <<  board.red_pawns;
    for(int i = 0; i < 64; i++){
        if(i % 8 == 0){
            std::cout << std::endl;
        }
        std::cout << ((board.red_pawns >> i) & 1);
    }
    std::cout << std::endl << "Blue Pawns: " << board.blue_pawns ;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((board.blue_pawns >> i) & 1);
    }
    std::cout << std::endl << "Red Red Knight: " << board.red_red_knight;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((board.red_red_knight >> i) & 1);
    }
    std::cout << std::endl << "Red Blue Knight: " << board.red_blue_knight;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((board.red_blue_knight >> i) & 1);
    }
    std::cout << std::endl << "Blue Red Knight: " << board.blue_red_knight;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((board.blue_red_knight >> i) & 1);
    }
    std::cout << std::endl << "Blue Blue Knight: " << board.blue_blue_knight;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((board.blue_blue_knight >> i) & 1);
    }

    std::cout << std::endl;
}

void Board::print_blockedfields(bitboard &board){
    // print uint64_t blocked_fields in 8x8 
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((board.blocked_fields >> i) & 1);
        
    }
}

std::string Board::bitboardFen(bitboard &board){
    std::string fen = "";
    int counter = 0;
    
    for (auto i : order) {
        if (i % 8 == 0 || i == 1) {
            fen += addCounter(counter);
            fen += "/";
        }
        if ((board.red_pawns >> i) & 1) {
            fen += addCounter(counter);
            fen += "r0";
        } else if ((board.blue_pawns >> i) & 1) {
            fen += addCounter(counter);
            fen += "b0";
        } else if ((board.red_red_knight >> i) & 1) {
            fen += addCounter(counter);
            fen += "rr";
        } else if ((board.red_blue_knight >> i) & 1) {
            fen += addCounter(counter);
            fen += "rb";
        } else if ((board.blue_red_knight >> i) & 1) {
            fen += addCounter(counter);
            fen += "br";
        } else if ((board.blue_blue_knight >> i) & 1) {
            fen += addCounter(counter);
            fen += "bb";
        } else {
            counter++;
        }
    }
    fen += addCounter(counter);
    fen += " ";
    fen += board.turn ? "b" : "r";
    return fen;
}

std::string Board::addCounter(int &counter){
    if(counter > 0){
        int temp = counter;
        counter = 0;
        return std::to_string(temp);
        
    }
    return "";
};

