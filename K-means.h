#ifndef KMEANS_H
#define KMEANS_H

// Estruturas dos Pixels e Clusters
typedef struct {
    int valor; // Intensidade de pixel (escala de cinza)
} Pixel;

typedef struct {
    int valor; // Valor do centróide (média dos pixels atribuídos)
    int count; // Contagem de pontos atribuídos ao centróide
} Cluster;

double distance(Pixel p1, Cluster cluster);
void initializeCentroids(Cluster *centroides, int k, int min_valor, int max_valor);
void assignClusters(Pixel *pixels, int n, Cluster *centroides, int k);
void updateCentroids(Cluster *centroides, int k);
int checkConvergence(Cluster *centroides, Cluster *antigoCentroides, int k);
void kMeans(Pixel *pixels, int n, Cluster *centroides, int k);
 
#endif // KMEANS_H