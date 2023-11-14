#include <windows.h> 
#include <stdio.h>
#include <locale.h>
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

char* turnicate_whitespace(char inp[], char trimmed_inp[2])
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
            positions[0][0] = (piece[0]-1);
            positions[0][1] = piece[1];
            positions[1][0] = (piece[0] - 2);
            positions[1][1] = piece[1];
            int positions_end_count = 2;

            int diag_pos_1 = ((piece[0]) - 1) * 8 + (piece[1] + 1);
            int diag_pos_2 = ((piece[0]) - 1) * 8 + (piece[1] - 1);

            if ((((piece[1]) + 1) >= 0 && ((piece[1]) + 1) < 8) && (*(board[diag_pos_1]) != ' ') && (is_white(*(board[(piece[0] * 8) + piece[1]])) ^ is_white(*(board[diag_pos_1])))) {
                positions[2][0] = (piece[0]) - 1;
                positions[2][1] = (piece[1] + 1);
                positions_end_count++;
            }

            if ((((piece[1]) - 1) >= 0 && ((piece[1]) - 1) < 8) && (*(board[diag_pos_2]) != ' ') && (is_white(*(board[(piece[0] * 8) + piece[1]])) ^ is_white(*(board[diag_pos_2])))) {
                positions[3][0] = (piece[0]) - 1;
                positions[3][1] = (piece[1] - 1);
                positions_end_count++;
            }

            positions[positions_end_count][0] = -1;
            positions[positions_end_count][1] = -1;
            return positions;
        } else {
            if ((piece[0] - 1) >= 0) {
                positions[0][0] = piece[0]-1;
                positions[0][1] = piece[1];

                positions[1][0] = -1;
                positions[1][1] = -1;
                return positions;
            } else {
                positions[0][0] = -1;
                positions[0][1] = -1;
                return positions;
            }
        }
    } else if (check_string_equality(piece_type, "b_pawn")) {
        if (piece[0] == 1) {
            positions[0][0] = (piece[0] + 1);
            positions[0][1] = piece[1];
            positions[1][0] = (piece[0] + 2);
            positions[1][1] = piece[1];
            int positions_end_count = 2;

            int diag_pos_1 = (((piece[0] + 1) * 8) + (piece[1] + 1));
            int diag_pos_2 = (((piece[0] + 1) * 8) + (piece[1] - 1));

            if ((((piece[1] + 1) >= 0) && ((piece[1] + 1) < 8)) && (*(board[diag_pos_1]) != ' ') && (is_white(*(board[(piece[0] * 8) + piece[1]])) ^ is_white(*(board[diag_pos_1])))) {
                positions[positions_end_count][0] = piece[0] + 1;
                positions[positions_end_count][1] = piece[1] + 1;
                positions_end_count++;
            }

            if ((((piece[1]) - 1) >= 0 && ((piece[1]) - 1) < 8) && (*(board[diag_pos_2]) != ' ') && (is_white(*(board[(piece[0] * 8) + piece[1]])) ^ is_white(*(board[diag_pos_2])))) {
                positions[positions_end_count][0] = piece[0] + 1;
                positions[positions_end_count][1] = piece[1] - 1;
                positions_end_count++;
            }

            positions[positions_end_count][0] = -1;
            positions[positions_end_count][1] = -1;
            return positions;
        } else {
            if ((piece[0] + 1) < 8) {
                positions[0][0] = piece[0] + 1; 
                positions[0][1] = piece[1];

                positions[1][0] = -1;
                positions[1][1] = -1;
                return positions;
            } else {
                positions[0][0] = -1;
                positions[0][1] = -1;
                return positions;
            }
        }

    }
}

void move_piece(char* board[64], int initial_pos[2], int final_pos[2]) 
{
    char* temp = board[(initial_pos[0]*8)+initial_pos[1]];
    board[(initial_pos[0]*8)+initial_pos[1]] = board[(final_pos[0]*8)+final_pos[1]];
    board[(final_pos[0]*8)+final_pos[1]] = temp;
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

    print_board(board);

    int positions[63][2] = {{1, 1}, {-1, -1}};
    int piece[2] = {6, 0};
    find_possible_moves(board, piece, positions);

    for (int i = 0; i != 10; i++)
    {
        printf("%d, %d\n", positions[i][0], positions[i][1]);
    }
    return 0;
}