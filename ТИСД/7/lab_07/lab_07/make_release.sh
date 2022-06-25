#!/bin/sh

keys="-Wall -Werror -Wextra -Wpedantic -Wfloat-conversion -Wvla -Wfloat-equal"

gcc -std=c99 ${keys} -c main.c
gcc main.o -o app.exe
./app.exe
rc=$?
dot -Tpng -opic graph
