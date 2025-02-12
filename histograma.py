import cv2
import matplotlib.pyplot as plt
import numpy as np
import os

def calcular_histograma(caminho_imagem):
    # Ler a imagem PGM
    imagem = cv2.imread(caminho_imagem, cv2.IMREAD_GRAYSCALE)  # Lê a imagem em tons de cinza

    # Verifica se a imagem foi carregada corretamente
    if imagem is None:
        print(f"Erro ao carregar a imagem: {caminho_imagem}")
        return

    # Calcular o histograma
    histograma = cv2.calcHist([imagem], [0], None, [256], [0, 256])

    # Plotar o histograma
    plt.figure()
    plt.title(f"Histograma da Imagem: {os.path.basename(caminho_imagem)}")
    plt.xlabel("Intensidade dos Pixels")
    plt.ylabel("Frequência")
    plt.plot(histograma, color='black')
    plt.xlim([0, 256])  # Define o limite do eixo X (0 a 255)
    plt.grid(True)
    plt.show()

def calcular_histogramas_do_diretorio(caminho_diretorio):
    # Lista todos os arquivos no diretório
    arquivos = os.listdir(caminho_diretorio)

    # Filtra apenas arquivos .pgm
    arquivos_pgm = [f for f in arquivos if f.endswith(".pgm")]

    # Calcula o histograma para cada imagem
    for arquivo in arquivos_pgm:
        caminho_completo = os.path.join(caminho_diretorio, arquivo)
        calcular_histograma(caminho_completo)

# Exemplo de uso
if __name__ == "__main__":
    caminho_diretorio = "Imagens"  # Diretório com as imagens não clusterizadas
    calcular_histogramas_do_diretorio(caminho_diretorio)

def calcular_histogramas_do_diretorio(caminho_diretorio):
    # Lista todos os arquivos no diretório
    arquivos = os.listdir(caminho_diretorio)
    print(f"Arquivos no diretório: {arquivos}")  # Depuração

    # Filtra apenas arquivos .pgm
    arquivos_pgm = [f for f in arquivos if f.endswith(".pgm")]
    print(f"Arquivos PGM: {arquivos_pgm}")  # Depuração

    # Calcula o histograma para cada imagem
    for arquivo in arquivos_pgm:
        caminho_completo = os.path.join(caminho_diretorio, arquivo)
        print(f"Processando: {caminho_completo}")  # Depuração
        calcular_histograma(caminho_completo)