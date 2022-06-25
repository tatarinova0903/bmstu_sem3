CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -Wextra -Wfloat-conversion -Wfloat-equal
DEP := $(wildcard out/*.d)
SRCS := $(wildcard *.c)

app.exe: stack_array.o stack_list.o word.o main.o
	$(CC) -o $@ $^

test.exe: stack_array.o stack_list.o word.o test.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -Iinc $(FLAGS) -c $< -o $@

%.d: %.c
	$(CC) -M $< > $@

include $(DEP)

.PHONY : clean
clean:
	rm *.exe *.o
