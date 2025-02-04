#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "pgmimage.h"

void readPGMImage(struct pgm *pImg, char *fileName);  
void writePGMImage(struct pgm *pImg, char *fileName);
void viewPGMImage(struct pgm *pImg);
void freePGMImage(struct pgm *pImg);
#define MAX_ITERATIONS 1000
#define THRESHOLD 0.0001

// Estruturas
typedef struct {
    int x, y; // Coordenadas do pixel (se necessário)
    int valor; // Intensidade de pixel (escala de cinza)
} Pixel;

typedef struct {
    int valor; // Valor do centróide (média dos pixels atribuídos)
    int count; // Contagem de pontos atribuídos ao centróide
} Cluster;

// Função para calcular a distância euclidiana
double distancia(Pixel p1, Cluster c) {
    return fabs(p1.valor - c.valor);
}

// Função para inicializar k centróides aleatoriamente
void inicializarCentroides(Cluster *centroides, int k, int min_val, int max_val) {
    srand(time(NULL)); // Inicializa a semente do random
    for (int i = 0; i < k; i++) {
        centroides[i].valor = min_val + rand() % (max_val - min_val + 1);
        centroides[i].count = 0;
    }
}

// Função para atribuir pixels aos centróides
void atribuirClusters(Pixel *pixels, int n, Cluster *centroides, int k) {
    for (int i = 0; i < n; i++) {
        double menorDistancia = __DBL_MAX__;
        int clusterIndex = 0;
        for (int j = 0; j < k; j++) {
            double dist = distancia(pixels[i], centroides[j]);
            if (dist < menorDistancia) {
                menorDistancia = dist;
                clusterIndex = j;
            }
        }
        // Atribui o pixel ao centróide mais próximo
        centroides[clusterIndex].count++;
        centroides[clusterIndex].valor += pixels[i].valor;
    }
}

// Função para atualizar os centróides
void atualizarCentroides(Cluster *centroides, int k) {
    for (int i = 0; i < k; i++) {
        if (centroides[i].count > 0) {
            centroides[i].valor /= centroides[i].count;
        }
    }
}

// Função principal do k-means
void kMeans(Pixel *pixels, int n, Cluster *centroides, int k, int max_iter) {
    for (int iter = 0; iter < max_iter; iter++) {
        // Zera os valores dos centroides antes de reatribuir
        for (int i = 0; i < k; i++) {
            centroides[i].valor = 0;
            centroides[i].count = 0;
        }

        // Atribui pixels aos clusters
        atribuirClusters(pixels, n, centroides, k);
        
        // Atualiza os centroides
        atualizarCentroides(centroides, k);

        // Verifica se houve mudança significativa nos centroides
        // (Pode ser adicionado um critério de convergência)
    }
}

int main(int argc, char *argv[]) {
    struct pgm img;
    if(argc != 3){
        printf("Formato: \n\t %s <imagemEntrada.pgm> <imagemSaida.pgm>\n", argv[0]);
        exit(1);
    }
    readPGMImage(&img, argv[1]);
    
    writePGMImage(&img, argv[2]);
    
    viewPGMImage(&img);
    int k = 3; // Número de clusters
    int n = 1000; // Número de pixels da imagem (substituir por valor real)
    Pixel *pixels = (Pixel *)malloc(n * sizeof(Pixel)); // Supondo que você tenha os pixels da imagem
    Cluster *centroides = (Cluster *)malloc(k * sizeof(Cluster));
    
    // Inicializa os centróides aleatoriamente
    inicializarCentroides(centroides, k, 0, 255);
    
    // Rodando o K-means
    kMeans(pixels, n, centroides, k, MAX_ITERATIONS);

    // Aqui você pode aplicar os clusters aos pixels e gerar a imagem resultante
    // Salvar a imagem de volta no formato PGM
    printf("K-means finalizado.\n");

    free(pixels);
    free(centroides);
    return 0;
}
