CFLAGS=-Wall -g -DNDEBUG

all: ex1 ex3 ex7 ex8 ex9 ex10 ex11 ex12 ex13 ex14 ex15 ex16 ex17 ex18 ex19 ex22_main ex23 ex24 ex25

ex22_main: ex22.o

clean:
	rm -f ex1 ex3 ex7 ex8 ex9 ex10 ex11 ex12 ex13 ex14 ex15 ex16 ex17 ex18 ex19 ex22_main ex23 ex24 ex25
