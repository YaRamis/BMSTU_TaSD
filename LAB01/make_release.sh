#!/bin/sh
keys="-std=c99 -Werror -Wall -Wpedantic -Wextra -Wvla -c"
gcc $keys main.c
gcc $keys multiply.c
gcc $keys normalization.c
gcc $keys print_input.c
gcc $keys validation.c
gcc -o app.exe *.o
