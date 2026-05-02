#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define Color_Red "\x1b[31m" // Color Start
#define Color_end "\x1b[0m" // To flush out prev settings

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

int main () {

    matrix true_board = {SIZE, SIZE};
    matrix user_board = {SIZE, SIZE};

    srand(time(NULL));

    true_board.data = (u8*)malloc(SIZE * SIZE * sizeof(u8));
    user_board.data = (u8*)malloc(SIZE * SIZE * sizeof(u8));

    for (u8 i = 0; i < SIZE*SIZE; i++) {

        if ((rand() % 100) < (100 - DIFFICULTY)) {

            true_board.data[i] = '.';

        } else {

            true_board.data[i] = 'o';

        };

        printf("%c", true_board.data[i]);
        printf(" ");

        if ((i+1) % SIZE == 0) {

            printf("\n");

        }

    }

    for(u8 i = 0; i < SIZE*SIZE; i++) {

        user_board.data[i] = check_cell(&true_board, i);

        if (user_board.data[i] == 9){
            printf("%s%d%s",Color_Red,user_board.data[i],Color_end);
            printf(" ");
        } else {
            printf("%d", user_board.data[i]);
            printf(" ");
        }

        if ((i+1) % SIZE == 0) {

            printf("\n");

        }
    }

    free(true_board.data);
    free(user_board.data);

    return 0;

}
