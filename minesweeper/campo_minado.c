#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define RED_TEXT            "\x1b[1;31m"
#define GREEN_TEXT          "\x1b[1;32m"
#define YELLOW_TEXT         "\x1b[1;33m"
#define BLUE_TEXT           "\x1b[1;34m"
#define DARK_BLUE_TEXT      "\x1b[1;34;1m"
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
    u8 rows, cols;

    u8* data;

} matrix;

#define SIZE 10
#define DIFFICULTY 21

int gen_true_board(const matrix* true_mat, const i8 difficulty) {

        for (u8 i = 0; i < SIZE*SIZE; i++) {

        if ((rand() % 100) < (100 - DIFFICULTY)) {

            true_mat->data[i] = '.';

        } else {

            true_mat->data[i] = 'o';

        };
    }

}

int check_cell (const matrix* true_mat, const i8 ind) {

    u8 cell_value = 0;
    i8 row = ind / 10;
    i8 col = ind % 10;

    if (true_mat->data[ind] == 'o'){

        return (9);

    } else {

        if (row > 0 && row < 9 && col > 0 && col < 9) {
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = -1; i < 2; i++){
                    if (true_mat->data[ind + (i) + (j)*10] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (row > 0 && row < 9 && col == 0) {
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = 0; i < 2; i++){

              

                    if (true_mat->data[ind + i + j*10] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (row > 0 && row < 9 && col == 9){
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = -1; i < 1; i++){

                  

                    if (true_mat->data[ind + i + j*10] == 'o') {

                        cell_value +=1;

                    }
                }
            }

        } else if (col > 0 && col < 9 && (row == 0)) {

            for (i8 j = 0; j < 2; j++) {
                for (i8 i = -1; i < 2; i++){

                

                    if (true_mat->data[ind + i + j*10] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (col > 0 && col < 9 && (row == 9)) {

            for (i8 j = -1; j < 1; j++) {
                for (i8 i = -1; i < 2; i++){
              

                    if (true_mat->data[ind + i + j*10] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (ind == 0) {

            for (i8 j = 0; j < 2; j++) {
                for (i8 i = 0; i < 2; i++){
                

                    if (true_mat->data[ind + i + j*10] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (ind == 9){
            for (i8 j = -1; j < 1; j++) {
                for (i8 i = 0; i < 2; i++){
                 
                    if (true_mat->data[ind + i + j*10] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (ind == 90) {

            for (i8 j = -1; j < 1; j++) {
                for (i8 i = 0; i < 2; i++){
                  
                    if (true_mat->data[ind + i + j*10] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        } else if (ind == 99) {

            for (i8 j = -1; j < 1; j++) {
                for (i8 i = -1; i < 1; i++){
              
                    if (true_mat->data[ind + i + j*10] == 'o') {

                        cell_value +=1;

                    }
                }
            }
        }
    }

    return (cell_value);
};

int print_board (const matrix* mat) {

    for(u8 i = 0; i < SIZE*SIZE; i++) {

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
        } else {
            printf("%c", mat->data[i]);
            printf(" ");
        }

        if ((i+1) % SIZE == 0) {

            printf("\n");

        }
    }
}

int scan_board (const matrix* ui_mat, const matrix* user_mat, const u8 input) {

    int row = input / 10;

    int col = input % 10;

    while (col < 10 && col >-1) {

        if (user_mat->data[col + row*SIZE] == 9) {

            break;

        } else {

            ui_mat->data[col + row*SIZE] = user_mat->data[col + row*SIZE];  
        }

        col--;

    }

    col = input % 10;

    while (col < 10 && col >-1) {

        if (user_mat->data[col + row*SIZE] == 9) {

            break;

        } else {

            ui_mat->data[col + row*SIZE] = user_mat->data[col + row*SIZE]; 
        }
        col++;

    }

    col = input % 10;

    while (row < 10 && row >-1) {

        if (user_mat->data[col + row*SIZE] == 9) {

            break;

        } else {

            ui_mat->data[col + row*SIZE] = user_mat->data[col + row*SIZE];  
        }
        row--;

    }

    row = input / 10;

    while (row < 10 && row >-1) {

        if (user_mat->data[col + row*SIZE] == 9) {

            break;

        } else {

            ui_mat->data[col + row*SIZE] = user_mat->data[col + row*SIZE];  
        }
        row++;

    }

}

int check_reveal_cell (const matrix* user_mat, const matrix* revelation, const matrix* ui_mat, const i8 ind) {

    int row = ind / 10;
    int col = ind % 10;

/*     int array[] = {-11, -10, -9, -1, 1, 0, 10, 11};

    if (revelation->data[ind] == 0) {

        for (u8 i = 0; i < 5; i++) {

            if (revelation->data[ind + array[i]] > -1 && revelation->data[ind + array[i]] < 100 && revelation->data[ind + array[i]] == 1) {
                
                if (user_mat->data[ind] < 9 && revelation->data[ind] == 
            }
        }
    } */

    if (revelation->data[ind] == 0) {

        return (0);

    } else if (user_mat->data[ind] == 0) {

        if (row > 0 && row < 9 && col > 0 && col < 9) {
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = -1; i < 2; i++){
                    if (user_mat->data[ind + (i) + (j)*10] < 9) {

                        revelation->data[ind + i +j*10] = 1;
                        ui_mat->data[ind + i +j*10] = user_mat->data[ind + i +j*10];

                    }
                }
            }
        } else if (row > 0 && row < 9 && col == 0) {
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = 0; i < 2; i++){
                    if (user_mat->data[ind + (i) + (j)*10] < 9) {

                        revelation->data[ind + i +j*10] = 1;
                        ui_mat->data[ind + i +j*10] = user_mat->data[ind + i +j*10];

                    }
                }
            }
        } else if (row > 0 && row < 9 && col == 9){
            for (i8 j = -1; j < 2; j++) {
                for (i8 i = -1; i < 1; i++){
                    if (user_mat->data[ind + (i) + (j)*10] < 9) {

                        revelation->data[ind + i +j*10] = 1;
                        ui_mat->data[ind + i +j*10] = user_mat->data[ind + i +j*10];

                    }
                }
            }

        } else if (col > 0 && col < 9 && (row == 0)) {
            for (i8 j = 0; j < 2; j++) {
                for (i8 i = -1; i < 2; i++){
                    if (user_mat->data[ind + (i) + (j)*10] < 9) {

                        revelation->data[ind + i +j*10] = 1;
                        ui_mat->data[ind + i +j*10] = user_mat->data[ind + i +j*10];

                    }
                }
            }
        } else if (col > 0 && col < 9 && (row == 9)) {
            for (i8 j = -1; j < 1; j++) {
                for (i8 i = -1; i < 2; i++){
                    if (user_mat->data[ind + (i) + (j)*10] < 9) {

                        revelation->data[ind + i +j*10] = 1;
                        ui_mat->data[ind + i +j*10] = user_mat->data[ind + i +j*10];

                    }
                }
            }
        } else if (ind == 0) {
            for (i8 j = 0; j < 2; j++) {
                for (i8 i = 0; i < 2; i++){
                    if (user_mat->data[ind + i + j*10] < 9) {

                        revelation->data[ind + i +j*10] = 1;
                        ui_mat->data[ind + i +j*10] = user_mat->data[ind + i +j*10];

                    }
                }
            }
        } else if (ind == 9){
            for (i8 j = 0; j < 2; j++) {
                for (i8 i = -1; i < 1; i++){
                    if (user_mat->data[ind + (i) + (j)*10] < 9) {

                        revelation->data[ind + i +j*10] = 1;
                        ui_mat->data[ind + i +j*10] = user_mat->data[ind + i +j*10];

                    }
                }
            }
        } else if (ind == 90) {
            for (i8 j = -1; j < 1; j++) {
                for (i8 i = 0; i < 2; i++){
                    if (user_mat->data[ind + (i) + (j)*10] < 9) {

                        revelation->data[ind + i +j*10] = 1;
                        ui_mat->data[ind + i +j*10] = user_mat->data[ind + i +j*10];

                    }
                }
            }
        } else if (ind == 99) {
            for (i8 j = -1; j < 1; j++) {
                for (i8 i = -1; i < 1; i++){
                    if (user_mat->data[ind + (i) + (j)*10] < 9) {

                        revelation->data[ind + i +j*10] = 1;
                        ui_mat->data[ind + i +j*10] = user_mat->data[ind + i +j*10];

                    }
                }
            }
        }
    }
};

int main () {

    matrix true_board = {SIZE, SIZE};
    matrix user_board = {SIZE, SIZE};
    matrix ui_board = {SIZE, SIZE};
    matrix revealed = {SIZE, SIZE};

    u8 index;
    b8 alive = true;
    const char *message = "Morreu";

    srand(time(NULL));

    true_board.data = (u8*)malloc(SIZE * SIZE * sizeof(u8));
    user_board.data = (u8*)malloc(SIZE * SIZE * sizeof(u8));
    ui_board.data = (u8*)malloc(SIZE * SIZE * sizeof(u8));
    revealed.data = (u8*)malloc(SIZE * SIZE * sizeof(u8));

    gen_true_board(&true_board, DIFFICULTY);
    print_board(&true_board);

    for (u8 i = 0; i < SIZE*SIZE; i++) {
        
        ui_board.data[i] = '.';
        revealed.data[i] = 0;
        user_board.data[i] = check_cell(&true_board, i);

    }

    print_board(&user_board);

    while (alive == true) {

        scanf("%d", &index);

        if (true_board.data[index] == 'o'){

            printf("%s", &message);
            alive = false;

        } else {

            //scan_board(&ui_board, &user_board, index);
            revealed.data[index] = 1;

            for (u8 i = 0; i < SIZE*SIZE; i++) {
                check_reveal_cell(&user_board, &revealed, &ui_board, i);
                check_reveal_cell(&user_board, &revealed, &ui_board, i);
            }

            print_board(&ui_board);
            print_board(&revealed);
            

        }
    }

    free(revealed.data);
    free(ui_board.data);
    free(true_board.data);
    free(user_board.data);

    return 0;

}
