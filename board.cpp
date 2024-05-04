#include "board.hpp"

class Board {
public:
    std::bitset<64> blue_pawns;
    std::bitset<64> red_pawns;
    std::bitset<64> blue_blue_knight;
    std::bitset<64> red_red_knight;
    std::bitset<64> red_blue_knight;
    std::bitset<64> blue_red_knight;
    // the 4 corners
     std::bitset<64> blocked_fields;
    
    bool turn;
    std::vector<std::vector<std::string>> board;

    Board(std::string fen) {
        fenBoard(fen);
        blocked_fields = 1000000100000000000000000000000000000000000000000000000010000001;
        // boardBitBoard();
    }

    void fenBoard(std::string fen){
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
    }

    void boardBitboard(){
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                std::string field = board[i][j];
                // Set Bitboard for Blue Pawns to 1 and all other bitboards to 0
            }
        }
    }
    void printBitBoard(){
        std::cout << "Blue Pawns: " << blue_pawns << std::endl;
        std::cout << "Red Pawns: " << red_pawns << std::endl;
        std::cout << "Blue Blue Knight: " << blue_blue_knight << std::endl;
        std::cout << "Red Red Knight: " << red_red_knight << std::endl;
        std::cout << "Blue Red Knight: " << blue_red_knight << std::endl;
        std::cout << "Red Blue Knight: " << red_blue_knight << std::endl;
    }

    void printBoard(){
        for (std::vector<std::string> row : board) {
            for (std::string field : row) {
                std::cout << field << " ";
            }
            std::cout << std::endl;
        }
    }
    void print_blockedfields(){
        // print  std::bitset<64> blocked_fields in 8x8 
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                std::cout << blocked_fields[i*8+j];
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::string> split(std::string str, char delimiter) {
        std::vector<std::string> result;
        std::string temp = "";
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == delimiter) {
                result.push_back(temp);
                temp = "";
            } else {
                temp += str[i];
            }
        }
        result.push_back(temp);
        return result;
    }

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
    
};

int main(){
    // class board with 6/1bbbbbbbbbbbb1/8/8/8/1r0r0r0r0r0r01/8r0r0r0r0r0r0 b
    Board board("6/1bbbbbbbbbbbb1/8/8/8/1r0r0r0r0r0r01/8/r0r0r0r0r0r0 b");
    // print
    //board.printBoard();
    //board.printBitBoard();
    //std::cout << board.boardFen() << std::endl;
    board.print_blockedfields();

    return 0;
}
