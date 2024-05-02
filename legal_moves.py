from typing import List 

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
    

