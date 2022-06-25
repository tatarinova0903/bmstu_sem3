#!/bin/sh

num=$1
file_in="neg_${num}_in.txt"
file_out="out.txt"

../app.exe < "$file_in" > "$file_out"
rc=$?

if [ ${rc} -ne 0 ]
then
  echo NEG TEST "$num" PASSED rc == ${rc}
else
  echo NEG TEST "$num" FAILED rc == 0
fi
