# Segmentação de Imagens de Células Cervicais com K-Means 🎯

## 🚀 Descrição

Este projeto foi desenvolvido na linguagem **C**, estruturado de forma modular para facilitar a manutenção e a expansão. O código é organizado em diferentes diretórios, separando arquivos de cabeçalho, implementações e resultados da execução, garantindo maior clareza e eficiência no desenvolvimento.



Este projeto implementa o algoritmo de **K-Means** para segmentação de imagens no formato **PGM**, utilizando o conjunto de dados **Herlev**. Este dataset contém imagens de células cervicais provenientes de exames de Papanicolaou e está disponível para download em: [Herlev Dataset](https://mde-lab.aegean.gr/index.php/downloads/). A segmentação dessas imagens auxilia na análise citológica e identificação de padrões para estudos médicos.

---

## 📂 Estrutura do Projeto  

```
Projeto-Final-C/
├── bin/                  # Diretório contendo o executável final (Main.exe)
├── include/              # Arquivos de cabeçalho (.h), responsáveis pelas definições de funções e estruturas
│   ├── Kmeans.h
│   ├── LerDir.h
│   ├── PgmImage.h
│   ├── ttime.h
├── output/               # Arquivos objeto (.o) gerados durante a compilação
├── scripts/              # Scripts auxiliares para análise e pós-processamento
│   ├── histograma.py
├── src/                  # Implementação principal do código-fonte (.c)
│   ├── Kmeans.c
│   ├── LerDir.c
│   ├── Main.c
│   ├── PgmImage.c
│   ├── ttime.c
├── Makefile              # Arquivo de build para automação da compilação
└── README.md             # Documentação do projeto
```

---

## 🛠️ Como Compilar e Executar

### 🔹 Compilar o projeto
Para compilar o código, execute o seguinte comando no terminal a partir do diretório raiz:

```sh
mingw32-make
```

Este comando irá compilar os arquivos `.c` em objetos `.o`, armazenando-os na pasta `output/`, e gerar o executável `Main.exe` na pasta `bin/`.

---

### 🔹 Executar o programa
Após a compilação, o programa pode ser executado com o seguinte comando, passando como argumento o diretório das imagens e o número desejado de clusters:

```sh
bin/Main.exe "C:\Users\Dell\OneDrive\Área de Trabalho\Projeto-Final-C\images" 4
```

O primeiro argumento especifica a pasta contendo as imagens a serem processadas, enquanto o segundo define o número de clusters para a segmentação.

---

### 🔹 Limpar os arquivos compilados
Para remover os arquivos objeto (`.o`) e o executável gerado, utilize:

```sh
mingw32-make clean
```

ℹ️ **Nota:** Esse comando deve ser executado no **Git Bash**, pois o `rm -rf` não é suportado pelo CMD do Windows.

---

## 📜 Funcionamento do Código
- O programa recebe um diretório contendo imagens no formato **PGM** e um valor `k`, que define a quantidade de clusters.
- Ele **lê e processa as imagens**, aplicando o algoritmo **K-Means** para segmentação baseada em padrões de intensidade.
- Os resultados podem ser analisados por meio do **script `histograma.py`**, que permite uma visualização gráfica da distribuição dos clusters.

---

## 🔧 Dependências
- **GCC (GNU Compiler Collection)** – Requerido para compilar o código C (MinGW no Windows ou GCC no Linux)
- **Make** – Necessário para executar os comandos de compilação automatizada (`mingw32-make` no Windows)
- **Python** – Utilizado para execução de scripts auxiliares, como o `histograma.py`

---

## 📝 Autores
- **Yan Pedro Façanha Brasileiro** ([BrasileiroYan](https://github.com/BrasileiroYan))
- **Ricardo Magalhães Parente Frota** ([Ricardo-Parente](https://github.com/Ricardo-Parente))
- **Eduardo Parente Lima** ([duduxl91](https://github.com/duduxl91))
- **Italo Beserra de Oliveira** ([italobeserra](https://github.com/italobeserra))

