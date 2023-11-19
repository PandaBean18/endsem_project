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
___
## check_string_equality
### return type -> integer
### parameters -> string str_1, string str_2

This function matches each character of the first string with the second string. Incase the characters do not match, the function returns 0 (representing false). If all the characters match and the for loop is exited successfully, it returns 1 (representing true).

___
## valid_input
### return type -> integer
### parameters -> string str

The input coordinates that are inputted by the user are in the format `<alphabet representing the column>` `<number representing the row>` example: e2. This function ensures that this input is correct. Parameters for being correct:

1. Alphabetic part is from 'a' to 'h'.
2. Numeric part is from '1' to '8'.
3. There should only be one alphabetic character and only one numeric character.
4. Only other characters permissible other than these are whitespace (' ').

___
## turnicate_whitespace
### return type -> char* (pointer to a character)
### parameters -> string inp, string trimmed_inp -> trimmed_inp is what gets returned by the function

The function iterates over the `inp` string and:
    1. If a character is encountered, assigns trimmed_inp[0] that character
    2. If a number is encountered, assigns trimmed_inp[1] that numeric character
    3. After the iteration is complete, it assigns '\0' to trimmed_inp[2]
    4. Returns `trimmed_inp`.

This function expects a valid input so the input must be first run through `valid_input` function to ensure the input is valid.

___
## convert_input_to_coordinates
### return type -> int*
### parameters -> string inp, integer array coords -> this is what is returned by the function.

The zeroth element of the `coords` array represents the row, and first represents the column. However, the zeroth element of `inp` string represents the column and first represents the row. 

Also, the numeric part of inp is reversed on the board (it goes from 8 on top to 1 on bottom)

To get the row value, we take the numeric value of inp and subtract it from 8.

Note: we have done 8 - (*inp - 48), This is because:
    *inp gives a character whose value can be from '1' to '8' but we wish to have an integer value. Unicode for '1' is 49, subtracting 48 from '1' we get 1, so we have convereted '1' to 1 (character 1 to integer 1).
    Similar logic is used to convert 'a' to 0.

___
## convert_coords_to_input
### return type -> char*
### parameters -> integer array coords, string inp

Does the opposite of what the above function does.

___
## is_white
### return type -> int
### parameters -> string str

Checks `str` against an array of strings which we know are white pieces. Returns 1 if str matches any of the strings in `whites` array, else it returns 0. 

___
## find_piece_type
### return type -> char* 
### parameters -> char* piece, char* type

Checks the value stored at `piece` against an array of unicode values. The index, `i`, where the value matches is stored. `piece_names[i]` gives the pointer to the string that corresponds to the name of `piece`. Each value of `piece_name[i]` is then assigned to `type`.

