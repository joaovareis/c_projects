#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

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

int main() {

    int myNumbers[] = {10, 20, 30, 40, 50};
    int length = sizeof(myNumbers) / sizeof(myNumbers[0]); // Calculate length

    for (int i = 0; i < 5; i++) {
        printf("%d\n", myNumbers[i]);
    }
    return 0;
}