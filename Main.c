#include <stdio.h>
#include <stdlib.h>
#include "pgmimage.h"
#include "k-means.h"

int main(int argc, char *argv[]) {
    
    struct pgm img;
    
    if(argc != 3){
        printf("Formato: \n\t %s <imagemEntrada.pgm> <imagemSaida.pgm>\n", argv[0]);
        exit(1);
    }
    
    readPGMImage(&img, argv[1]);
    
    writePGMImage(&img, argv[2]);
    
    viewPGMImage(&img);

    freePGMImage(&img);
    
    int k = 3; // Número de clusters
    int n = img.c * img.r; // Número de pixels da imagem
    
    Pixel *pixels = (Pixel *)malloc(n * sizeof(Pixel));
    if(pixels == NULL){
        puts("Erro em alocação de memória.");
        exit(2);
    }

    Cluster *centroides = (Cluster *)malloc(k * sizeof(Cluster));
    if(centroides == NULL){
        puts("Erro em alocação de memória.");
        exit(3);
    }    
    
    // Atribui cada valor da matriz da imagem ao respectivo array pixels
    for(int i = 0; i<n; i++){
        pixels[i].valor = img.pData[i]; 
    }

    // Inicializa os centróides aleatoriamente
    initializeCentroids(centroides, k, 0, 255);
    
    // Rodando o K-means
    kMeans(pixels, n, centroides, k);

    // Aqui você pode aplicar os clusters aos pixels e gerar a imagem resultante
    // Salvar a imagem de volta no formato PGM
    printf("K-means finalizado.\n");

    free(pixels);
    free(centroides);
    return 0;
}