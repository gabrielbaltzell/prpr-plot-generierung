main: main.o pgfplots.o
	gcc -o main main.o pgfplots.o
main.o: main.c pgfplots.h
	gcc -c -g main .c -o main.o
pgfplots.o: pgfplots.c pgfplots.h
	gcc -c -g pgfplots.c
