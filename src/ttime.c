#include <stdio.h>
#include <time.h>

#define QTDIMG 100

void tempo(){
	int k;
	clock_t begin, end;
	double time_per_img, time_total=0;
	long long int a = 999999999;

	begin = clock();

	for (k=0; k<QTDIMG; k++){

		// Leitura

		
		while(a){
			a--;
		}

		

	}

	end = clock();

	time_total = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Tempo Total: %lf\n",time_total);

}
