#include "ai.hpp"
#include "board.hpp"
#include "moves.hpp"
#include "connect.hpp"

#include <string>
// Main function

/*
. Connect to Server  (TODO)
1a. Start Game (TODO)
2. Get FEN from Server (TODO)

3. Convert FEN to Board (DONE)
3a. Check if game is over (DONE)


4. Get legal moves from Board (DONE)
5. Choose a move from legal moves (DONE)
6. Send move to Server (TODO)
7. Repeat from 2 until game is over
8. Close connection
*/


int main(){
    // class board with 6/1bbbbbbbbbbbb1/8/8/8/1r0r0r0r0r0r01/8r0r0r0r0r0r0 b
    std::string fen = "6/1bbbbbbbbbbbb1/8/8/8/1r0r0r0r0r0r01/8/r0r0r0r0r0r0 r";
    bitboard bitboard;

    Moves moves;
    Board board(fen, bitboard);
    // std::cout << fen << std::endl;
    // std::cout << board.bitboardFen(bitboard) << std::endl;
    // board.printBitboard(bitboard);
    // which turn is it?
    std::vector<uint16_t> legal_moves = moves.generateMoves(bitboard);
    std::cout << "Game Over: " << moves.gameOver(bitboard, legal_moves) << std::endl;

    moves.printMoves(legal_moves);

    //uint16_t move = legal_moves[0];
    //bitboard = moves.updateBoard(bitboard, move);
    //board.printBitboard(bitboard);

    return 0;
}



/*

import dummy_ai as da
import string_conversion as sc

import legal_moves as lm
from translate_moves import translate_move

import time 
from sys import argv
import json


if __name__ == '__main__':
    strings = ["1b04/2b03b01/b01rr5/r02b01b02/1b06/1r02b03/8/1r01r0r0r0 b"]

    
    for str in strings:
        try:
            board = sc.fen_board(str)
            moves = lm.legal_moves(board)

            print(len(moves))
            for move in moves:
                print(translate_move(move), end=" ")
            # move_rating = da.move_rating(board, moves)
            # Make a move
            # lm.update_board(board, moves[0])
            # Send Move


            for row in board:
                print(row)
        except Exception as e:
            print(e)

# start = time.time()
# stop = time.time()
# print("Time: ", stop-start)
"""
print(len(moves))
print(moves)
for move in moves:
    print(translate_move(move), end=" ")
"""

*/

