#include <windows.h> 
#include <stdio.h>
#include <locale.h>

typedef struct CheckResult {
    int colour; // 0, 1 or 2
    int king_under_check[2]; 
    int piece[2];
} CheckResult;

int includes(char str[], char c) 
{
    for(1; *str != '\0'; str++) {
        if (*str == c) {
            return 1;
        }
    }

    return 0;
}

int check_string_equality(char str_1[], char str_2[]) 
{
    for (1; *str_1 != '\0'; 1) {
        if (*str_1 != *str_2) {
            return 0;
        } 
        str_1++;
        str_2++;
    }
    return 1;
}

int valid_input(char str[]) 
{
    int count_alpha = 0; 
    int count_num = 0; 
    char alpha[] = "abcdefgh";
    char num[] = "12345678";

    for(0; *str != '\0'; str++) {
        if (includes(alpha, *str)) {
            if ((*str < 'a') || (*str > 'h')) {
                return 0;
            }

            count_alpha++;

            if (count_alpha > 1) {
                return 0;
            }
        } else if (includes(num, *str)) {
            if ((*str < '1') || (*str > '8')) {
                return 0;
            }

            count_num++;

            if (count_num > 1) {
                return 0;
            }
        } else if  (*str != ' ') {
            return 0;
        }
    }

    if ((count_alpha == 0) || (count_num == 0)) {
        return 0;
    }

    return 1;
}

char* turnicate_whitespace(char inp[], char trimmed_inp[3])
{
    char alpha[] = "abcdefgh";
    char num[] = "12345678";

    for(0; *inp != '\0'; inp++) {
        if (includes(alpha, *inp)) {
            trimmed_inp[0] = *inp;
        } else if (includes(num, *inp)) {
            trimmed_inp[1] = *inp;
        }
    }
    trimmed_inp[2] = '\0';
    return trimmed_inp;
}

int* convert_input_to_coordinates(char inp[], int coords[2]) 
{

    char alpha[] = "abcdefgh";
    char num[] = "12345678";

    for(1; *inp != '\0'; inp++) {
        if (includes(alpha, *inp)) {
            coords[1] = *inp - 97;
        }
        if (includes(num, *inp)) {
            coords[0] =  8 - (*inp - 48);
        }
    } 
    
    return coords;
}

int is_white(char str[])
{
    char *whites[6] = {"\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659"};

    for (int i = 0; i < 6; i++)
    {
        if (check_string_equality(whites[i], str))
        {
            return 1;
        }
    }

    return 0;
}

