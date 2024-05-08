#include "board.hpp"

Board::Board(std::string fen) {
    fenBitboard(fen);
    // fenBoard(fen);
    // blocked_fields = 1000000100000000000000000000000000000000000000000000000010000001;
    // boardBitBoard();
}
/*
void Board::fenBoard(std::string fen){
    // Read Player
    turn = (fen[fen.size()-1] == 'b');
    std::string fen_new = fen.substr(0, fen.size()-2);

    for (std::string row : split(fen_new, '/')) {
        std::vector<std::string> boardRow;
        for (int i = 0; i < row.length(); i++) {
            char c = row[i];
            if (isdigit(c)) {
                for (int j = 0; j < std::stoi(std::string(1,c)); j++) {
                    boardRow.push_back("0");
                }
            } else {
                    boardRow.push_back(std::string(1, c) + row[i + 1]);
                i++;
            }
        }
        board.push_back(boardRow);
    }
    std::reverse(board.begin(), board.end());
    // Add 0s to [0][0] and [7][7], [0][7] and [7][0] to make it 8x8
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++){
            if (i == 0 && j == 0){
                board[i].insert(board[i].begin(), "0");
            } else if (i == 7 && j == 7){
                board[i].push_back("0");
            } else if (i == 0 && j == 7){
                board[i].push_back("0");
            } else if (i == 7 && j == 0){
                board[i].insert(board[i].begin(), "0");
            }
        }
    }
}


void boardBitboard(){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::string field = board[i][j];
            if (field == "r0"){
                red_pawns |= 1ull << (i * 8 + j);
            }
        }
    }
}
*/

void Board::fenBitboard(std::string fen){
    // First line is the last line in the board (8th row)

    turn = (fen[fen.size()-1] == 'b');
    std::string fen_new = fen.substr(0, fen.size()-2);
    int pos = 57;
    for (u_long i = 0; i < fen_new.length(); i++) {
        
        char c = fen_new[i];

        if(pos == 63){
            pos = 48;
        } else if(pos == 0){
            pos = 1;
        } else if(c == '/') {
            pos -= 16;
        } else if (isdigit(c)) {
            pos += std::stoi(std::string(1, c));
        } else if (c == 'b') {
            char temp = fen_new[++i];
            if (temp == 'b') {
                blue_blue_knight |= 1ull << pos;
            } else if (temp == 'r') {
                blue_red_knight |= 1ull << pos;
            } else if (temp == '0') {
                blue_pawns |= 1ull << pos;
            }
            pos++;
        } else if (c == 'r') {
            char temp = fen_new[++i];
            if (temp == 'b') {
                red_blue_knight |= 1ull << pos;
            } else if (temp == 'r') {
                red_red_knight |= 1ull << pos;
            } else if (temp == '0') {
                red_pawns |= 1ull << pos;
            }
            pos++;
        }
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

/* */

std::string Board::bitboardFen(){
    std::string fen = "";
    std::vector<int> order = {56, 57, 58, 59, 60, 61, 62, 63, 48, 49, 50, 51, 52, 53, 54, 55, 40, 41, 42, 43, 44, 45, 46, 47, 32, 33, 34, 35, 36, 37, 38, 39, 
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0 && i != 0) {
            fen += "/";
        }
        if ((red_pawns >> i) & 1) {
            fen += "r0";
        } else if ((blue_pawns >> i) & 1) {
            fen += "b0";
        } else if ((red_red_knight >> i) & 1) {
            fen += "rr";
        } else if ((red_blue_knight >> i) & 1) {
            fen += "rb";
        } else if ((blue_red_knight >> i) & 1) {
            fen += "br";
        } else if ((blue_blue_knight >> i) & 1) {
            fen += "bb";
        } else {
            if(!(i == 63 || i == 0 || i == 7 || i == 56)){
                fen += "0";
            }
        }
    }

    // reverse the string
    std::reverse(fen.begin(), fen.end());
    fen += " ";
    fen += turn ? "b" : "r";
    return fen;
}





/*
// Remove
std::string boardFen(){
    std::string fen = "";
    for (std::vector<std::string> row : board) {
        int count = 0;
        for (std::string field : row) {
            if (field == "0") {
                count++;
            } else {
                if (count > 0) {
                    fen += std::to_string(count);
                    count = 0;
                }
                fen += field;
            }
        }
        if (count > 0) {
            fen += std::to_string(count);
        }
        fen += "/";
    }
    fen += " ";
    fen += turn ? "b" : "r";
    return fen;
}
*/
