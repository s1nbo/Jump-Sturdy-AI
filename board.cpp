#include "board.hpp"

Board::Board(std::string fen) {
    fenBoard(fen);
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
    turn = (fen[fen.size()-1] == 'b');
    std::string fen_new = fen.substr(0, fen.size()-2);

    for (std::string row : split(fen_new, '/')) {
        for (u_long i = 0; i < row.length(); i++) {    
        }
    }
}


void Board::printBitBoard(){
    std::cout << "Red Pawns: " << red_pawns << std::endl;
    for(int i = 0; i < 64; i++){
        if(i % 8 == 0){
            std::cout << std::endl;
        }
        std::cout << ((red_pawns >> i) & 1);
    }
}


void Board::printBoard(){
    for (std::vector<std::string> row : board) {
        for (std::string field : row) {
            std::cout << field << " ";
        }
        std::cout << std::endl;
    }
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

std::vector<std::string> Board::split(std::string str, char delimiter) {
    std::vector<std::string> ans;
    std::string temp = "";
    for (u_long i = 0; i < str.length(); i++) {
        if (str[i] == delimiter) {
            ans.push_back(temp);
            temp = "";
        } else {
            temp += str[i];
        }
    }
    ans.push_back(temp);
    return ans;
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
