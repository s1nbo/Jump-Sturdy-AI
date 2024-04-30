import dummy_ai as da
import string_conversion as sc
import json
import legal_moves as lm
from translate_moves import translate_move
import time 


if __name__ == '__main__':
    str = '8/2b02b02/2r02r02/8/8/2b02b02/2r02r02/8 b'
    print(str)
   
    for i in range(1):
        board = sc.fen_board(str)
        moves = lm.legal_moves(board)

        move_rating = da.move_rating(board, moves)
        # Make a move
        lm.update_board(board, moves[0])
        # Send Move

    for row in board:
        print(row)

# start = time.time()
# stop = time.time()
# print("Time: ", stop-start)
"""
print(len(moves))
print(moves)
for move in moves:
    print(translate_move(move), end=" ")
"""