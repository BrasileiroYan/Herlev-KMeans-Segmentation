all: main

main: Main.o Histogram.o Kmeans.o LerDir.o PgmImage.o
	gcc -o main Main.o Histogram.o Kmeans.o LerDir.o PgmImage.o

Main.o: Main.c Histogram.h Kmeans.h PgmImage.h
	gcc -c Main.c

Histogram.o: Histogram.c Histogram.h 
	gcc -c Histogram.c

Kmeans.o: Kmeans.c Kmeans.h PgmImage.h
	gcc -c Kmeans.c

LerDir.o: LerDir.c LerDir.h
	gcc -c LerDir.c

PgmImage.o: PgmImage.c PgmImage.h
	gcc -c PgmImage.c

clean: 
	rm -rf *.o main
