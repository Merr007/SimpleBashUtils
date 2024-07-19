FLAGS=-Wall -Werror -Wextra

all: s21_grep

s21_grep: s21_grep.o
	gcc $(FLAGS) s21_grep.o -o s21_grep

s21_grep.o: 
	gcc $(FLAGS) -c ./s21_grep.c -o s21_grep.o

clean:
	rm -rf *.o s21_grep
rebuild: clean all