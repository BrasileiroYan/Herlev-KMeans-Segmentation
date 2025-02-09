all: main

main: Main.o Histogram.o K-means.o LerDir.o PgmImage.o
	gcc -o main Main.o Histogram.o K-means.o LerDir.o PgmImage.o

Main.o: Main.c Histogram.h K-means.h PgmImage.h
	gcc -c Main.c

Histogram.o: Histogram.c Histogram.h 
	gcc -c Histogram.c

K-means.o: K-means.c K-means.h PgmImage.h
	gcc -c K-means.c

LerDir.o: LerDir.c LerDir.h
	gcc -c LerDir.c

PgmImage.o: PgmImage.c PgmImage.h
	gcc -c PgmImage.c

clean: 
	rm -rf *.o main
