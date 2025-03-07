#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgmimage.h"
#include "kmeans.h"
#include "lerdir.h"
#include "ttime.h"

void clusterizarImagem(const char *imagePath, int k);

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        printf("Uso: %s <caminho_do_diretorio> <numero_de_clusters>\n", argv[0]);
        exit(1);
    }

    int k = atoi(argv[2]);
    if(k <= 0){
        printf("Erro: numero de clusters deve ser maior que zero!");
        exit(1);
    }

    tempo();

    processDirectory(argv[1], k);    

    tempo();

    return 0;
}

void clusterizarImagem(const char *imagePath, int k){
    
    PGMImage img;

    // Le a imagem PGM
    readPGMImage(&img, imagePath);

    // Aplica o K-Means
    kMeans(&img, k);

    char outputPath[1024];
    strcpy(outputPath, imagePath);
    char *ext = strrchr(outputPath, '.'); // Encontra a extensao do arquivo (.pgm)
    if (ext) {
        *ext = '\0'; // Remove a extensao
    }
    sprintf(outputPath, "%s_k%d.pgm", outputPath, k); // Adiciona sufixo com o numero de clusters

    // Salva a imagem segmentada
    writePGMImage(&img, outputPath);

    // Libera a memoria alocada
    freePGMImage(&img);
}
