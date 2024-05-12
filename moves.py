# Generate Moves

"""

"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"

00 01 02 03 04 05 06 07
08 09 10 11 12 13 14 15
16 17 18 19 20 21 22 23
24 25 26 27 28 29 30 31
32 33 34 35 36 37 38 39
40 41 42 43 44 45 46 47
48 49 50 51 52 53 54 55
56 57 58 59 60 61 62 63


    const std::array<std::array<uint16_t, 4>, 64> redKnightTable = {
    };
    const std::array<std::array<uint16_t, 4>, 64> blueKnightTable = {
    };
    const std::array<std::array<uint16_t, 3>, 64> redPawnTable =
        {{
            {},{2, 9},{1, 3, 10},{2, 4, 11},{3, 5, 12},{4, 6, 13},{5, 7, 14},{},
            {9, 16},{8, 10, 17},{9, 11, 18},{10, 12, 19},{11, 13, 20},{12, 14, 21},{13, 15, 22},{14, 23},
            {17, 24},{16, 18, 25},{17, 19, 26},{18, 20, 27},{19, 21, 28},{20, 22, 29},{21, 23, 30},{22, 31},
            {25, 32},{24, 26, 33},{25, 27, 34},{26, 28, 35},{27, 29, 36},{28, 30, 37},{29, 31, 38},{30, 39},
            {33, 40},{32, 34, 41},{33, 35, 42},{34, 36, 43},{35, 37, 44},{36, 38, 45},{37, 39, 46},{38, 47},
            {41, 48},{40, 42, 49},{41, 43, 50},{42, 44, 51},{43, 45, 52},{44, 46, 53},{45, 47, 54},{46, 55},
            {49, 56},{48, 50, 57},{49, 51, 58},{50, 52, 59},{51, 53, 60},{52, 54, 61},{53, 55, 62},{54, 63},
            {},{56, 58},{57, 59},{58, 60},{59, 61},{60, 62},{61, 63},{}
        }};
    const std::array<std::array<uint16_t, 3>, 64> bluePawnTable = {
    };
    const std::array<std::array<uint16_t, 2>, 64> bluePawnDiagonalTable = {
    };
    const std::array<std::array<uint16_t, 2>, 64> redPawnDiagonalTable = {    };
"""


# Red pawns can move left, right and down
def generate_red_pawns():
    print("Red Pawns", end ="")
    print("{", end ="")
    for i in range(64):
        # print for every position
        match i:
            case 0:
                print("{},", end ="")
            case 1:
                print("{2, 9},", end ="")
            case 2:
                print("{1, 3, 10},", end ="")
            case 3:
                print("{2, 4, 11},", end ="")
            case 4:
                print("{3, 5, 12},", end ="")
            case 5:
                print("{4, 6, 13},", end ="")
            case 6:
                print("{5, 7, 14},", end="")
            case 7:
                print("{6, 15},")
            case 8:
                print("{9, 16},", end ="")
            case 9:
                print("{8, 10, 17},", end ="")
            case 10:
                print("{9, 11, 18},", end ="")
            case 11:
                print("{10, 12, 19},", end ="")
            case 12:
                print("{11, 13, 20},", end ="")
            case 13:
                print("{12, 14, 21},", end ="")
            case 14:
                print("{13, 15, 22},", end ="")
            case 15:
                print("{14, 23},")
            case 16:
                print("{17, 24},", end ="")
            case 17:
                print("{16, 18, 25},", end ="")
            case 18:
                print("{17, 19, 26},", end ="")
            case 19:
                print("{18, 20, 27},", end ="")
            case 20:
                print("{19, 21, 28},", end ="")
            case 21:
                print("{20, 22, 29},", end ="")
            case 22:
                print("{21, 23, 30},", end ="")
            case 23:
                print("{22, 31},")
            case 24:
                print("{25, 32},", end ="")
            case 25:
                print("{24, 26, 33},", end ="")
            case 26:
                print("{25, 27, 34},", end ="")
            case 27:
                print("{26, 28, 35},", end ="")
            case 28:
                print("{27, 29, 36},", end ="")
            case 29:
                print("{28, 30, 37},", end ="")
            case 30:
                print("{29, 31, 38},", end ="")
            case 31:
                print("{30, 39},")
            case 32:
                print("{33, 40},", end ="")
            case 33:
                print("{32, 34, 41},", end ="")
            case 34:
                print("{33, 35, 42},", end ="")
            case 35:
                print("{34, 36, 43},", end ="")
            case 36:
                print("{35, 37, 44},", end ="")
            case 37:
                print("{36, 38, 45},", end ="")
            case 38:
                print("{37, 39, 46},", end ="")
            case 39:
                print("{38, 47},")
            case 40:
                print("{41, 48},", end ="")
            case 41:
                print("{40, 42, 49},", end ="")
            case 42:
                print("{41, 43, 50},", end ="")
            case 43:
                print("{42, 44, 51},", end ="")
            case 44:
                print("{43, 45, 52},", end ="")
            case 45:
                print("{44, 46, 53},", end ="")
            case 46:
                print("{45, 47, 54},", end ="")
            case 47:
                print("{46, 55},")
            case 48:
                print("{49, 56},", end ="")
            case 49:
                print("{48, 50, 57},", end ="")
            case 50:
                print("{49, 51, 58},", end ="")
            case 51:
                print("{50, 52, 59},", end ="")
            case 52:
                print("{51, 53, 60},", end ="")
            case 53:
                print("{52, 54, 61},", end ="")
            case 54:
                print("{53, 55, 62},", end ="")
            case 55:
                print("{54, 63},")
            case 56:
                print("{57},", end ="")
            case 57:
                print("{56, 58},", end ="")
            case 58:
                print("{57, 59},", end ="")
            case 59:
                print("{58, 60},", end ="")
            case 60:
                print("{59, 61},", end ="")
            case 61:
                print("{60, 62},", end ="")
            case 62:
                print("{61, 63},", end ="")
            case 63:
                print("{62}")
            case _:
                print("Error", end ="")
    print("}")

