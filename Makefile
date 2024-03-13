build: main

main: lists.o files.o main.c
	gcc -o lanParty main.c lists.o files.o

lists.o: lists.c lists.h
	gcc -c lists.c

files.o: files.c files.h
	gcc -c files.c

clean:
	rm lanParty *.o

.PHONY: clean
