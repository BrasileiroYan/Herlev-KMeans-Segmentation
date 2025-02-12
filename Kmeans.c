#include "kmeans.h"
#include "pgmimage.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_ITERATIONS 1000
#define THRESHOLD 0.0001

typedef struct{
    int count;
    int intensity;
}Cluster;

// Função principal do K-Means
void kMeans(PGMImage *image, int k) { 
    int n = image->c * image->r; // 🔹 Número total de pixels
    unsigned char *pixels = image->pData; // 🔹 Acessa diretamente os valores dos pixels

    // Aloca dinamicamente os centróides
    Cluster *centroides = (Cluster *)malloc(k * sizeof(Cluster));
    Cluster *antigoCentroides = (Cluster *)malloc(k * sizeof(Cluster));
    if (!centroides || !antigoCentroides) {
        perror("Erro ao alocar memoria para os centroides.");
        exit(1);
    }

    srand(time(NULL)); // 🔹 Inicializa a semente do random

    // Determina os valores mínimo e máximo dos pixels
    int min_valor = 255, max_valor = 0;
    for (int i = 0; i < n; i++) {
        if (pixels[i] < min_valor) min_valor = pixels[i];
        if (pixels[i] > max_valor) max_valor = pixels[i];
    }

    // Inicializa k centróides aleatoriamente no intervalo [min, max]
    for (int i = 0; i < k; i++) {
        centroides[i].intensity = min_valor + rand() % (max_valor - min_valor + 1);
        centroides[i].count = 0;
    }

    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        // Salva os valores antigos para verificar a convergência
        for (int i = 0; i < k; i++) {
            antigoCentroides[i] = centroides[i];
            centroides[i].intensity = 0;
            centroides[i].count = 0;
        }

        // Atribui cada pixel ao centróide mais próximo
        for (int i = 0; i < n; i++) {
            double menorDistancia = INFINITY;
            int clusterIndex = 0;
            
            for (int j = 0; j < k; j++) {
                double distancia = fabs(pixels[i] - centroides[j].intensity);
                if (distancia < menorDistancia) {
                    menorDistancia = distancia;
                    clusterIndex = j;
                }
            }

            // Atualiza a soma e a contagem para o cálculo da média
            centroides[clusterIndex].intensity += pixels[i];
            centroides[clusterIndex].count++;

            // Atualiza o valor do pixel para o valor do centróide do cluster
            pixels[i] = centroides[clusterIndex].intensity;
        }

        // Atualiza os centróides com a média dos valores atribuídos
        for (int i = 0; i < k; i++) {
            if (centroides[i].count > 0) {
                centroides[i].intensity /= centroides[i].count;
            }
        }

        // Verifica se os centróides convergiram
        int convergiu = 1;
        for (int i = 0; i < k; i++) {
            if (fabs(centroides[i].intensity - antigoCentroides[i].intensity) > THRESHOLD) {
                convergiu = 0;
                break;
            }
        }
        
        if (convergiu) {
            puts("Os Centroides convergiram!\n");
            break;
        }
    }

    // Libera memória alocada dinamicamente
    free(centroides);
    free(antigoCentroides);
}
