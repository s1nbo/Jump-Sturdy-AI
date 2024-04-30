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

