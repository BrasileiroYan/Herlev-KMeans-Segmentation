#include "kmeans.h"
#include "pgmimage.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_ITERATIONS 1000
#define THRESHOLD 0.0001

// Funçao do K-Means
void kMeans(PGMImage *pImg, int k){ 
 
    int tamImg = pImg->c * pImg->r; // Tamanho da imagem(lin x col) 
    
    // Aloca memoria  para pixels e os centroides
    unsigned int *centroides = (unsigned int *)malloc(k * sizeof(unsigned int));
    unsigned int *antigoCentroides = (unsigned int *)malloc(k * sizeof(unsigned int));
 
    // Verifica se a alocaçao funcionou
    if(!(centroides) || !(antigoCentroides)){
        perror("Erro ao alocar memoria para os centroides.");
        exit(1);
    }

    srand(time(NULL)); // Define a semente randomica
    
    // Inicia os centroides aleatoriamente
    int valorK[k]; // Um vetor que armazena os valores de cada k 
    for(int i=0; i<k; i++){
        valorK[i] = pImg->pData[rand() % tamImg]; // Cada posiçao do vetor recebe um valor aleatorio da matriz da imagem 
        centroides[i] = valorK[i]; // Cada centroide recebe o valor correspondente 
    }

    for(int iter=0; iter<MAX_ITERATIONS; iter++){
        // Salva os valores antigos para verificar a convergencia posteriormente
        for (int i=0; i<k; i++){
            antigoCentroides[i] = centroides[i];
        }

        // Define e inicializa variaveis de somatorio e contagem para cada centroide
        unsigned long somatorioCentroides[k];
        unsigned int contCentroides[k];

        for(int i=0; i<k; i++){
            somatorioCentroides[i] = 0;
            contCentroides[i] = 0;
        }
        
        // Atribui cada pixel ao centroide mais proximo
        for(int i=0; i<tamImg; i++){
            unsigned int menorDistancia = abs(pImg->pData[i] - centroides[0]);
            int centroideIndice = 0;
            
            for(int j=0; j<k; j++){
                unsigned int distancia = abs(pImg->pData[i] - centroides[j]);
                if(distancia < menorDistancia){
                    menorDistancia = distancia;
                    centroideIndice = j;
                }
            }

            // Calcula o somatorio de pixels e atualiza a contagem de cada centroide
            somatorioCentroides[centroideIndice] += pImg->pData[i];
            contCentroides[centroideIndice]++;

            // Atualiza o valor do pixel para o valor do centroide do cluster
            pImg->pData[i] = centroides[centroideIndice];
        }

        // Atualiza os centroides para a media dos pixels atribuidos
        for(int i=0; i<k; i++){
            if(contCentroides[i]>0){
                centroides[i] = somatorioCentroides[i] / contCentroides[i];
            }
        }

        // Verifica a variacao dos centroides
        double maiorVariacao = 0;
        for(int i=0; i<k; i++){
            double variacao = fabs((double)centroides[i] - antigoCentroides[i]);

            if(variacao > maiorVariacao){
                maiorVariacao = variacao;
            }
        }

        // Se a varicao for um valor infimo, mostra mensagem ao usuario e finaliza o laco de iteracao
        if(maiorVariacao < THRESHOLD){
            printf("Centroides convergiram com %d iteracoes!\n", iter+1);
            fflush(stdout);
            break;
        }
    }

    // Libera memoria alocada dinamicamente
    free(centroides);
    free(antigoCentroides);
}
