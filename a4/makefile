# compiler
CC = gcc
# executables out
OUT = bubbleSort selectionSort quickSort

all:  a4.o bubble.o selection.o quick.o
	${CC} a4.o bubble.o -o bubbleSort
	${CC} a4.o selection.o -o selectionSort
	${CC} a4.o quick.o -o quickSort

bubble: a4.o bubble.o
	${CC} a4.o bubble.o -o bubbleSort

selection: a4.o selection.o
	${CC} a4.o selection.o -o selectionSort

quick: a4.o quick.o
	${CC} a4.o quick.o -o quickSort

a4.o: a4.c
	${CC} -c a4.c sort.c sort.h

bubble.o: bubble.c
	${CC} -c bubble.c

quick.o: quick.c
	${CC} -c quick.c

selection.o: selection.c
	${CC} -c selection.c

sort.o: sort.c
	${CC} -c sort.c

#clean without deleting executables
cleanIntermediate:
	rm -f *.gch *.o

clean:
	rm -f *.gch *.o ${OUT}