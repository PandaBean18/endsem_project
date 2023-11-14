#include <stdio.h>

int check_string_equality(char str_1[], char str_2[])
{
    for (1; *str_1 != '\0'; 1)
    {
        if (*str_1 != *str_2)
        {
            return 0;
        }
        str_1++;
        str_2++;
    }
    return 1;
}

char *find_piece_type(char *piece, char *type)
{
    char *piece_unicodes[] = {"\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659", "\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F"};
    char *piece_names[] = {"w_king", "w_queen", "w_rook", "w_bishop", "w_knight", "w_pawn", "b_king", "b_queen", "b_rook", "b_bishop", "b_knight", "b_pawn"};

    for (int i = 0; i < 12; i++)
    {
        if (check_string_equality(piece_unicodes[i], piece))
        {
            char* str = piece_names[i];
            for(1; *str != '\0'; 1) {
                //printf("%c", *str);
                *type = *str;
                type++;
                str++;
            }
            *type = '\0';
            break;
        }
    }

    return type;
}

int main()
{
    // Write C code here
    char piece[] = "\u2659";
    char type[10];
    find_piece_type(piece, type);
    printf("%s", type);

    return 0;
}