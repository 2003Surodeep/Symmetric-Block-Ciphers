import random

IP = [                                                            #initial permutation table
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1, 
    59, 51, 43, 35, 27, 19, 11, 3, 
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
]

FP = [                                                            #final permutation table
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
]

pc_l = [                                                          #permuted choice table for the left half of the key
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36
]

pc_r = [                                                          #permuted choice table for the right half of the key
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
]


compression_permutation = [                                       #compression permutation table
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
]

expansion_table = [                                               #expansion table
    32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
]


PBOX = [                                                          #permutation box table
    16, 7, 20, 21, 29, 12, 28, 17, 
    1, 15, 23, 26, 5, 18, 31, 10, 
    2, 8, 24, 14, 32, 27, 3, 9, 
    19, 13, 30, 6, 22, 11, 4, 25
]

SBOX1 = [
    [14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7],
    [0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8],
    [4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0],
    [15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13]
]

SBOX2 = [
    [15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10],
    [3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5],
    [0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15],
    [13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9]
]

SBOX3 = [
    [10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8],
    [13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1],
    [13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7],
    [1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12]
]

SBOX4 = [
    [7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15],
    [13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9],
    [10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4],
    [3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14]
]

SBOX5 = [
    [2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9],
    [14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6],
    [4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 6, 5, 3, 0, 14],
    [11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3]
]

SBOX6 = [
    [12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11],
    [10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8],
    [9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6],
    [4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13]
]

SBOX7 = [
    [4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1],
    [13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6],
    [1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2],
    [6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12]
]

SBOX8 = [
    [13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7],
    [1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2],
    [7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8],
    [2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11]
]

SBOX = [SBOX1, SBOX2, SBOX3, SBOX4, SBOX5, SBOX6, SBOX7, SBOX8]   #array consisting of the 8 substitution box tables

def lshift(x, n):                                                 #function to left shift a given binary sequence x by n bits
    arr = []
    val = ""
    for i in range(len(x)):
        arr.append(x[i])
    for i in range(n):
        temp = arr[0]
        for j in range(len(x)-1):
            arr[j] = arr[j+1]
        arr[len(x)-1] = temp
    for i in arr:
        val += i
    return val

def toASCII(seq):                                                 #function that takes a 64 bit binary sequence as input and converts it to ASCII
    final = ""
    for i in range(8, len(seq)+1, 8):
        final += chr(int("0b"+seq[(i-8):i], 2))
    return final

def toBIN(seq):                                                   #function that takes a 8 byte ASCII sequence as input and converts it to binary
    final = ""
    for i in seq:
        final += "0"*(8-len(bin(ord(i))[2:])) + bin(ord(i))[2:]
    return final

def xor(x, y):                                                    #xor function that finds the exclusive-or of 2 binary sequences
    val = ""
    for i in range(len(x)):
        val += str(int(x[i]) ^ int(y[i]))
    return val

def key_transformation_fn(key):                                   #key transformation function that takes a 64 bit key as input and generates an array of keys for the 16 rounds of the DES encryption algorithm 
    '''#key discarding phase - every 8th bit gets discarded in order to create a 56 bit key
    final = ""
    for i in range(len(key)):
        if((i+1)%8 != 0):
            final += key[i]'''
    
    #dividing the key into two 28 bit halves using the permuted choice tables (Used permuted choice tables directly without dropping every 8th bit manually)
    left_half = ""
    for i in pc_l:
        left_half += key[i-1]
    
    right_half = ""
    for i in pc_r:
        right_half += key[i-1]
        
    #declaring an array to contain the keys for all 16 rounds
    key_arr = []
    for i in range(16):
        if((i+1) == 1 | (i+1) == 2 | (i+1) == 9 | (i+1) == 16):   #for 1st, 2nd, 9th and 16th rounds, left shift the left and the right halves of the key by 1 bit
            left_half = lshift(left_half, 1)    
            right_half = lshift(right_half, 1)
        else:                                                     #for the other rounds, left shift both the halves by 2 bits
            left_half = lshift(left_half, 2)
            right_half = lshift(right_half, 2)
        
        final = left_half + right_half                            #concatenate the left and the right halves to make a temporary 56 bit key
        
        #compression permutation phase
        final_output = ""
        for j in compression_permutation:
            final_output += final[j-1]                  
        key_arr.append(final_output)                              #appending the output of the compression permutation phase that will serve as a key for i-th round to the array 

    return key_arr

