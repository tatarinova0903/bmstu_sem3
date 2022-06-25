#!/bin/sh

count=$(find . -type f -name "pos*in.txt" | wc -l)
i=1
while [ $i -le "$count" ]; do
  num=$(printf "%02d" ${i})
  
  ./pos_test.sh "$num"

  i=$(( i + 1 ))
done

echo

count=$(find . -type f -name "neg*in.txt" | wc -l)

i=1
while [ $i -le "$count" ]; do
  num=$(printf "%02d" ${i})

  ./neg_test.sh "$num"

  i=$(( i + 1 ))
done
