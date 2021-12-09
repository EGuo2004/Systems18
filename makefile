all: main.o
	gcc -o eighteen main.o

main.o: main.c
	gcc -c main.c

run:
	./eighteen