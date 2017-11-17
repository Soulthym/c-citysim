ALL: EXE RM LANCEMENT CLEAN
DEBUG: EXE RM LANCEMENTVAL CLEAN

libs.o: lib/libs.c lib/libs.h
	gcc -Wall -o libs.o -c lib/libs.c -g -lm

main.o: main.c main.h
	gcc -Wall -o main.o -c main.c -g -lm

EXE: main.o libs.o main.h
	gcc -Wall -o EXE main.o libs.o -g -lm

LANCEMENT:
	./EXE

LANCEMENTVAL:
	valgrind --leak-check=full ./EXE

RM:
	rm *.o

CLEAN:
	rm EXE
#NB: when using valgrind to debug: use it on ./EXE not make (rm causes a leak)

