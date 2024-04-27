from collections import defaultdict

def choose_move(board):
    return 0

def move_rating(board, moves):
    ans = defaultdict(int)
    for move in moves:
        ans[move] = 0
    
    return ans

