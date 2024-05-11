decimal = 132096

# convert decimal to binary and fill with 0s to make it 64 bits long
binary = bin(decimal)[2:]
while len(binary) < 64:
    binary = "0" + binary

# split the binary string into 8-bit chunks
chunks = [binary[i:i+8] for i in range(0, len(binary), 8)]
for i in range(8):
    print(chunks[i])
