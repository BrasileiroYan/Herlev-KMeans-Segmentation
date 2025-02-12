#ifndef PGMIMAGE_H
#define PGMIMAGE_H

typedef struct {
    int tipo;        // Tipo da imagem PGM (P2 ou P5)
    int c, r;        // Largura (colunas) e altura (linhas)
    int mv;          // Valor máximo do pixel (normalmente 255)
    unsigned char *pData; // Dados da imagem (pixels)
} PGMImage;

void readPGMImage(PGMImage *pImg, const char *fileName);
void writePGMImage(PGMImage *pImg, const char *fileName);
void viewPGMImage(PGMImage *pImg);
void freePGMImage(PGMImage *pImg);

#endif
