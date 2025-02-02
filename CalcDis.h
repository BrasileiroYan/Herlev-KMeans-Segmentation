#ifndef CALCDIS_H
#define CALCDIS_H

struct point{ // define a estrutura de cada ponto do vetor imagem
    int x;
    int y;
};

typedef struct point point;

double calculate_distance_points(point p1, point pCentroide); // protótipo da função implementadada

#endif // CALCDIS_H