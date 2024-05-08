#include "board.hpp"

Board::Board(std::string fen) {
    fenBitboard(fen);

}
void Board::fenBitboard(std::string fen){

    turn = (fen[fen.size()-1] == 'b');
    std::string fen_new = fen.substr(0, fen.size()-2);
    int pos = 0;
    
    for (auto i = 0; i < fen_new.length(); i++) {
        int cur = order[pos];
        char c = fen_new[i];

        if (isdigit(c)) {
            pos += std::stoi(std::string(1, c));
        } else if (c == 'b') {
            char temp = fen_new[++i];
            if (temp == 'b') {
                blue_blue_knight |= 1ull << order[pos];
            } else if (temp == 'r') {
                blue_red_knight |= 1ull << order[pos];
            } else if (temp == '0') {
                blue_pawns |= 1ull << order[pos];
            }
        } else if (c == 'r') {
            char temp = fen_new[++i];
            if (temp == 'b') {
                red_blue_knight |= 1ull << order[pos];
            } else if (temp == 'r') {
                red_red_knight |= 1ull << order[pos];
            } else if (temp == '0') {
                red_pawns |= 1ull << order[pos];
            }
        }
        pos++;
    }
}


void Board::printBitboard(){

    std::cout << "Red Pawns: " << red_pawns;
    for(int i = 0; i < 64; i++){
        if(i % 8 == 0){
            std::cout << std::endl;
        }
        std::cout << ((red_pawns >> i) & 1);
    }
    std::cout << std::endl << "Blue Pawns: " << blue_pawns ;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((blue_pawns >> i) & 1);
    }
    std::cout << std::endl << "Red Red Knight: " << red_red_knight;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((red_red_knight >> i) & 1);
    }
    std::cout << std::endl << "Red Blue Knight: " << red_blue_knight;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((red_blue_knight >> i) & 1);
    }
    std::cout << std::endl << "Blue Red Knight: " << blue_red_knight;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((blue_red_knight >> i) & 1);
    }
    std::cout << std::endl << "Blue Blue Knight: " << blue_blue_knight;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((blue_blue_knight >> i) & 1);
    }

    std::cout << std::endl;
}

void Board::print_blockedfields(){
    // print uint64_t blocked_fields in 8x8 
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << ((blocked_fields >> i) & 1);
        
    }
}

std::string Board::bitboardFen(){
    std::string fen = "";
    int counter = 0;
    
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0 && i != 0) {
            fen += addCounter(counter);
            fen += "/";
        }
        if ((red_pawns >> i) & 1) {
            fen += addCounter(counter);
            fen += "r0";
        } else if ((blue_pawns >> i) & 1) {
            fen += addCounter(counter);
            fen += "b0";
        } else if ((red_red_knight >> i) & 1) {
            fen += addCounter(counter);
            fen += "rr";
        } else if ((red_blue_knight >> i) & 1) {
            fen += addCounter(counter);
            fen += "rb";
        } else if ((blue_red_knight >> i) & 1) {
            fen += addCounter(counter);
            fen += "br";
        } else if ((blue_blue_knight >> i) & 1) {
            fen += addCounter(counter);
            fen += "bb";
        } else {
            counter++;
        }
    }

    fen += " ";
    fen += turn ? "b" : "r";
    return fen;
}

std::string Board::addCounter(int &counter){
    if(counter > 0){
        counter = 0;
        return std::to_string(counter);
    }
    return "";
};

