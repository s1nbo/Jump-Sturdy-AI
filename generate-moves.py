
possible = ["red_pawn", "blue_pawn", "red_knight", "blue_knight"]
ans = []

for piece in possible:
    for row in range(8):
        for variant in range(256):
            # create binary list out of 256
            cur = [int(x) for x in bin(variant)[2:]]
            cur = [0]*(8-len(cur)) + cur

            # check if the piece can move
            if piece == "red_pawn":
                for col in range(8):
                    if col> 0 and cur[col-1]:
                        # move left
                        pass
                    if col < 7 and cur[col+1]:
                        # move right
                        pass
                    if row < 7:
                        # move down
                        pass
                    if row < 7 and not(row == 6 and col == 6) and col < 7:
                        # move diagonal right down
                        pass
                    if row < 7 and not(row == 6 and col == 1) and col > 0:
                        # move diagonal left down
                        pass

            elif piece == "blue_pawn":
                pass
            
            elif piece == "red_knight":
                pass
            
            elif piece == "blue_knight":
                pass

        


            



"""

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
"""