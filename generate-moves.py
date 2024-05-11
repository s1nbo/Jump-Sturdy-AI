
possible = ["red_pawn", "blue_pawn", "blue_attack", "red_attack", "red_knight", "blue_knight"]
ans = []

piece = possible[0] # iterate over manually 

name_id = {
    "blue_pawn": 0,
    "red_pawn": 4,
    "blue_knight": 1,
    "red_knight": 5,
    "blue_red_knight": 2,
    "red_blue_knight": 6
}


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



for row in range(8): # iterate over rows 1-6 or (2-7 for non computer science people)
    temp3 = [] # list of moves for each row
    for variant in range(256):
        # create binary list out of 256
        cur = [int(x) for x in bin(variant)[2:]]
        cur = [0]*(8-len(cur)) + cur
        temp2 = [] # list of moves for each variant of the row
        

        # All the possible moves for the red_pawn piece
        # if row is 8 tiles long
        if piece == "red_pawn":
            for col in range(8):
                temp = ""

                if cur[col] == 1 and col > 0: # move left
                    start = row*8 + col
                    end = row*8 + col - 1
                    # make them 6 bits long
                    temp = bin(end)[2:]
                    while len(temp) < 6:
                        temp = "0" + temp
                    # add the start position
                    temp = bin(start)[2:] + temp
                    # make them 6 bits long
                    while len(temp) < 12:
                        temp = "0" + temp
                    # add the piece id
                    temp += ("100" + "0")
                    # add to the list
                    temp2.append(temp)


                if col < 7 and cur[col] == 1: # move right
                    start = row*8 + col
                    end = row*8 + col + 1
                    # make them 6 bits long
                    temp = bin(end)[2:]
                    while len(temp) < 6:
                        temp = "0" + temp
                    # add the start position
                    temp = bin(start)[2:] + temp
                    # make them 6 bits long
                    while len(temp) < 12:
                        temp = "0" + temp
                    # add the piece id
                    temp += ("100" + "0")
                    # add to the list
                    temp2.append(temp)
                
                

            temp2.append(temp)
       
        



        elif piece == "blue_pawn":
            pass

        elif piece == "blue_attack":
            pass
        
        elif piece == "red_attack":
            pass

        
        elif piece == "red_knight":
            pass
        
        elif piece == "blue_knight":
            pass
        
        
        temp3.append(temp2)
      
    ans.append(temp3)



# print ans into file

with open("moves.txt", "w") as f:
    f.write(str(ans))
    f.close()





