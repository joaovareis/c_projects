#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//This code was written for Windows Terminal. In order to work properly with Unix systems, change "cls" to "clear"

#define RED_TEXT            "\x1b[1;31m"
#define GREEN_TEXT          "\x1b[1;32m"
#define YELLOW_TEXT         "\x1b[1;33m"
#define BLUE_TEXT           "\x1b[1;34m"
#define DARK_BLUE_TEXT      "\x1b[1;38;2;155;89;182m"
#define MAROON_TEXT         "\x1b[1;34;2m"
#define MAGENTA_TEXT        "\x1b[1;35m"
#define CYAN_TEXT           "\x1b[1;36m"
#define GRAY_TEXT           "\x1b[1;37m" // Color Start
#define COLOR_END           "\x1b[0m" // To flush out prev settings

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef i8 b8;
typedef i32 b32;

typedef float f32;

typedef struct {
    i64 rows, cols;

    u8* data;

} matrix;

#define SIZE 20
#define DIFFICULTY 21

void clear_screen();

void gen_true_board(const matrix* true_mat, const i8 difficulty);

i32 check_cell (const matrix* true_mat, const i64 ind);

void print_board (const matrix* mat);

void check_reveal_cell (const matrix* user_mat, const matrix* revelation, const matrix* ui_mat, const i64 ind);

int main () {

    matrix true_board = {SIZE, SIZE};
    matrix user_board = {SIZE, SIZE};
    matrix ui_board = {SIZE, SIZE};
    matrix revealed = {SIZE, SIZE};

    i64 index;
    b8 alive = true;

    const char *index_too_big = "Index invalido";
    const char *death_message = "Morreu";
    const char *input_message = "Digite um numero de 0 a ";
    const char *exit_message = "Para sair pressione Ctrl+C";
    //const char *start_message = "Qual tamanho você deseja?";

    //printf("%s\n", start_message,"\n");

    srand(time(NULL));

    true_board.data = (u8*)malloc(SIZE * SIZE * sizeof(u8));
    user_board.data = (u8*)malloc(SIZE * SIZE * sizeof(u8));
    ui_board.data = (u8*)malloc(SIZE * SIZE * sizeof(u8));
    revealed.data = (u8*)malloc(SIZE * SIZE * sizeof(u8));

    gen_true_board(&true_board, DIFFICULTY);

    for (i64 i = 0; i < SIZE*SIZE; i++) {
        
        ui_board.data[i] = '.';
        revealed.data[i] = 0;
        user_board.data[i] = check_cell(&true_board, i);

    }

    //print_board(&true_board);
    print_board(&ui_board);
    //print_board(&user_board);

    while (alive == true) {

        printf("%s%d\n", input_message, (SIZE*SIZE));
        scanf("%d", &index);

        if (index > (SIZE*SIZE - 1) || index < 0) {

            printf("%s\n", index_too_big);
            scanf("%d", &index);
        }

        if (true_board.data[index] == 'o'){

            clear_screen();
            printf("%s\n", death_message);
            ui_board.data[index] = true_board.data[index];
            print_board(&ui_board);
            alive = false;

        } else {

            revealed.data[index] = 1;
            ui_board.data[index] = user_board.data[index];

            for (i64 i = 0; i < SIZE*SIZE; i++) {
                check_reveal_cell(&user_board, &revealed, &ui_board, i);
                check_reveal_cell(&user_board, &revealed, &ui_board, (SIZE*SIZE - i));
            }

            clear_screen();
            print_board(&ui_board);

        }
    }

    printf("%s\n", exit_message);
    scanf("%s", &index);

    free(revealed.data);
    free(ui_board.data);
    free(true_board.data);
    free(user_board.data);
    
    return 0;

}

void clear_screen () {

    printf("\x1b[2J\x1b[H");
    
}

