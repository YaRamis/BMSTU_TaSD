#ifndef _MY_UTILS_H_
#define _MY_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 40 // Максимальная длина вводимой строки "+123456789012345678901234567890E+99999\n\0"

#define MAX_MANTISA_DIGITS 30 // Максимальное количестов цифр в мантисе
#define MAX_MANTISA_LEN 32 // С учетом точки и знака мантисы
#define MAX_ORDER_LEN 6 // С учетом знака порядка

#define INPUT_OVERFLOW 2
#define TOO_MANY_POINTS 3
#define IS_NOT_NUM_M 4
#define IS_NOT_NUM_O 5
#define TOO_LONG_ORDER 6
#define TOO_LONG_MANTISA 7

typedef short mantisa_t[MAX_MANTISA_DIGITS];

typedef struct          
{
    char sign_m;
    mantisa_t mantisa;
    int order;
} huge_float_t;

#endif