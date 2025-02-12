all: main  

main: output/Main.o output/Kmeans.o output/LerDir.o output/PgmImage.o output/ttime.o
	gcc -o bin/Main.exe output/Main.o output/Kmeans.o output/LerDir.o output/PgmImage.o output/ttime.o

output/Main.o: src/Main.c include/Kmeans.h include/PgmImage.h include/ttime.h
	gcc -c src/Main.c -o output/Main.o -Iinclude

output/Kmeans.o: src/Kmeans.c include/Kmeans.h include/PgmImage.h
	gcc -c src/Kmeans.c -o output/Kmeans.o -Iinclude

output/LerDir.o: src/LerDir.c include/LerDir.h
	gcc -c src/LerDir.c -o output/LerDir.o -Iinclude

output/PgmImage.o: src/PgmImage.c include/PgmImage.h
	gcc -c src/PgmImage.c -o output/PgmImage.o -Iinclude

output/ttime.o: src/ttime.c include/ttime.h
	gcc -c src/ttime.c -o output/ttime.o -Iinclude

clean:
	rm -rf output/*.o bin/Main.exe

