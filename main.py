import dummy_ai as da
import string_conversion as sc
import json
import legal_moves as lm

import time 


if __name__ == '__main__':
    
    str = 'b0b0b0b0b0b0/1b0b0b0b0b0b01/8/8/8/8/1r0r0r0r0r0r01/r0r0r0r0r0r0 b'
    print(str)
    start = time.time()
    for i in range(34**20):
        board = sc.fen_board(str)
        moves = lm.legal_moves(board)
        move_rating = da.move_rating(board, moves)
        # Make a move
        lm.update_board(board, moves[0])
        # Send Move
    stop = time.time()
    for row in board:
        print(row)
    print("Time: ", stop-start)