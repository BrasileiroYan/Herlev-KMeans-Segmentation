import cv2
import matplotlib.pyplot as plt
import numpy as np
import os

# Classe para exibir histogramas das imagens em um diretorio
class HistogramaViewer:
    def __init__(self, caminho_diretorio):
        # Inicializa a classe com o caminho do diretorio
        self.caminho_diretorio = caminho_diretorio
        
        # Lista os arquivos .pgm no diretorio fornecido
        self.arquivos = [f for f in os.listdir(caminho_diretorio) if f.endswith(".pgm")]
        
        # Define o indice do arquivo atual
        self.index = 0
        
        # Cria a figura e o eixo para o grafico
        self.fig, self.ax = plt.subplots(figsize=(8, 6))
        
        # Conecta a funçao para tratar eventos de teclas pressionadas
        self.fig.canvas.mpl_connect('key_press_event', self.tecla_pressionada)
        
        # Mostra o histograma da primeira imagem
        self.mostrar_histograma()

    # Funçao para calcular o histograma de uma imagem
    def calcular_histograma(self, caminho_imagem):
        # Carrega a imagem em escala de cinza
        imagem = cv2.imread(caminho_imagem, cv2.IMREAD_GRAYSCALE)
        
        # Verifica se a imagem foi carregada corretamente
        if imagem is None:
            print(f"Erro ao carregar a imagem: {caminho_imagem}")
            return None, None
        
        # Calcula o histograma da imagem
        histograma = cv2.calcHist([imagem], [0], None, [256], [0, 256])
        
        # Retorna o histograma e o nome da imagem
        return histograma, os.path.basename(caminho_imagem)

    # Funçao para exibir o histograma na tela
    def mostrar_histograma(self):
        # Limpa o grafico antes de desenhar o novo histograma
        self.ax.clear()
        
        # Obtem o caminho completo da imagem atual
        caminho_imagem = os.path.join(self.caminho_diretorio, self.arquivos[self.index])
        
        # Calcula o histograma da imagem
        histograma, nome_imagem = self.calcular_histograma(caminho_imagem)

        # Se o histograma foi calculado corretamente, plota o grafico
        if histograma is not None:
            self.ax.plot(histograma, color='blue')
            self.ax.set_title(f"Histograma: {nome_imagem}", fontsize=12)
            self.ax.set_xlabel("Intensidade dos Pixels")
            self.ax.set_ylabel("Frequência")
            self.ax.grid(True)

        # Atualiza o grafico com o novo histograma
        self.fig.canvas.draw()

    # Funçao chamada quando uma tecla e pressionada
    def tecla_pressionada(self, event):
        # Se a tecla pressionada for 'right', avança para a próxima imagem
        if event.key == 'right':
            self.index = (self.index + 1) % len(self.arquivos)
        
        # Se a tecla pressionada for 'left', volta para a imagem anterior
        elif event.key == 'left':
            self.index = (self.index - 1) % len(self.arquivos)
        
        # Se a tecla pressionada for 'escape', fecha a janela
        elif event.key == 'escape':
            plt.close(self.fig)  # Permite fechar a janela com a tecla ESC
        
        # Mostra o histograma da imagem atual
        self.mostrar_histograma()

# Funçao principal para visualizar os histogramas de todas as imagens no diretorio
def visualizar_histogramas(caminho_diretorio):
    # Verifica se o diretorio existe
    if not os.path.exists(caminho_diretorio):
        print("Diretorio nao encontrado.")
        return
    
    # Verifica se o diretorio esta vazio
    if not os.listdir(caminho_diretorio):
        print("Nenhum arquivo encontrado.")
        return

    # Cria uma instância da classe HistogramaViewer para o diretorio
    viewer = HistogramaViewer(caminho_diretorio)
    
    # Exibe a janela com o grafico
    plt.show()

# Exemplo de uso:
if __name__ == "__main__":
    # Caminho do diretorio contendo as imagens .pgm
    caminho_diretorio = "images"
    
    # Chama a funçao para visualizar os histogramas
    visualizar_histogramas(caminho_diretorio)
