#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

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

#define SIZE 25

void clear_screen ();

void print_screen ();

void hide_cursor (const u8 hide);

int main() {

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;
    matrix screen = {SIZE, SIZE};
    u64 snake_size = 1;
    int snake_head_pos[2] = {(SIZE/2), (SIZE/2)};
    u8 last_command = 0;
    u8 snake_speed = 0;
    
    screen.data = (u8*)malloc( SIZE * SIZE * sizeof(u8) );

    for (u64 i = 0; i < SIZE*SIZE; i++) {

        screen.data[i] = '.';

    }

    screen.data[ snake_head_pos[0] + snake_head_pos[1]*SIZE ] = '#';

    hide_cursor(1);

    while (1) {

        DWORD numEvents = 0;
        GetNumberOfConsoleInputEvents(hInput, &numEvents);

        if (numEvents > 0) {
            if (ReadConsoleInput(hInput, irInBuf, 128, &cNumRead)) {
                for (DWORD i = 0; i < cNumRead; i++) {
                    if (irInBuf[i].EventType == KEY_EVENT) {
                        KEY_EVENT_RECORD ker = irInBuf[i].Event.KeyEvent;
                        
                        if (ker.bKeyDown) {

                            if ((ker.wVirtualKeyCode == 37) || (ker.wVirtualKeyCode == 38) || (ker.wVirtualKeyCode == 39) || (ker.wVirtualKeyCode == 40)) {

                                last_command = ker.wVirtualKeyCode;

                            }

                        } /* else {

                            printf("Tecla solta: 0x%X\n", ker.wVirtualKeyCode);
                        } */

                        if (ker.wVirtualKeyCode == VK_ESCAPE) return 0;
                    }
                }
            }
        }

        if (snake_speed == 0) {

            if (last_command == 38) {

                snake_head_pos[1] -= 1;
                screen.data[ snake_head_pos[0] + (snake_head_pos[1] + 1)*SIZE ] = '.';

                if (snake_head_pos[1] == -1) {

                    snake_head_pos[1] = SIZE - 1;
                    screen.data[ snake_head_pos[0] + snake_head_pos[1]*SIZE ] = '#';

                } else {

                    screen.data[ snake_head_pos[0] + snake_head_pos[1]*SIZE ] = '#';
                }

            } else if (last_command == 40) {

                snake_head_pos[1] += 1;
                screen.data[ snake_head_pos[0] + (snake_head_pos[1] - 1)*SIZE ] = '.';

                if (snake_head_pos[1] == SIZE) {

                    snake_head_pos[1] = 0;
                    screen.data[ snake_head_pos[0] + snake_head_pos[1]*SIZE ] = '#';

                } else {
                    
                    screen.data[ snake_head_pos[0] + snake_head_pos[1]*SIZE ] = '#';
                }

            } else if (last_command == 37) {

                snake_head_pos[0] -= 1;
                screen.data[ (snake_head_pos[0] + 1) + snake_head_pos[1]*SIZE ] = '.';

                if (snake_head_pos[0] == -1) {

                    snake_head_pos[0] = SIZE - 1;
                    screen.data[ (snake_head_pos[0]) + snake_head_pos[1]*SIZE ] = '#';

                } else {

                    screen.data[ (snake_head_pos[0]) + snake_head_pos[1]*SIZE ] = '#';

                }

            } else if (last_command == 39) {

                snake_head_pos[0] += 1;
                screen.data[ (snake_head_pos[0] - 1) + snake_head_pos[1]*SIZE ] = '.';

                if (snake_head_pos[0] == SIZE) {

                    snake_head_pos[0] = 0;
                    screen.data[ (snake_head_pos[0]) + snake_head_pos[1]*SIZE ] = '#';

                } else {

                    screen.data[ (snake_head_pos[0]) + snake_head_pos[1]*SIZE ] = '#';

                }
            }
        }

        Sleep(10);
        snake_speed += 1;

        if (snake_speed == 1) {
            snake_speed = 0;
            }
    
        clear_screen();
        print_screen(&screen);
    }

    hide_cursor(1);
    free(screen.data);
    return 0;

}

void print_screen (const matrix* mat) {

    for(i64 i = 0; i < SIZE*SIZE; i++) {

        if (mat->data[i] == '.'){
            printf("%s%c%s",GRAY_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == 'o') {
            printf("%s%c%s",RED_TEXT,mat->data[i],COLOR_END);
            printf(" ");

        } else if (mat->data[i] == '#') {
            printf("%s%c%s",GREEN_TEXT,mat->data[i],COLOR_END);
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

void clear_screen () {

    printf("\x1b[H");
    //system("cls");
    
}

void hide_cursor (const u8 hide) {

    if (hide == 1) {
        
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);

    } else {

        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = TRUE;
        SetConsoleCursorInfo(consoleHandle, &info);

    }

}