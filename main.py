
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