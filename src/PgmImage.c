#include "pgmimage.h"
#include <stdio.h>
#include <stdlib.h>

// Função para ler uma imagem PGM e armazenar seus dados na estrutura PGMImage
void readPGMImage(PGMImage *pImg, const char *fileName) {
    FILE *fp;
    char ch;

    // Tenta abrir o arquivo PGM para leitura
    if (!(fp = fopen(fileName, "rb"))) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Verifica se o arquivo e do tipo PGM (deve começar com "P")
    if ((ch = getc(fp)) != 'P') {
        puts("O arquivo nao e uma imagem PGM valida.");
        exit(2);
    }

    // Obtem o tipo de PGM (P2 = texto, P5 = binario)
    pImg->tipo = getc(fp) - 48;
    fseek(fp, 1, SEEK_CUR); // Avança para a proxima linha

    // Ignora comentarios (linhas que começam com '#')
    while ((ch = getc(fp)) == '#') {
        while (getc(fp) != '\n');
    }
    fseek(fp, -1, SEEK_CUR); // Retorna um caractere para tras

    // Le as dimensoes da imagem (largura x altura)
    if (fscanf(fp, "%d %d", &pImg->c, &pImg->r) != 2) {
        puts("Erro ao ler as dimensoes da imagem.");
        exit(3);
    }

    // Le o valor maximo dos pixels (geralmente 255)
    if (fscanf(fp, "%d", &pImg->mv) != 1) {
        puts("Erro ao ler o valor maximo da imagem.");
        exit(4);
    }
    fseek(fp, 1, SEEK_CUR); // Avança para a proxima linha

    // Aloca memoria para os pixels da imagem
    pImg->pData = (unsigned char *)malloc(pImg->c * pImg->r * sizeof(unsigned char));
    if (!pImg->pData) {
        perror("Erro ao alocar memoria.");
        exit(5);
    }

    // Le os pixels da imagem com base no tipo PGM
    switch (pImg->tipo) {
        case 2: // PGM em formato texto
            puts("Lendo imagem PGM (formato texto, P2).");
            for (int i = 0; i < (pImg->c * pImg->r); i++) {
                fscanf(fp, "%hhu", &pImg->pData[i]);
            }
            break;
        case 5: // PGM em formato binário
            puts("Lendo imagem PGM (formato binario, P5).");
            fread(pImg->pData, sizeof(unsigned char), pImg->c * pImg->r, fp);
            break;
        default:
            puts("Formato PGM nao suportado.");
            free(pImg->pData);
            exit(6);
    }

    fclose(fp); // Fecha o arquivo apos a leitura
}

// Funçao para salvar uma imagem PGM em arquivo
void writePGMImage(PGMImage *pImg, const char *fileName) {
    FILE *fp;

    // Tenta abrir o arquivo para escrita
    if (!(fp = fopen(fileName, "wb"))) {
        perror("Erro ao criar o arquivo");
        exit(1);
    }

    // Escreve o cabeçalho do PGM (formato P5)
    fprintf(fp, "P5\n");
    fprintf(fp, "%d %d\n", pImg->c, pImg->r);
    fprintf(fp, "%d\n", pImg->mv);

    // Escreve os pixels da imagem no arquivo
    fwrite(pImg->pData, sizeof(unsigned char), pImg->c * pImg->r, fp);

    fclose(fp); // Fecha o arquivo apos a escrita
}

// Funçao para exibir informaçoes sobre a imagem PGM no terminal
void viewPGMImage(PGMImage *pImg) {
    printf("Tipo: P%d\n", pImg->tipo);
    printf("Dimensoes: %d x %d\n", pImg->c, pImg->r);
    printf("Valor Maximo: %d\n", pImg->mv);

    // Exibe os pixels da imagem (somente para debugging, pode ser removido)
    for (int i = 0; i < pImg->r; i++) {
        for (int j = 0; j < pImg->c; j++) {
            printf("%3d ", pImg->pData[i * pImg->c + j]);
        }
        printf("\n");
    }
}

// Funçao para liberar a memoria alocada para a imagem
void freePGMImage(PGMImage *pImg) {
    free(pImg->pData);
    pImg->pData = NULL; // Deixa o ponteiro nulo, evitando comportamento indesejado
}