# Red pawns can move left, right and up
def generate_blue_pawn():
    for i in range(64):
        # print for every position
        # dont use match
        if i%8 != 0 and i%8 != 7: # not on the left or right edge
            if i > 7: # not on the top edge
                print(f" {{ {i-8}, {i+1}, {i-1} }}," , end ="")
            else:
                print(f" {{ {i+1}, {i-1} }}," , end ="")
        elif i%8 == 0: # left edge
            if i > 7:
                print(f" {{ {i-8}, {i+1} }}," , end ="")
            else:
                print(f" {{ {i+1} }}," , end ="")
        elif i%8 == 7: # right edge
            if i > 7:
                print(f"{{ {i-8}, {i-1} }}," , end ="")
            else:
                print(f" {{ {i-1} }}," , end ="")
        else:
            print("Error", end ="")
        if i%8 == 7:
            print("")

# down left and down right
def generate_red_pawn_diagonal():
        for i in range(64):
        # print for every position
        # dont use match
            if i%8 != 0 and i%8 != 7: # not on the left or right edge
                if i < 56: # not on the bottom edge
                    print(f" {{ {i+7}, {i+9} }}," , end ="")
                else:
                    print(f" {{ }}," , end ="")
            
            elif i%8 == 0: # left edge
                if i < 56:
                    print(f" {{ {i+9} }}," , end ="")
                else:
                    print(f" {{ }}," , end ="")
            elif i%8 == 7: # right edge
                if i < 56:
                    print(f"{{ {i+7} }}," , end ="")
                else:
                    print(f" {{ }}," , end ="")
            else:
                print("Error", end ="")
            if i%8 == 7:
                print("")  


# up left and up right
def generate_blue_pawn_diagonal():
    for i in range(64):
        if i%8 != 0 and i%8 != 7:
            if i > 7:
                print(f" {{ {i-7}, {i-9} }}," , end ="")
            else:
                print(f" {{ }}," , end ="")
        elif i%8 == 0:
            if i > 7:
                print(f" {{ {i-7} }}," , end ="")
            else:
                print(f" {{ }}," , end ="")
        elif i%8 == 7:
            if i > 7:
                print(f"{{ {i-9} }}," , end ="")
            else:
                print(f" {{ }}," , end ="")
        else:
            print("Error", end ="")
        if i%8 == 7:
            print("")

"""
00 01 02 03 04 05 06 07
08 09 10 11 12 13 14 15
16 17 18 19 20 21 22 23
24 25 26 27 28 29 30 31
32 33 34 35 36 37 38 39
40 41 42 43 44 45 46 47
48 49 50 51 52 53 54 55
56 57 58 59 60 61 62 63


"""



# can move in L shape up left, up right, left up, right up
# 17 15 10 6 (negative for blue)
def generate_blue_knight():
    for i in range(64):
        print(f"{{", end ="")
        if i%8 != 0 and i > 15:
            print(f"{i-17},", end ="")
        if i%8 != 7 and i > 15:
            print(f"{i-15},", end ="")
        if i%8 != 1 and i%8 != 0 and i > 7:
            print(f"{i-10},", end ="")
        if i%8 != 6 and i%8 != 7 and i > 7:
            print(f"{i-6},", end ="")
        print(f"}},", end ="")
        if i%8 == 7:
            print("")



# can move in L shape down left, down right, left down, right down
# 17 15 10 6 (positive for red)
def generate_red_knight():
    for i in range(64):
        print(f"{{", end ="")
        # add 17 down right
        # only works if not on the right edge and not second to last row or last row
        if i%8 != 7 and i < 48:
            print(f"{i+17},", end ="")
        


        # add 15 down left
        # only works if not on the left edge and not second to last row or last row
        if i%8 != 0 and i < 48:
            print(f"{i+15},", end ="")

        # add 10 right down
        # only works if not on the right edge or second to right field and not on the last row
        if i%8 != 6 and i%8 != 7 and i < 56:
            print(f"{i+10},", end ="")

        # add 6 left down
        # only works if not on the left edge or second to left field and not on the last row
        if i%8 != 0 and i%8 != 1 and i < 56:
            print(f"{i+6},", end ="")

        print(f"}},", end ="")
    
        if i%8 == 7:
            print("")



    

generate_red_knight()
print("\n")
generate_blue_knight()



         
