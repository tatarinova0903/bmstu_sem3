CFILES := $(wildcard *.c)
OBJECTS := $(CFILES:%.c=%.o)
FLAGS := -pedantic -Wall -Werror -Wextra -Wvla -Wfloat-equal -Wfloat-conversion -std=c99

app.exe: $(OBJECTS)
	gcc $(FLAGS) $(OBJECTS) -o app.exe

%.o: %.c
	gcc $(FLAGS) -c $<

run: app.exe
	./app.exe
	
# .PHONY - чтобы не было конфликтов с файлами
.PHONY : clean run
clean:
	$(RM) *.o *.exe

run:
	dot -v -Tpng -opic graph > /dev/null