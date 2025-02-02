#include "calcdis.h"
#include <math.h>

double calculate_distance_points(point p1, point pCentroide){

    return sqrt(pow(p1.x - pCentroide.x, 2) + pow(p1.y - pCentroide.y, 2));

}