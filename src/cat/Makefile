FLAGS=-Wall -Werror -Wextra

all: s21_cat

s21_cat: s21_cat.o
	gcc $(FLAGS) s21_cat.o -o s21_cat

s21_cat.o: 
	gcc $(FLAGS) -c ./s21_cat.c -o s21_cat.o

clean:
	rm -rf *.o s21_cat
rebuild: clean all