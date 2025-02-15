#ifndef LERDIR_H
#define LERDIR_H

// Declara as funcoes que serao utilizadas em LerDir.c
void processImage(const char *fileName, int k);  
void processDirectory(const char *directoryPath, int k);
void clusterizarImagem(const char *imagePath, int k);

#endif // LERDIR_H