/*
from typing import List 
class move:
    def legal_moves(board: List[List[str]]) -> List[int]:
        ans = []
        # check whos turn it is
        # True -> blue and False -> red
        player = (board[0][0] == 'B')

        for row in range(8):
            for col in range(8):
                # Blue
                if player:
                    if board[row][col] == 'b':
                        # Going Up
                        if row-1 >= 0 and (board[row-1][col] == '0' or board[row-1][col] == 'b'):
                            ans.append((row, col, row-1, col))

                        # Going Left
                        if col-1 >= 0 and (board[row][col-1] == '0' or board[row][col-1] == 'b'):
                            ans.append((row, col, row, col-1))

                        # Going Right
                        if col+1 < 8 and (board[row][col+1] == '0' or board[row][col+1] == 'b'):
                            ans.append((row, col, row, col+1))

                        # Diagonal Left
                        if row-1 >= 0 and col-1 >= 0 and (board[row-1][col-1] == 'r' or board[row-1][col-1] == 'br' or board[row-1][col-1] == 'rr'):
                            ans.append((row, col, row-1, col-1))

                        # Diagonal Right
                        if row-1 >= 0 and col+1 < 8 and (board[row-1][col+1] == 'r' or board[row-1][col+1] == 'br' or board[row-1][col+1] == 'rr'):
                            ans.append((row, col, row-1, col+1))
                        
                        
                        # can move to field, 0, b;
                        # can move diagonaly to field, r, rb, rr;
                        # cannot move to field, bb, br, X, R, B;

                        
                    
                    if board[row][col] == 'bb' or board[row][col] == 'rb':

                        # Going Up and Left
                        if row-2 >= 0 and col-1 >= 0 and (board[row-2][col-1] == '0' or board[row-2][col-1] == 'b' or board[row-2][col-1] == 'r' or board[row-2][col-1] == 'br' or board[row-2][col-1] == 'rr'):
                            ans.append((row, col, row-2, col-1))
                        # Going Up and Right
                        if row-2 >= 0 and col+1 < 8 and (board[row-2][col+1] == '0' or board[row-2][col+1] == 'b' or board[row-2][col+1] == 'r' or board[row-2][col+1] == 'br' or board[row-2][col+1] == 'rr'):
                            ans.append((row, col, row-2, col+1))
                        # Going Left and Up
                        if row-1 >= 0 and col-2 >= 0 and (board[row-1][col-2] == '0' or board[row-1][col-2] == 'b' or board[row-1][col-2] == 'r' or board[row-1][col-2] == 'br' or board[row-1][col-2] == 'rr'):
                            ans.append((row, col, row-1, col-2))
                        # Going Right and Up
                        if row-1 >= 0 and col+2 < 8 and (board[row-1][col+2] == '0' or board[row-1][col+2] == 'b' or board[row-1][col+2] == 'r' or board[row-1][col+2] == 'br' or board[row-1][col+2] == 'rr'):
                            ans.append((row, col, row-1, col+2))
                        
                        # Horse (walks in L shape, forward and left/right, left/right and forward)
                        # Blue row-2 and col-1, row-2 and col+1, row-1 and col-2, row-1 and col+2
                        # Can Land on field: 0, b, r, rb, rr
                        # Cannot land on field, bb, br, X, B, R
                        
                # Red
                else:
                    if board[row][col] == 'r': 
                        # Going Down
                        if row+1 < 8 and (board[row+1][col] == '0' or board[row+1][col] == 'r'):
                            ans.append((row, col, row+1, col))

                        # Going Left
                        if col-1 >= 0 and (board[row][col-1] == '0' or board[row][col-1] == 'r'):
                            ans.append((row, col, row, col-1))

                        # Going Right
                        if col+1 < 8 and (board[row][col+1] == '0' or board[row][col+1] == 'r'):
                            ans.append((row, col, row, col+1))

                        # Diagonal Left
                        if row+1 < 8 and col-1 >= 0 and (board[row+1][col-1] == 'b' or board[row+1][col-1] == 'rb' or board[row+1][col-1] == 'bb'):
                            ans.append((row, col, row+1, col-1))
                        
                        # Diagonal Right
                        if row+1 < 8 and col+1 < 8 and (board[row+1][col+1] == 'b' or board[row+1][col+1] == 'rb' or board[row+1][col+1] == 'bb'):
                            ans.append((row, col, row+1, col+1))
                    
                    if board[row][col] == 'rr' or board[row][col] == 'br':
                        # Going Down and Left
                        if row+2 < 8 and col-1 >= 0 and (board[row+2][col-1] == '0' or board[row+2][col-1] == 'r' or board[row+2][col-1] == 'b' or board[row+2][col-1] == 'rb' or board[row+2][col-1] == 'bb'):
                            ans.append((row, col, row+2, col-1))
                        # Going Down and Right
                        if row+2 < 8 and col+1 < 8 and (board[row+2][col+1] == '0' or board[row+2][col+1] == 'r' or board[row+2][col+1] == 'b' or board[row+2][col+1] == 'rb' or board[row+2][col+1] == 'bb'):
                            ans.append((row, col, row+2, col+1))
                        # Going Left and Down
                        if row+1 < 8 and col-2 >= 0 and (board[row+1][col-2] == '0' or board[row+1][col-2] == 'r' or board[row+1][col-2] == 'b' or board[row+1][col-2] == 'rb' or board[row+1][col-2] == 'bb'):
                            ans.append((row, col, row+1, col-2))
                        # Going Right and Down
                        if row+1 < 8 and col+2 < 8 and (board[row+1][col+2] == '0' or board[row+1][col+2] == 'r' or board[row+1][col+2] == 'b' or board[row+1][col+2] == 'rb' or board[row+1][col+2] == 'bb'):
                            ans.append((row, col, row+1, col+2))
                        
                        # Horse (walks in L shape, forward and left/right, left/right and forward)
                        # Red row+2 and col-1, row+2 and col+1, row+1 and col-2, row+1 and col+2
                        # Can Land on field: 0, b, r, br, bb
                        # Cannot land on field, rr, rb, X, B, R

        return ans


    def game_over(board: List[List[str]]) -> bool:
        for i in range(1, 7):
            if board[0][i] == 'b' or board[0][i] == 'bb' or board[0][i] == 'rb' or board[7][i] == 'r' or board[7][i] == 'rr' or board[7][i] == 'br':
                return True
            
            # Check if opponent can make a move
            board_copy = board.copy()
            moves = legal_moves(board_copy)
            if len(moves) == 0:
                return True
            # Change player
            board_copy[0][0] = 'R' if board_copy[0][0] == 'B' else 'B'
            moves = legal_moves(board_copy)
            if len(moves) == 0:
                return True
            
        return False

    def update_board(board, move):
        # Only takes legal moves
        row, col, new_row, new_col = move
        old_field = board[row][col]
        target_field = board[new_row][new_col]
        player = (board[0][0] == 'B')

        # Move can be made by (b, bb, br)or (r, rr, rb)
        if old_field == 'b' or old_field == 'r':
            board[row][col] = '0'
        elif old_field == 'bb' or old_field == 'br':
            board[row][col] = 'b'
        elif old_field == 'rr' or old_field == 'rb':
            board[row][col] = 'r'

        if target_field == '0':
            if player:
                board[new_row][new_col] = 'b'
            else:
                board[new_row][new_col] = 'r'
        
        if target_field == 'b':
            if player:
                board[new_row][new_col] = 'bb'
            else:
                board[new_row][new_col] = 'r'
        
        # Move on field with red piece
        if target_field == 'r':
            if player:
                board[new_row][new_col] = 'b'
            else:
                board[new_row][new_col] = 'rr'
        
        if target_field == 'rr' and player:
            board[new_row][new_col] = 'rb'
        
        if target_field == 'bb' and not player:
            board[new_row][new_col] = 'br'

        if target_field == 'br' and player:
            board[new_row][new_col] = 'bb'
        
        if target_field == 'rb' and not player:
            board[new_row][new_col] = 'rr'
        
        # Change player
        board[0][0] = 'R' if board[0][0] == 'B' else 'B'

        return 
        


*/

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

00 01 02 03 04 05 06 07
08 09 10 11 12 13 14 15
16 17 18 19 20 21 22 23
24 25 26 27 28 29 30 31
32 33 34 35 36 37 38 39
40 41 42 43 44 45 46 47
48 49 50 51 52 53 54 55
56 57 58 59 60 61 62 63

100011 111000 001 0
*/