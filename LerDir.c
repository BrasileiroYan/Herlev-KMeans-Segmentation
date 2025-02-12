#include "lerdir.h"
#include "kmeans.h"
#include "pgmimage.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

void processDirectory(const char *directoryPath, int k){
    DIR *dir = opendir(directoryPath);
    if (dir == NULL) {
        perror("Erro ao abrir o diretorio");
        exit(1);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Verifica se é um arquivo regular
            // Formata o caminho completo do arquivo
            char fullPath[1024];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", directoryPath, entry->d_name);
            printf("Processando arquivo: %s\n", fullPath);
            clusterizarImagem(fullPath, k);  // Passa o caminho completo do arquivo
        }
    }

    closedir(dir);
}