char* find_piece_type(char* piece, char* type) 
{
    char* piece_unicodes[] = {"\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659", "\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F"};
    char* piece_names[] = {"w_king", "w_queen", "w_rook", "w_bishop", "w_knight", "w_pawn", "b_king", "b_queen", "b_rook", "b_bishop", "b_knight", "b_pawn"};

    for(int i = 0; i < 12; i++) {
        if (check_string_equality(piece_unicodes[i], piece)) {
            char *str = piece_names[i];
            for (1; *str != '\0'; 1)
            {
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

int** find_possible_moves(char* board[64], int piece_ptr[], int* positions[63][2])
{

    int piece[2] = {*(piece_ptr++), *piece_ptr};
    char piece_type[10];
    find_piece_type(board[(piece[0] * 8) + piece[1]], piece_type);
    if (check_string_equality(piece_type, "w_pawn")) {
        if (piece[0] == 6) {
            int positions_end_count = 0;
            int piece_pos = (piece[0] * 8) + piece[1];
            int piece_color = is_white(board[piece_pos]);
            if (*(board[((piece[0] - 1) * 8) + piece[1]]) == ' ') {
                positions[positions_end_count][0] = (piece[0] - 1);
                positions[positions_end_count][1] = piece[1];
                positions_end_count++;

                if ((*(board[((piece[0] - 2) * 8) + piece[1]]) == ' '))
                {
                    positions[positions_end_count][0] = (piece[0] - 2);
                    positions[positions_end_count][1] = piece[1];
                    positions_end_count++;
                }
            }

            int diag_pos_1 = ((piece[0]) - 1) * 8 + (piece[1] + 1);
            int diag_pos_2 = ((piece[0]) - 1) * 8 + (piece[1] - 1);

            if ((((piece[1]) + 1) >= 0 && ((piece[1]) + 1) < 8) && (*(board[diag_pos_1]) != ' ') && (is_white((board[(piece[0] * 8) + piece[1]])) ^ is_white((board[diag_pos_1])))) {
                positions[positions_end_count][0] = (piece[0]) - 1;
                positions[positions_end_count][1] = (piece[1] + 1);
                positions_end_count++;
            }

            if ((((piece[1]) - 1) >= 0 && ((piece[1]) - 1) < 8) && (*(board[diag_pos_2]) != ' ') && (is_white((board[(piece[0] * 8) + piece[1]])) ^ is_white((board[diag_pos_2])))) {
                positions[positions_end_count][0] = (piece[0]) - 1;
                positions[positions_end_count][1] = (piece[1] - 1);
                positions_end_count++;
            }

            positions[positions_end_count][0] = -1;
            positions[positions_end_count][1] = -1;
            return positions;
        } else {
            if ((piece[0] - 1) >= 0) {
                int positions_end_count = 0;

                if (*(board[((piece[0] - 1) * 8) + piece[1]]) == ' ') {
                    positions[positions_end_count][0] = piece[0]-1;
                    positions[positions_end_count][1] = piece[1];
                    positions_end_count++;
                }

                int diag_pos_1 = ((piece[0]) - 1) * 8 + (piece[1] + 1);
                int diag_pos_2 = ((piece[0]) - 1) * 8 + (piece[1] - 1);

                if ((((piece[1]) + 1) >= 0 && ((piece[1]) + 1) < 8) && (*(board[diag_pos_1]) != ' ') && (is_white((board[(piece[0] * 8) + piece[1]])) ^ is_white((board[diag_pos_1]))))
                {
                    positions[positions_end_count][0] = (piece[0]) - 1;
                    positions[positions_end_count][1] = (piece[1] + 1);
                    positions_end_count++;
                }

                if ((((piece[1]) - 1) >= 0 && ((piece[1]) - 1) < 8) && (*(board[diag_pos_2]) != ' ') && (is_white((board[(piece[0] * 8) + piece[1]])) ^ is_white((board[diag_pos_2]))))
                {
                    positions[positions_end_count][0] = (piece[0]) - 1;
                    positions[positions_end_count][1] = (piece[1] - 1);
                    positions_end_count++;
                }

                positions[positions_end_count][0] = -1;
                positions[positions_end_count][1] = -1;
                return positions;
            } else {
                positions[0][0] = -1;
                positions[0][1] = -1;
                return positions;
            }
        }
    } else if (check_string_equality(piece_type, "b_pawn")) {
        if (piece[0] == 1) {
            int positions_end_count = 0;
            int piece_pos = (piece[0] * 8) + piece[1];
            int piece_color = is_white(board[piece_pos]);
            if (*(board[((piece[0] + 1) * 8) + piece[1]]) == ' ')
            {
                positions[positions_end_count][0] = (piece[0] + 1);
                positions[positions_end_count][1] = piece[1];
                positions_end_count++;

                if ((*(board[((piece[0] + 2) * 8) + piece[1]]) == ' '))
                {
                    positions[positions_end_count][0] = (piece[0] + 2);
                    positions[positions_end_count][1] = piece[1];
                    positions_end_count++;
                }
            }

            int diag_pos_1 = (((piece[0] + 1) * 8) + (piece[1] + 1));
            int diag_pos_2 = (((piece[0] + 1) * 8) + (piece[1] - 1));

            if ((((piece[1] + 1) >= 0) && ((piece[1] + 1) < 8)) && (*(board[diag_pos_1]) != ' ') && (is_white((board[(piece[0] * 8) + piece[1]])) ^ is_white((board[diag_pos_1]))))
            {
                positions[positions_end_count][0] = piece[0] + 1;
                positions[positions_end_count][1] = piece[1] + 1;
                positions_end_count++;
            }

            if ((((piece[1]) - 1) >= 0 && ((piece[1]) - 1) < 8) && (*(board[diag_pos_2]) != ' ') && (is_white((board[(piece[0] * 8) + piece[1]])) ^ is_white((board[diag_pos_2])))) {
                positions[positions_end_count][0] = piece[0] + 1;
                positions[positions_end_count][1] = piece[1] - 1;
                positions_end_count++;
            }

            positions[positions_end_count][0] = -1;
            positions[positions_end_count][1] = -1;
            return positions;
        } else {
            if ((piece[0] + 1) < 8) {
                int positions_end_count = 0;

                if (*(board[((piece[0] + 1) * 8) + piece[1]]) == ' ')
                {
                    positions[positions_end_count][0] = piece[0] + 1;
                    positions[positions_end_count][1] = piece[1];
                    positions_end_count++;
                }

                int diag_pos_1 = (((piece[0] + 1) * 8) + (piece[1] + 1));
                int diag_pos_2 = (((piece[0] + 1) * 8) + (piece[1] - 1));

                if ((((piece[1] + 1) >= 0) && ((piece[1] + 1) < 8)) && (*(board[diag_pos_1]) != ' ') && (is_white((board[(piece[0] * 8) + piece[1]])) ^ is_white((board[diag_pos_1]))))
                {
                    positions[positions_end_count][0] = piece[0] + 1;
                    positions[positions_end_count][1] = piece[1] + 1;
                    positions_end_count++;
                }

                if ((((piece[1]) - 1) >= 0 && ((piece[1]) - 1) < 8) && (*(board[diag_pos_2]) != ' ') && (is_white((board[(piece[0] * 8) + piece[1]])) ^ is_white((board[diag_pos_2]))))
                {
                    positions[positions_end_count][0] = piece[0] + 1;
                    positions[positions_end_count][1] = piece[1] - 1;
                    positions_end_count++;
                }

                positions[positions_end_count][0] = -1;
                positions[positions_end_count][1] = -1;
                return positions;
            } else {
                positions[0][0] = -1;
                positions[0][1] = -1;
                return positions;
            }
        }

    } else if ((check_string_equality(piece_type, "w_rook")) || (check_string_equality(piece_type, "b_rook"))) {
        int positions_count = 0;

        for(int i = 1; (piece[0] + i) < 8; i++) {
            if (*(board[((piece[0] + i) * 8) + piece[1]]) == ' ') {
                positions[positions_count][0] = piece[0] + i;
                positions[positions_count][1] = piece[1];
                positions_count++;
            } else {
                if (is_white(board[((piece[0] + i) * 8) + piece[1]]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0] + i;
                    positions[positions_count][1] = piece[1];
                    positions_count++;
                }
                break;
            }
        }

        for(int i = 1; (piece[1] + i) < 8; i++) {
            if (*(board[(piece[0] * 8) + piece[1] + i]) == ' ') {
                positions[positions_count][0] = piece[0];
                positions[positions_count][1] = piece[1] + i;
                positions_count++;
            } else {
                if (is_white(board[(piece[0] * 8) + piece[1] + i]) ^ is_white(board[(piece[0] * 8) + piece[1]]))
                {
                    positions[positions_count][0] = piece[0];
                    positions[positions_count][1] = piece[1] + i;
                    positions_count++;
                }
                break;
            }
        }

        for(int i = 1; (piece[0] - i) >= 0; i++) {
            if (*(board[((piece[0] - i) * 8) + piece[1]]) == ' ') {
                positions[positions_count][0] = piece[0] - i;
                positions[positions_count][1] = piece[1];
                positions_count++;
            } else {
                if (is_white(board[((piece[0] - i) * 8) + piece[1]]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0] - i;
                    positions[positions_count][1] = piece[1];
                    positions_count++;
                }
                break;
            }
        }

        for(int i = 1; (piece[1] - i) >= 0; i++) {
            if (*(board[(piece[0] * 8) + piece[1] - i]) == ' ') {
                positions[positions_count][0] = piece[0];
                positions[positions_count][1] = piece[1] - i;
                positions_count++;
            } else {
                if (is_white(board[(piece[0] * 8) + piece[1] - i]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0];
                    positions[positions_count][1] = piece[1] - i;
                    positions_count++;
                }
                break;
            }
        }

        positions[positions_count][0] = -1; 
        positions[positions_count][1] = -1; 
        return positions;
    } else if (check_string_equality(piece_type, "w_bishop") || check_string_equality(piece_type, "b_bishop")) {
        int positions_count = 0;
        int i = 1;

        while (((piece[0] + i) < 8) && (piece[1] + i) < 8) {
            if (*(board[((piece[0] + i) * 8) + piece[1] + i]) == ' ') {
                positions[positions_count][0] = piece[0] + i;
                positions[positions_count][1] = piece[1] + i;
                positions_count++;
            } else {
                if (is_white(board[((piece[0] + i) * 8) + piece[1] + i]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0] + i;
                    positions[positions_count][1] = piece[1] + i;
                    positions_count++;
                }
                break;
            }

            i++;
        }

        i = 1;

        while (((piece[0] + i) < 8) && ((piece[1] - i) >= 0)) {
            if (*(board[((piece[0] + i) * 8) + piece[1] - i]) == ' ')
            {
                positions[positions_count][0] = piece[0] + i;
                positions[positions_count][1] = piece[1] - i;
                positions_count++;
            }
            else
            {
                if (is_white(board[((piece[0] + i) * 8) + piece[1] - i]) ^ is_white(board[(piece[0] * 8) + piece[1]]))
                {
                    positions[positions_count][0] = piece[0] + i;
                    positions[positions_count][1] = piece[1] - i;
                    positions_count++;
                }
                break;
            }
            i++;
        }

        i = 1;

        while (((piece[0] - i) >= 0) && ((piece[1] - i) >= 0)) {
            if (*(board[((piece[0] - i) * 8) + piece[1] - i]) == ' ')
            {
                positions[positions_count][0] = piece[0] - i;
                positions[positions_count][1] = piece[1] - i;
                positions_count++;
            }
            else
            {
                if (is_white(board[((piece[0] - i) * 8) + piece[1] - i]) ^ is_white(board[(piece[0] * 8) + piece[1]]))
                {
                    positions[positions_count][0] = piece[0] - i;
                    positions[positions_count][1] = piece[1] - i;
                    positions_count++;
                }
                break;
            }

            i++;
        }

        i = 1;

        while (((piece[0] - i) >= 0) && ((piece[1] + i) < 8))
        {
            if (*(board[((piece[0] - i) * 8) + piece[1] + i]) == ' ')
            {
                positions[positions_count][0] = piece[0] - i;
                positions[positions_count][1] = piece[1] + i;
                positions_count++;
            }
            else
            {
                if (is_white(board[((piece[0] - i) * 8) + piece[1] + i]) ^ is_white(board[(piece[0] * 8) + piece[1]]))
                {
                    positions[positions_count][0] = piece[0] - i;
                    positions[positions_count][1] = piece[1] + i;
                    positions_count++;
                }
                break;
            }
            i++;
        }

        positions[positions_count][0] = -1;
        positions[positions_count][1] = -1;
        return positions;
    } else if (check_string_equality(piece_type, "w_queen") || check_string_equality(piece_type, "b_queen")) {
        int positions_count = 0;

        for(int i = 1; (piece[0] + i) < 8; i++) {
            if (*(board[((piece[0] + i) * 8) + piece[1]]) == ' ') {
                positions[positions_count][0] = piece[0] + i;
                positions[positions_count][1] = piece[1];
                positions_count++;
            } else {
                if (is_white(board[((piece[0] + i) * 8) + piece[1]]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0] + i;
                    positions[positions_count][1] = piece[1];
                    positions_count++;
                }
                break;
            }
        }

        for(int i = 1; (piece[1] + i) < 8; i++) {
            if (*(board[(piece[0] * 8) + piece[1] + i]) == ' ') {
                positions[positions_count][0] = piece[0];
                positions[positions_count][1] = piece[1] + i;
                positions_count++;
            } else {
                if (is_white(board[(piece[0] * 8) + piece[1] + i]) ^ is_white(board[(piece[0] * 8) + piece[1]]))
                {
                    positions[positions_count][0] = piece[0];
                    positions[positions_count][1] = piece[1] + i;
                    positions_count++;
                }
                break;
            }
        }

        for(int i = 1; (piece[0] - i) >= 0; i++) {
            if (*(board[((piece[0] - i) * 8) + piece[1]]) == ' ') {
                positions[positions_count][0] = piece[0] - i;
                positions[positions_count][1] = piece[1];
                positions_count++;
            } else {
                if (is_white(board[((piece[0] - i) * 8) + piece[1]]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0] - i;
                    positions[positions_count][1] = piece[1];
                    positions_count++;
                }
                break;
            }
        }

        for(int i = 1; (piece[1] - i) >= 0; i++) {
            if (*(board[(piece[0] * 8) + piece[1] - i]) == ' ') {
                positions[positions_count][0] = piece[0];
                positions[positions_count][1] = piece[1] - i;
                positions_count++;
            } else {
                if (is_white(board[(piece[0] * 8) + piece[1] - i]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0];
                    positions[positions_count][1] = piece[1] - i;
                    positions_count++;
                }
                break;
            }
        }

        int i = 1;

        while (((piece[0] + i) < 8) && (piece[1] + i) < 8) {
            if (*(board[((piece[0] + i) * 8) + piece[1] + i]) == ' ') {
                positions[positions_count][0] = piece[0] + i;
                positions[positions_count][1] = piece[1] + i;
                positions_count++;
            } else {
                if (is_white(board[((piece[0] + i) * 8) + piece[1] + i]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0] + i;
                    positions[positions_count][1] = piece[1] + i;
                    positions_count++;
                }
                break;
            }

            i++;
        }

        i = 1;

        while (((piece[0] + i) < 8) && ((piece[1] - i) >= 0)) {
            if (*(board[((piece[0] + i) * 8) + piece[1] - i]) == ' ')
            {
                positions[positions_count][0] = piece[0] + i;
                positions[positions_count][1] = piece[1] - i;
                positions_count++;
            }
            else
            {
                if (is_white(board[((piece[0] + i) * 8) + piece[1] - i]) ^ is_white(board[(piece[0] * 8) + piece[1]]))
                {
                    positions[positions_count][0] = piece[0] + i;
                    positions[positions_count][1] = piece[1] - i;
                    positions_count++;
                }
                break;
            }
            i++;
        }

        i = 1;

        while (((piece[0] - i) >= 0) && ((piece[1] - i) >= 0)) {
            if (*(board[((piece[0] - i) * 8) + piece[1] - i]) == ' ')
            {
                positions[positions_count][0] = piece[0] - i;
                positions[positions_count][1] = piece[1] - i;
                positions_count++;
            }
            else
            {
                if (is_white(board[((piece[0] - i) * 8) + piece[1] - i]) ^ is_white(board[(piece[0] * 8) + piece[1]]))
                {
                    positions[positions_count][0] = piece[0] - i;
                    positions[positions_count][1] = piece[1] - i;
                    positions_count++;
                }
                break;
            }

            i++;
        }

        i = 1;

        while (((piece[0] - i) >= 0) && ((piece[1] + i) < 8))
        {
            if (*(board[((piece[0] - i) * 8) + piece[1] + i]) == ' ')
            {
                positions[positions_count][0] = piece[0] - i;
                positions[positions_count][1] = piece[1] + i;
                positions_count++;
            }
            else
            {
                if (is_white(board[((piece[0] - i) * 8) + piece[1] + i]) ^ is_white(board[(piece[0] * 8) + piece[1]]))
                {
                    positions[positions_count][0] = piece[0] - i;
                    positions[positions_count][1] = piece[1] + i;
                    positions_count++;
                }
                break;
            }
            i++;
        }

        positions[positions_count][0] = -1;
        positions[positions_count][1] = -1;
        return positions;
    } else if (check_string_equality(piece_type, "w_knight") || check_string_equality(piece_type, "b_knight")) {
        int positions_count = 0;

        if ((piece[0] + 2) < 8) {
            if ((piece[1] + 1) < 8) {
                if (is_white(board[((piece[0] + 2) * 8) + piece[1] + 1]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0] + 2;
                    positions[positions_count][1] = piece[1] + 1;
                    positions_count++;
                }
            }

            if ((piece[1] - 1) >= 0) {
                if (is_white(board[((piece[0] + 2) * 8) + piece[1] - 1]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0] + 2;
                    positions[positions_count][1] = piece[1] - 1;
                    positions_count++;
                }
            }
        }

        if ((piece[0] - 2) >= 0) {
            if ((piece[1] + 1) < 8) {
                if (is_white(board[((piece[0] - 2) * 8) + piece[1] + 1]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0] - 2;
                    positions[positions_count][1] = piece[1] + 1;
                    positions_count++;
                }
            }

            if ((piece[1] - 1) >= 0) {
                if (is_white(board[((piece[0] - 2) * 8) + piece[1] - 1]) ^ is_white(board[(piece[0] * 8) + piece[1]])) {
                    positions[positions_count][0] = piece[0] - 2;
                    positions[positions_count][1] = piece[1] - 1;
                    positions_count++;
                }
            }
        }

        positions[positions_count][0] = -1;
        positions[positions_count][1] = -1;
        return positions;
    } else if (check_string_equality(piece_type, "w_king") || check_string_equality(piece_type, "b_king")) {
        int positions_count = 0;
        int piece_pos = (piece[0] * 8) + piece[1];
        int piece_color = is_white(board[piece_pos]);
        if ((piece[0] + 1) < 8) {
            if ((*(board[((piece[0] + 1) * 8) + piece[1]]) == ' ') || (piece_color ^ is_white(board[((piece[0] + 1) * 8) + piece[1]])))
            {
                positions[positions_count][0] = piece[0] + 1;
                positions[positions_count][1] = piece[1];
                positions++;
            }

            if (((piece[1] + 1) < 8) && ((*(board[((piece[0] + 1) * 8) + piece[1] + 1]) == ' ') || (piece_color ^ is_white(board[((piece[0] + 1) * 8) + piece[1] + 1]))))
            {
                positions[positions_count][0] = piece[0] + 1;
                positions[positions_count][1] = piece[1] + 1;
                positions++;
            }

            if (((piece[1] - 1) >= 0) && ((*(board[((piece[0] + 1) * 8) + piece[1] - 1]) == ' ') || (piece_color ^ is_white(board[((piece[0] + 1) * 8) + piece[1] - 1]))))
            {
                positions[positions_count][0] = piece[0] + 1;
                positions[positions_count][1] = piece[1] - 1;
                positions++;
            }
        } 
        
        if ((piece[0] - 1) >= 0) {
            if ((*(board[((piece[0] - 1) * 8) + piece[1]]) == ' ') || (piece_color ^ is_white(board[((piece[0] - 1) * 8) + piece[1]])))
            {
                positions[positions_count][0] = piece[0] - 1;
                positions[positions_count][1] = piece[1];
                positions++;
            }

            if (((piece[1] + 1) < 8) && ((*(board[((piece[0] - 1) * 8) + piece[1] + 1]) == ' ') || (piece_color ^ is_white(board[((piece[0] - 1) * 8) + piece[1] + 1]))))
            {
                positions[positions_count][0] = piece[0] - 1;
                positions[positions_count][1] = piece[1] + 1;
                positions++;
            }

            if (((piece[1] - 1) >= 0) && ((*(board[((piece[0] - 1) * 8) + piece[1] - 1]) == ' ') || (piece_color ^ is_white(board[((piece[0] - 1) * 8) + piece[1] - 1]))))
            {
                positions[positions_count][0] = piece[0] - 1;
                positions[positions_count][1] = piece[1] - 1;
                positions++;
            }
        }

        if ((piece[1] + 1) < 8) {
            if ((*(board[(piece[0] * 8) + piece[1] + 1]) == ' ') || (piece_color ^ is_white(board[(piece[0] * 8) + piece[1] + 1])))
            {
                positions[positions_count][0] = piece[0];
                positions[positions_count][1] = piece[1] + 1;
                positions_count++;
            }
        }

        if ((piece[1] - 1) >= 0) {
            if ((*(board[(piece[0] * 8) + piece[1] - 1]) == ' ') || (piece_color ^ is_white(board[(piece[0] * 8) + piece[1] - 1])))
            {
                positions[positions_count][0] = piece[0];
                positions[positions_count][1] = piece[1] - 1;
                positions_count++;
            }
        }

        positions[positions_count][0] = -1;
        positions[positions_count][1] = -1;
        return positions;
    }
}

CheckResult king_in_check(char* board[64], CheckResult result) // return 0 -> no king in check
{                                  // return 1 -> white in check
    char b_king[] = "\u265A";      // return 2 -> black in check
    char w_king[] = "\u2654";
    
    int positions[63][2] = {{-1, -1}};

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if (*(board[(i * 8) + j]) != ' ') {
                int piece[] = {i, j};
                find_possible_moves(board, piece, positions);
                for(int k = 0; positions[k][0] != -1; k++) {
                    if (check_string_equality(board[(positions[k][0] * 8) + positions[k][1]], w_king)) {
                        result.colour = 1;
                        result.king_under_check[0] = positions[k][0];
                        result.king_under_check[1] = positions[k][1];
                        result.piece[0] = piece[0];
                        result.piece[1] = piece[1];
                        return result;
                    }
                    else if (check_string_equality(board[(positions[k][0] * 8) + positions[k][1]], b_king)) {
                        result.colour = 2;
                        result.king_under_check[0] = positions[k][0];
                        result.king_under_check[1] = positions[k][1];
                        result.piece[0] = piece[0];
                        result.piece[1] = piece[1];
                        return result;
                    }
                }
            }
        }
    }
    printf("a");
    result.colour = 0;
    return result;
}

int move_piece(char* board[64], int initial_pos[2], int final_pos[2]) 
{
    int possible_moves[63][2] = {{-1, -1}}; 
    find_possible_moves(board, initial_pos, possible_moves);

    for (int i = 0; possible_moves[i][0] != -1; i++) {
        if ((possible_moves[i][0] == final_pos[0]) && (possible_moves[i][1] == final_pos[1])) {
            board[(final_pos[0] * 8) + final_pos[1]] = board[(initial_pos[0] * 8) + initial_pos[1]];
            board[(initial_pos[0] * 8) + initial_pos[1]] = " \0";
            return 1;
        } 
    }

    return 0;
}

void print_board(char* board[64])
{
    system("cls");
    printf("   a  b  c  d  e  f  g  h \n");
    for(int i = 0; i < 8; i++) {
        printf("%d ", 8-i);
        for(int j = 0; j < 8; j++) {
            if ((i+j) % 2 == 0) {
                if (is_white(board[(i*8)+j])) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |FOREGROUND_INTENSITY);
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN);
                }
                
            } else {
                if (is_white(board[(i*8)+j])) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |FOREGROUND_INTENSITY);
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
                }
            }

            if (check_string_equality(board[(i*8)+j], "\u265F")) {
                printf(" %s", board[(i*8)+j]);
            } else {
                printf(" %s ", board[(i*8)+j]);
            }
            
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |FOREGROUND_INTENSITY);
        printf(" %d\n", 8-i);

    }
    printf("   a  b  c  d  e  f  g  h \n");
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    const char w_king[] = "\u2654";
    const char w_queen[] = "\u2655";
    const char w_rook[] = "\u2656";
    const char w_bishop[] = "\u2657";
    const char w_knight[] = "\u2658";
    const char w_pawn[] = "\u2659";

    const char b_king[] = "\u265A";
    const char b_queen[] = "\u265B";
    const char b_rook[] = "\u265C";
    const char b_bishop[] = "\u265D";
    const char b_knight[] = "\u265E";
    const char b_pawn[] = "\u265F";
    const char whitespace[] = " ";

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

    int game_over = 0;
    int check_w = 0; 
    int check_b = 0;
    int current_player = 1; // 0 for black 1 for white

    char player_w[10];
    char player_b[10];
    CheckResult check_result;
    check_result.colour = 0;

    fflush(stdin);

    printf("Please enter the name of the first player (white): ");
    gets(&player_w);

    fflush(stdin); 

    printf("Please enter the name of the second player (black): ");
    gets(&player_b);

    printf("White moves first!\n\n");

    while (!game_over) {
        char inp_1[10];
        char inp_2[10];
        char trimmed_1[3];
        char trimmed_2[3];

        int coords_initial[2];
        int coords_final[2];
        int valid_move = 0;

        print_board(board);
        if (check_w) {
            printf("\n\n%s is under check. (King - {%d, %d}, Piece - {%d, %d})\n\n", player_w, check_result.king_under_check[0], check_result.king_under_check[1], check_result.piece[0], check_result.piece[1]);
        } else if (check_b) {
            printf("\n\n%s is under check. (King - {%d, %d}, Piece - {%d, %d})\n\n", player_b, check_result.king_under_check[0], check_result.king_under_check[1], check_result.piece[0], check_result.piece[1]);
        }

        if (current_player == 0) {
            printf("It is %s's turn.\n\n", player_b);
        } else {
            printf("It is %s's turn.\n\n", player_w);
        }

        while (!valid_move) {
            fflush(stdin);
            printf("Please enter the position of the piece you wish to move: ");
            gets(&inp_1);

            int input_valid = valid_input(inp_1);

            while (!input_valid) {
                fflush(stdin);
                printf("Input is not valid, please try again: ");
                gets(&inp_1);
                input_valid = valid_input(inp_1);
            }

            fflush(stdin);
            printf("Please enter the position to which you want to move to: ");
            gets(&inp_2);

            input_valid = valid_input(inp_2);

            while (!input_valid) {
                fflush(stdin);
                printf("Input is not valid, please try again: ");
                gets(&inp_2);
                input_valid = valid_input(inp_2);
            }

            turnicate_whitespace(inp_1, trimmed_1);
            turnicate_whitespace(inp_2, trimmed_2);

            convert_input_to_coordinates(trimmed_1, coords_initial);
            convert_input_to_coordinates(trimmed_2, coords_final);

            if (is_white(board[(coords_initial[0] * 8) + coords_initial[1]]) ^ current_player) {
                printf("\nPlease pick a %s coloured piece.\n", (current_player ? "white\0" : "black\0"));
                continue;
            } else if (*(board[(coords_initial[0] * 8) + coords_initial[1]]) == ' ') {
                printf("\nNo piece at %s.\n", trimmed_1);
                continue;
            }

            valid_move = move_piece(board, coords_initial, coords_final); 

            if (!valid_move) {
                printf("Can not move %s to %s. Try again.\n", trimmed_1, trimmed_2);
            } else {
                current_player = (current_player + 1) % 2;
            }
        }

        check_result = king_in_check(board, check_result);
        int check = check_result.colour;

        if (check == 1) {
            if (check_w == 1) {
                print_board(board);
                printf("White is under checkmate. %s wins\n\n", player_b);
                game_over = 1;
            } else {
                check_w = 1;
            }
        } else if (check == 2) {
            if (check_b == 1) {
                print_board(board);
                printf("Black is under checkmate. %s wins\n\n", player_w);
                game_over = 1;
            } else {
                check_b = 1;
            }
        } else {
            check_b = 0;
            check_w = 0;
        }
    }

    return 0;
}