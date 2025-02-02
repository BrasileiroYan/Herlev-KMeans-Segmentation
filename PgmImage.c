#include "pgmimage.h"
#include <stdio.h>
#include <stdlib.h>

void readPGMImage(struct pgm *pImg, char *fileName){
    FILE *fp;
    char ch;

    if(!(fp = fopen(fileName, "r"))){ // verifica se o arquivo pode ser aberto
        perror("Erro!");
        exit(1);
    }
    if((ch = getc(fp)) != 'P'){ // verifica se o arquivo é do tipo PGM
        puts("A imagem fornecida não é do tipo PGM.");
        exit(2);
    }

    pImg->tipo = getc(fp) - 48; // converte o valor ASCII do caractere para inteiro

    fseek(fp, 1, SEEK_CUR); // move o ponteiro para próxima linha

    while((ch = getc(fp)) == '#'){  // varre as linhas de comentários (que iniciam em # até o fim da linha)
        while((ch = getc(fp)) != '\n');
    }
    
    fseek(fp, -1, SEEK_CUR); // volta um caractere atrás para ler corretamente os próximos números

    fscanf(fp, "%d %d", &pImg->c, &pImg->r); // lê, respectivamente, o número de colunas e linhas da matriz da imagem

    if(ferror(fp)){ // verifica se houve algum erro com o arquivo
        perror(NULL);
        exit(3);
    }

    fscanf(fp, "%d", &pImg->mv); // lê o valor máximo dos pixels(255) da imagem

    fseek(fp, 1, SEEK_CUR); // move o ponteiro para próxima linha

    pImg->pData = (unsigned char *) malloc(pImg->c * pImg->r * sizeof(unsigned char)); // aloca memória para o ponteiro de dados
    if(pImg->pData == NULL){
        perror("Erro ao alocar memória.");
        exit(4);
    }

    switch(pImg->tipo){  // lê a imagem com base no seu tipo (textual ou binário)
        case 2:
            puts("Lendo imagem PGM (arquivo em texto).");
            for(int i=0; i<(pImg->c * pImg->r); i++){
                fscanf(fp, "%hhu", pImg->pData + i);
            }
        break;
        case 5:
            puts("Lendo imagem PGM (arquivo em binário).");
            fread(pImg->pData, sizeof(unsigned char), pImg->c * pImg->r, fp);
        break;
        default:
            puts("Formato não implementado.");
            free(pImg->pData);
    }

    fclose(fp); // fecha o fluxo do arquivo
}
void writePGMImage(struct pgm *pImg, char *fileName){
    FILE *fp;
    char ch;

    if(!(fp = fopen(fileName, "wb"))){   // verifica se é possível abrir 
        perror("Erro.");                 // o arquivo binário para escrita 
        exit(1);
    }

    fprintf(fp, "%s\n", "P5");                          // imprime o tipo (P5)
    fprintf(fp, "%d %d\n", pImg->c, pImg->r);           // imprime as dimensões
    fprintf(fp, "%d\n", pImg->mv);                      // imprime o valor máximo

    fwrite(pImg->pData, sizeof(unsigned char), pImg->c * pImg->r, fp); // escreve os pixels da imagem

    fclose(fp); // fecha o fluxo do arquivo   
}
void viewPGMImage(struct pgm *pImg){
    printf("Tipo: %d\n", pImg->tipo);                   // imprime o tipo da imagem
    printf("Dimensões: [%d %d]\n", pImg->c, pImg->r);   // imprime as dimensões da imagem
    printf("Valor Máximo: %d\n", pImg->mv);             // imprime o valor máximo da imagem  

    for(int i=0; i < (pImg->c * pImg->r); i++){         // imprime cada pixel da imagem,
        if(!(i % pImg->c)){                             // formatando corretamente as linhas 
            printf("\n");                               // e colunas 
        }
        printf("%2hhu", *(pImg->pData + i));
    }
    printf("\n");
}
void freePGMImage(struct pgm *pImg){
    free(pImg->pData);  // libera memória alocada anteriormente
    pImg->pData = NULL; // evita comportamento indefinido do ponteiro
}