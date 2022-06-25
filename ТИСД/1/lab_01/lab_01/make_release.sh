#!/bin/sh

keys="-Wall -Werror -Wextra -Wpedantic -Wfloat-conversion -Wvla -Wfloat-equal"

gcc -std=c99 ${keys} -c main.c
gcc -std=c99 ${keys} -c bigfloat.c
gcc -std=c99 ${keys} -c string_t.c
gcc -std=c99 ${keys} -c int_array.c
gcc-10 -std=c99 ${keys} -c int.c
gcc main.o bigfloat.o string_t.o int_array.o int.o -o app.exe
