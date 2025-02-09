#include "k-means.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "pgmimage.h"

#define MAX_ITERATIONS 1000
#define THRESHOLD 0.0001

// Estruturas dos Pixels e Clusters
typedef struct {
    int valor; // Intensidade de pixel (escala de cinza)
} Pixel;

typedef struct {
    int valor; // Valor do centróide (média dos pixels atribuídos)
    int count; // Contagem de pontos atribuídos ao centróide
} Cluster;

// Função para calcular a distância euclidiana
double distance(Pixel p1, Cluster cluster) {
    return fabs(p1.valor - cluster.valor); // Retorna o módulo da distância 
}

// Função para inicializar k centróides aleatoriamente
void initializeCentroids(Cluster *centroides, int k, int min_valor, int max_valor) {
    srand(time(NULL)); // Inicializa a semente do random
    for (int i = 0; i < k; i++) {
        centroides[i].valor = min_valor + rand() % (max_valor - min_valor + 1);
        centroides[i].count = 0;
    }
}

// Função para atribuir pixels aos centróides
void assignClusters(Pixel *pixels, int n, Cluster *centroides, int k, int *indiceCluster) {
    // Zera os valores dos centróides antes de reatribuir
    for (int i = 0; i < k; i++) {
        centroides[i].valor = 0;  // Reinicializa soma dos valores dos centróides
        centroides[i].count = 0;
    }

    for (int i = 0; i < n; i++) {
        double menorDistancia = __DBL_MAX__;
        int clusterIndex = 0;
        for (int j = 0; j < k; j++) {
            double distancia = distance(pixels[i], centroides[j]);
            if (distancia < menorDistancia) {
                menorDistancia = distancia;
                clusterIndex = j;
            }
        }

        indiceCluster[i] = clusterIndex;

        // Atribui o pixel ao centróide mais próximo
        centroides[clusterIndex].valor += pixels[i].valor;
        centroides[clusterIndex].count++;
    }
}

// Função para atualizar os centróides
void updateCentroids(Cluster *centroides, int k) {
    for (int i = 0; i < k; i++) {
        if (centroides[i].count > 0) {
            centroides[i].valor /= centroides[i].count;
        }
    }
}

// Função que verifica convergência dos centroides
int checkConvergence(Cluster *centroides, Cluster *antigoCentroides, int k) {
    for (int i = 0; i < k; i++) {
        if ((fabs(centroides[i].valor - antigoCentroides[i].valor)) > THRESHOLD) {
            return 0;
        }
    }

    return 1;
}

// Função principal do k-means
void kMeans(Pixel *pixels, int n, Cluster *centroides, int k, int *indiceCluster) {
    
    Cluster antigoCentroides[k];

    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        // Armazena o centroide atual em um antigo para comparar nas iterações
        for (int i = 0; i < k; i++) {
            antigoCentroides[i] = centroides[i];
        }

        // Atribui pixels aos clusters e recalcula os centróides
        assignClusters(pixels, n, centroides, k, indiceCluster);
        
        // Atualiza os centróides
        updateCentroids(centroides, k);

        // Verifica se os centróides convergiram
        if (checkConvergence(centroides, antigoCentroides, k)) {
            puts("Os Centróides convergiram!\n");
            break;
        }

        // Atualiza o valor de cada pixel para o valor do centróide de índice correspondente
        for (int i = 0; i < n; i++) {
            pixels[i].valor = centroides[indiceCluster[i]].valor;
        }
    }
}
