# The board
Every m*n board that is to be displayed can be represented as a two dimensional array:
| 0 | 0 | 0 |
|---|---|---|
| 0 | 0 | 0 |
| 0 | 0 | 0 |

is the same as:

{
    {0, 0, 0},
    {0, 0, 0}, 
    {0, 0, 0}
}

The advantage of using two dimensional arrays is that it allows us to use coordinate system to refer to each piece on the grid, for example (0, 0) refers to the top left element of the grid, and if we look at the array, array[0][0] refers to zeroth element of zeroth array, which coinicdes with the top left element.


In our chess game however, we have used a one dimensional array of length 64 to represent the 64 places on a normal chess board (8*8 = 64). This is because on our board we are using strings to represent the chess pieces, and we know that strings are arrays of characters themselves, this would have meant that our board would have went up from 2 dimensions to 3. So here we have used a one dimensional array, and each element of the array is a pointer to the string's location. 

What the board looks like in code:

char *board[64] = {
        b_rook, b_knight, b_bishop, b_queen, b_king, b_bishop, b_knight, b_rook,
        b_pawn, b_pawn, b_pawn, b_pawn, b_pawn, b_pawn, b_pawn, b_pawn,
        whitespace, whitespace, whitespace, whitespace, whitespace, whitespace, whitespace, whitespace,
        whitespace, whitespace, whitespace, whitespace, whitespace, whitespace, whitespace, whitespace,
        whitespace, whitespace, whitespace, whitespace, whitespace, whitespace, whitespace, whitespace,
        whitespace, whitespace, whitespace, whitespace, whitespace, whitespace, whitespace, whitespace,
        w_pawn, w_pawn, w_pawn, w_pawn, w_pawn, w_pawn, w_pawn, w_pawn,
        w_rook, w_knight, w_bishop, w_queen, w_king, w_bishop, w_knight, w_rook
    };

Here the chess pieces are actually unicode characters.

Even though the chess board is a one dimensional array, the coordinate system is still utilized here to reference places on the chess board as follows:

lets say you wish to refer to the jth element of the ith row, which would be represented in coordinate system as (i, j), one dimensional index corresponding to this element can be found as follows:

(i * 8) + j

The above expression will be used throughout the code to check for pieces at (i, j)th position.


___
# CheckResult struct

```c
typedef struct CheckResult {
    int colour; // 0, 1 or 2
    int king_under_check[2]; 
    int piece[2];
} CheckResult;
```

The struct has been used to check if a king is under a check or no. `colour` can be any value from {0, 1, 2}, 0 representing no check, 1 representing white under check, and 2 representing black under check. `king_under_check` is an array containing coordinates of the king that is under check and `piece` is an array containing the coordinates of the piece that is causing the check.

___

# Function Definations 

## includes
### return type -> integer
### parameters -> string called str, character c

The function checks if a string (str) contains a character (c). It does this by running a for loop which starts at the first character of string and till null character ('\0') is encountered. The null character is the last character in a string. The parameter str is actually a pointer to the first character of the string, so to move to the next character, we increment the pointer (str++). If at any point in the loop, the value at pointer (\*str) is equal to the character (c), we return 1, indicating that the string (str) **includes** the character (c). If none of the characters of the string match the character (c), the for loop ends. Since the character was not found in the string, we return 0. 

Here 1 and 0 act as True and False.

##