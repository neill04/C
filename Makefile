testList: main.o list.o
	gcc -o testList main.o list.o
main.o: main.c list.h
	gcc -c -g main.c
list.o: list.c list.h
	gcc -c -g list.c
clean:
	rm *o testList
