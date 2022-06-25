#!/bin/sh

rm -f ./*.gcov ./*.gcda
cd func_tests || return
./all_test.sh
cd ..