void gen_true_board(const matrix* true_mat, const i8 difficulty) {

        for (i64 i = 0; i < SIZE*SIZE; i++) {

        if ((rand() % 100) < (100 - DIFFICULTY)) {

            true_mat->data[i] = '.';

        } else {

            true_mat->data[i] = 'o';

        }
    }
}

i32 check_cell (const matrix* true_mat, const i64 ind) {

    u8 cell_value = 0;
    i64 row = ind / SIZE;
    i64 col = ind % SIZE;

    if (true_mat->data[ind] == 'o'){

        return (9);

    } else {

        if (row > 0 && row < (SIZE - 1) && col > 0 && col < (SIZE - 1)) {
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = -1; i < 2; i++){
                    if (true_mat->data[ind + (i) + (j)*SIZE] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (row > 0 && row < (SIZE -1) && col == 0) {
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = 0; i < 2; i++){
                    if (true_mat->data[ind + i + j*SIZE] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (row > 0 && row < (SIZE -1) && col == (SIZE -1)){
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = -1; i < 1; i++){
                    if (true_mat->data[ind + i + j*SIZE] == 'o') {

                        cell_value +=1;

                    }
                }
            }

        } else if (col > 0 && col < (SIZE -1) && (row == 0)) {
            for (i8 j = 0; j < 2; j++) {
                for (i8 i = -1; i < 2; i++){
                    if (true_mat->data[ind + i + j*SIZE] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (col > 0 && col < (SIZE -1) && (row == (SIZE -1))) {
            for (i8 j = -1; j < 1; j++) {
                for (i8 i = -1; i < 2; i++){
                    if (true_mat->data[ind + i + j*SIZE] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (ind == 0) {
            for (i8 j = 0; j < 2; j++) {
                for (i8 i = 0; i < 2; i++){
                    if (true_mat->data[ind + i + j*SIZE] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (ind == (SIZE - 1)){
            for (i8 j = 0; j < 2; j++) {
                for (i8 i = -1; i < 1; i++){
                    if (true_mat->data[ind + i + j*SIZE] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (ind == (SIZE - 1)*SIZE) {
            for (i8 j = -1; j < 1; j++) {
                for (i8 i = 0; i < 2; i++){
                    if (true_mat->data[ind + i + j*SIZE] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (ind == ((SIZE*SIZE) - 1)) {
            for (i8 j = -1; j < 1; j++) {
                for (i8 i = -1; i < 1; i++){
                    if (true_mat->data[ind + i + j*SIZE] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        }
    }

    return (cell_value);
};

void print_board (const matrix* mat) {

    for(i64 i = 0; i < SIZE*SIZE; i++) {

        if (mat->data[i] == 9){
            printf("%s%d%s",RED_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == 1) {
            printf("%s%d%s",BLUE_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == 2) {
            printf("%s%d%s",GREEN_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == 3) {
            printf("%s%d%s",MAGENTA_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == 4) {
            printf("%s%d%s",DARK_BLUE_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == 5) {
            printf("%s%d%s",MAROON_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == 6) {
            printf("%s%d%s",CYAN_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == 7) {
            printf("%s%d%s",YELLOW_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == 8) {
            printf("%s%d%s",GRAY_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == 0){
            printf("%d", mat->data[i]);
            printf(" ");
        } else if (mat->data[i] == 'o') {
            printf("%s%c%s", RED_TEXT, mat->data[i], COLOR_END);
            printf(" ");
        } else {
            printf("%c", mat->data[i]);
            printf(" ");            
        }

        if ((i+1) % SIZE == 0) {

            printf("\n");

        }
    }
}

void check_reveal_cell (const matrix* user_mat, const matrix* revelation, const matrix* ui_mat, const i64 ind) {

    int row = ind / SIZE;
    int col = ind % SIZE;
    
    if (revelation->data[ind] == 0) {

        return;

    } else if (user_mat->data[ind] == 0) {

        if (row > 0 && row < (SIZE -1) && col > 0 && col < (SIZE -1)) {
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = -1; i < 2; i++){
                    if (user_mat->data[ind + i + (j*SIZE)] < 9) {

                        revelation->data[ind + i + (j*SIZE)] = 1;
                        ui_mat->data[ind + i + (j*SIZE)] = user_mat->data[ind + i +(j*SIZE)];

                    }
                }
            }
        } else if (row > 0 && row < (SIZE -1) && col == 0) {
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = 0; i < 2; i++){
                    if (user_mat->data[ind + i + (j*SIZE)] < 9) {

                        revelation->data[ind + i + (j*SIZE)] = 1;
                        ui_mat->data[ind + i + (j*SIZE)] = user_mat->data[ind + i +(j*SIZE)];

                    }
                }
            }
        } else if (row > 0 && row < (SIZE -1) && col == (SIZE -1)){
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = -1; i < 1; i++){
                    if (user_mat->data[ind + i + (j*SIZE)] < 9) {

                        revelation->data[ind + i + (j*SIZE)] = 1;
                        ui_mat->data[ind + i + (j*SIZE)] = user_mat->data[ind + i +(j*SIZE)];

                    }
                }
            }

        } else if (col > 0 && col < (SIZE -1) && (row == 0)) {
            for (i8 j = 0; j < 2; j++) {
                for (i8 i = -1; i < 2; i++){
                    if (user_mat->data[ind + i + (j*SIZE)] < 9) {

                        revelation->data[ind + i + (j*SIZE)] = 1;
                        ui_mat->data[ind + i + (j*SIZE)] = user_mat->data[ind + i + (j*SIZE)];

                    }
                }
            }
        } else if (col > 0 && col < (SIZE -1) && (row == (SIZE -1))) {
            for (i8 j = -1; j < 1; j++) {
                for (i8 i = -1; i < 2; i++){
                    if (user_mat->data[ind + i + (j*SIZE)] < 9) {

                        revelation->data[ind + i + (j*SIZE)] = 1;
                        ui_mat->data[ind + i + (j*SIZE)] = user_mat->data[ind + i + (j*SIZE)];

                    }
                }
            }
        } else if (ind == 0) {
            for (i8 j = 0; j < 2; j++) {
                for (i8 i = 0; i < 2; i++){
                    if (user_mat->data[ind + i + (j*SIZE)] < 9) {

                        revelation->data[ind + i + (j*SIZE)] = 1;
                        ui_mat->data[ind + i + (j*SIZE)] = user_mat->data[ind + i + (j*SIZE)];

                    }
                }
            }
        } else if (ind == (SIZE -1)){
            for (i8 j = 0; j < 2; j++) {
                for (i8 i = -1; i < 1; i++){
                    if (user_mat->data[ind + i + (j*SIZE)] < 9) {

                        revelation->data[ind + i + (j*SIZE)] = 1;
                        ui_mat->data[ind + i + (j*SIZE)] = user_mat->data[ind + i + (j*SIZE)];

                    }
                }
            }
        } else if (ind == SIZE*(SIZE - 1)) {
            for (i8 j = -1; j < 1; j++) {
                for (i8 i = 0; i < 2; i++){
                    if (user_mat->data[ind + i + (j*SIZE)] < 9) {

                        revelation->data[ind + i + (j*SIZE)] = 1;
                        ui_mat->data[ind + i + (j*SIZE)] = user_mat->data[ind + i + (j*SIZE)];

                    }
                }
            }
        } else if (ind == (SIZE*SIZE - 1)) {
            for (i8 j = -1; j < 1; j++) {
                for (i8 i = -1; i < 1; i++){
                    if (user_mat->data[ind + i + (j*SIZE)] < 9) {

                        revelation->data[ind + i + (j*SIZE)] = 1;
                        ui_mat->data[ind + i + (j*SIZE)] = user_mat->data[ind + i + (j*SIZE)];
                    }
                }
            }
        }
    }
};