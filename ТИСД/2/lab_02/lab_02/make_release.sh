#!/bin/sh

keys="-Wall -Werror -Wextra -Wpedantic -Wfloat-conversion -Wvla -Wfloat-equal"

gcc-10 -std=c99 ${keys} -c main.c
gcc-10 -std=c99 ${keys} -c car_t.c
gcc-10 main.o car_t.o -o app.exe