def round_fn(rpt, key):                                           #round function that takes as input the 32 bit right half of the 64 bit plain text and the 48 bit key   
    #expansion permutation phase to convert 32 bit rpt into 48 bit rpt
    final = ""
    for i in expansion_table:
        final += rpt[i-1]

    #xor-ing 48 bit expanded rpt with 48 bit key
    final = xor(final, key)

    #s-box substitution phase to generate 32 bit output
    pieces = []
    for i in range(6, len(final)+1, 6):
        pieces.append(final[(i-6):i])
    final = ""
    for i in range(len(pieces)):
        row = "0b" + pieces[i][0] + pieces[i][5]
        column = "0b" + pieces[i][1:5]
        row = int(row, 2); column = int(column, 2)
        final += "0"*(4-len(bin(SBOX[i][row][column])[2:])) + bin(SBOX[i][row][column])[2:]

    #p-box permutation phase 
    final_output = ""
    for i in PBOX:
        final_output += final[i-1]
    return final_output                                           #32 bit final output
 
def DES_encrypt(pt, key):                                         #DES encryption function that takes as input the 64 bit plain text and the 64 bit key
    #initial permutation phase 
    final = ""
    for i in IP:
        final += pt[i-1]
    
    #key transformation 
    key_arr = key_transformation_fn(key)                          #this function returns an array of the 48 bit keys to be used for each of the 16 rounds

    #16 rounds of encryption
    round = 16
    lptM = final[:32]; rptM = final[32:]                                #master values of lpt(left plain text) and rpt(right plain text)
    for i in range(round):
        temp1 = round_fn(rptM, key_arr[i])                        #running the round function over the 48 bit key and the 32 bit rpt
        temp2 = xor(lptM, temp1)                                  #xor-ing 32 bit the result with the 32 bit lpt
        lptM = rptM                                               #the previous rpt becomes the lpt
        rptM = temp2                                              #the result becomes the rpt
    final = rptM + lptM                                           #concatenate the 32 bit rpt and the 32 bit lpt 
    
    #final permutation phase
    cipher_text = ""
    for i in FP:
        cipher_text += final[i-1]

    return cipher_text                                            #return the final cipher text

def DES_decrypt(ct, key):
    #initial permutation phase 
    final = ""
    for i in IP:
        final += ct[i-1]
    
    #key transformation 
    key_arr = key_transformation_fn(key)[::-1]                    #this function returns a reversed array of the 48 bit keys to be used for each of the 16 rounds

    #16 rounds of encryption
    round = 16
    lctM = final[:32]; rctM = final[32:]                                #master values of lct(left cipher text) and rct(right cipher text)
    for i in range(round):
        temp1 = round_fn(rctM, key_arr[i])                        #running the round function over the 48 bit key and the 32 bit rct
        temp2 = xor(temp1, lctM)                                  #xor-ing 32 bit the result with the 32 bit lct
        lctM = rctM                                               #the previous rct becomes the lct
        rctM = temp2                                              #the result becomes the rct
    final = rctM + lctM                                           #concatenate the 32 bit rct and the 32 bit lct 
    
    #final permutation phase
    plain_text = ""
    for i in FP:
        plain_text += final[i-1]
    return plain_text                                            #return the final plain text


'''pt = "1100110000110100100000111010000010010101001101111000000001000010" #CC3483A095378042
key= "0111001101101100101101010010010111000101101100011100001011001100" #736CB525C5B1C2CC
print(DES_encrypt(pt, key))
ct = DES_encrypt(pt, key)
print(DES_decrypt(ct, key))'''
while 1:
    print("Main Menu: \n1. DES Encrypt 2. DES Decrypt 3. Exit")
    choice = int(input("Enter your choice: "))
    if choice == 1:
        pt = "0x" + input("Enter 64 bit plain text in hex: ")
        key = "0x" + input("Enter 64 bit key in hex: ")
        pt = bin(int(pt, 16))[2:]
        key = bin(int(key, 16))[2:]
        ct = "0b" + DES_encrypt(pt, key)
        ct = hex(int(ct, 2))[2:]
        print("Cipher text: ", ct)
    elif choice == 2:
        ct = "0x" + input("Enter 64 bit cipher text in hex: ")
        key = "0x" + input("Enter 64 bit key in hex: ")
        ct = bin(int(ct, 16))[2:]
        key = bin(int(key, 16))[2:]
        pt = "0b" + DES_decrypt(ct, key)
        pt = hex(int(pt, 2))[2:]
        print("Plain text: ", pt)
    else: 
        exit()
