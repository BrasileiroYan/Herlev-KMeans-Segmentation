#ifndef PGMIMAGE_H
#define PGMIMAGE_H

// estrutura pgm
struct pgm{               // define como a imagem pgm será armazenada
    int tipo;             // tipo de imagem (2 para textual e 5 para binário)
    int c;                // quantidade de colunas
    int r;                // quantidade de linhas
    int mv;               // máximo valor dos pixels (255)
    unsigned char *pData; // vetor dos dados da imagem
};

// protótipos das funções que serão utilizadas:
void readPGMImage(struct pgm *pImg, char *fileName);  
void writePGMImage(struct pgm *pImg, char *fileName);
void viewPGMImage(struct pgm *pImg);
void freePGMImage(struct pgm *pImg);

#endif // PGMIMAGE_H