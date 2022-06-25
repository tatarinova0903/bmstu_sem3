#!/bin/sh

num=$1
file_in="pos_${num}_in.txt"
file_out="pos_${num}_out.txt"

../app.exe < "$file_in" > out.txt
rc=$?

if [ ${rc} -ne 0 ]
then 
    echo POS TEST "$num" FAILED rc == ${rc}
else
    compare=$(python3 comparator.py out.txt "${file_out}")
    if [ "${compare}" -eq 0 ]
    then
        echo POS TEST "$num" FAILED rc == 0
        echo
        cat "${file_out}"
        echo
        cat out.txt
    else
        echo POS TEST "$num" PASSED rc == 0
    fi
fi
