#include <stdio.h>
#include "PgmImage.h"

#define TAM 256

// Função para calcular o histograma da Imagem
void histogramImage(struct pgm *pImg){
    int frequencia[TAM] = {0};
    
    for(int i=0; i<(pImg->c * pImg->r); i++){
        frequencia[pImg->pData[i]]++;
    }

    for(int i=0; i<TAM; i++){
        printf("[%d]: Frequencia[%d]\n", i, frequencia[i]);
    }

} 
