import cv2
import matplotlib.pyplot as plt
import numpy as np
import os

class HistogramaViewer:
    def __init__(self, caminho_diretorio):
        self.caminho_diretorio = caminho_diretorio
        self.arquivos = [f for f in os.listdir(caminho_diretorio) if f.endswith(".pgm")]
        self.index = 0
        self.fig, self.ax = plt.subplots(figsize=(8, 6))
        self.fig.canvas.mpl_connect('key_press_event', self.tecla_pressionada)
        self.mostrar_histograma()

    def calcular_histograma(self, caminho_imagem):
        imagem = cv2.imread(caminho_imagem, cv2.IMREAD_GRAYSCALE)
        if imagem is None:
            print(f"Erro ao carregar a imagem: {caminho_imagem}")
            return None, None
        histograma = cv2.calcHist([imagem], [0], None, [256], [0, 256])
        return histograma, os.path.basename(caminho_imagem)

    def mostrar_histograma(self):
        self.ax.clear()
        caminho_imagem = os.path.join(self.caminho_diretorio, self.arquivos[self.index])
        histograma, nome_imagem = self.calcular_histograma(caminho_imagem)

        if histograma is not None:
            self.ax.plot(histograma, color='black')
            self.ax.set_title(f"Histograma: {nome_imagem}", fontsize=12)
            self.ax.set_xlabel("Intensidade dos Pixels")
            self.ax.set_ylabel("Frequência")
            self.ax.grid(True)

        self.fig.canvas.draw()

    def tecla_pressionada(self, event):
        if event.key == 'right':
            self.index = (self.index + 1) % len(self.arquivos)
        elif event.key == 'left':
            self.index = (self.index - 1) % len(self.arquivos)
        elif event.key == 'escape':
            plt.close(self.fig)  # Permite fechar a janela com a tecla ESC
        self.mostrar_histograma()

def visualizar_histogramas(caminho_diretorio):
    if not os.path.exists(caminho_diretorio):
        print("Diretório não encontrado.")
        return
    if not os.listdir(caminho_diretorio):
        print("Nenhum arquivo encontrado.")
        return

    viewer = HistogramaViewer(caminho_diretorio)
    plt.show()

# Exemplo de uso:
if __name__ == "__main__":
    caminho_diretorio = "Imagens"
    visualizar_histogramas(caminho_diretorio)
