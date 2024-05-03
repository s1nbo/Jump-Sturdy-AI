/*# Empty -> 00
# blue -> 01
# red -> 10
# blue blue -> 02
# red red -> 20
# red blue -> 11
# blue red -> 11
# Not a field -> X

# example string -> b0b0b0b0b0b0/1b0b0b0b0b0b01/8/8/8/8/1r0r0r0r0r0r01/r0r0r0r0r0r0 b
from typing import List
class Board:
    def __init__(self, fen: str):
        self.board = self.fen_board(fen)
        self.fen = fen
        self.player = fen.split(' ')[1]
# Could add Caching to the function to speed up the process
    def fen_board(self, fen: str) -> List[List[str]]:
        fen = fen.split(' ')
        board = []
        for row in fen[0].split('/')[::-1]:

            board_row = []
            figure = True
            for i in range(len(row)):
                if figure:
                    char = row[i]
                    if char.isdigit():
                        for _ in range(int(char)):
                            board_row.append('0')
                    else:
                        figure = False
                        if row[i+1] == '0':
                            board_row.append(char)
                        else:
                            board_row.append(char + row[i+1])          
                else:
                    figure = True

            board.append(board_row)
        
        # Add x to the end of the board
        board[-1].insert(0, 'X')
        board[0].insert(0, fen[1].upper())
        board[0].append('X')
        board[-1].append('X')
        return board
        

    def board_fen(board: List[List[str]]) -> str:
        
        for i in range(8):
            counter = 0
            for j in range(8):
                if board[i][j] == '0':
                    counter += 1
                    board[i][j] = ''
                else:
                    if counter > 0:
                        board[i][j-1] = str(counter)
                        counter = 0
                    match board[i][j]:
                        case 'b':
                            board[i][j] = 'b0'
                        case 'r':
                            board[i][j] = 'r0'
                        case 'X':
                            board[i][j] = ''
                        case 'B':
                            board[i][j] = ''
                            player = 'b'
                        case 'R':
                            board[i][j] = ''
                            player = 'r'
            
            if counter > 0:
                board[i][7] = str(counter)

        # make string out of the board
        ans = '' + '/'.join([''.join(row) for row in board[::-1]]) + ' ' + player.lower()
        return ans 
*/
/*

# Translate moves from (y1, x1, y2, x2) to A1, B2, etc.
#  y = 0 to 7 is 0 to 7
#  x = 0 to 7 is A to H

def translate_move(move):
    y1, x1, y2, x2 = move
    x1 = chr(x1 + 65)
    x2 = chr(x2 + 65)
    y1 = 8 - y1
    y2 = 8 - y2
    return f"{x1}{y1}->{x2}{y2},"



*/