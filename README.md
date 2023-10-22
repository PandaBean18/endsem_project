# Function Definations 

## includes
### return type -> integer
### parameters -> string called str, character c

The function checks if a string (str) contains a character (c). It does this by running a for loop which starts at the first character of string and till null character ('\0') is encountered. The null character is the last character in a string. The parameter str is actually a pointer to the first character of the string, so to move to the next character, we increment the pointer (str++). If at any point in the loop, the value at pointer (\*str) is equal to the character (c), we return 1, indicating that the string (str) **includes** the character (c). If none of the characters of the string match the character (c), the for loop ends. Since the character was not found in the string, we return 0. 

Here 1 and 0 act as True and False.