# Cervical Cell Image Segmentation with K-Means 🎯

## 🚀 Description

This project was developed in the **C** programming language, structured in a modular way to facilitate maintenance and expansion. The code is organized into different directories, separating header files, implementations, and execution results, ensuring greater clarity and efficiency in development.

This project implements the **K-Means** algorithm for **PGM** image segmentation using the **Herlev** dataset. This dataset contains images of cervical cells from Pap smear tests and is available for download at: [Herlev Dataset](https://mde-lab.aegean.gr/index.php/downloads/). The segmentation of these images aids in cytological analysis and pattern identification for medical studies.

---

## 📂 Project Structure  

```
Herlev-KMeans-Segmentation/
├── images/               # Directory containing PGM images for segmentation├── bin/                  # Directory containing the final executable (Main.exe)
├── include/              # Header files (.h) defining functions and structures
│   ├── Kmeans.h
│   ├── LerDir.h
│   ├── PgmImage.h
│   ├── ttime.h
├── output/               # Object files (.o) generated during compilation
├── scripts/              # Auxiliary scripts for analysis and post-processing
│   ├── histograma.py
├── src/                  # Main source code implementation (.c)
│   ├── Kmeans.c
│   ├── LerDir.c
│   ├── Main.c
│   ├── PgmImage.c
│   ├── ttime.c
├── Makefile              # Build file for automated compilation
└── README.md             # Project documentation
```

---

## 🛠️ How to Compile and Run

### 🔹 Compile the project
To compile the code, run the following command in the terminal from the root directory:

```sh
mingw32-make
```

This command compiles the `.c` files into `.o` objects, storing them in the `output/` folder, and generates the `Main.exe` executable in the `bin/` folder.

---

### 🔹 Run the program
After compilation, the program can be executed with the following command, passing the image directory and the desired number of clusters as arguments:

```sh
bin/Main.exe "C:\Users\Dell\OneDrive\Desktop\Herlev-KMeans-Segmentation\images" 4
```

The first argument specifies the folder containing the images to be processed, while the second defines the number of clusters for segmentation.

---

### 🔹 Clean compiled files
To remove object files (`.o`) and the generated executable, use:

```sh
mingw32-make clean
```

ℹ️ **Note:** This command should be executed in **Git Bash**, as `rm -rf` is not supported in Windows CMD.

---

## 📜 Code Functionality
- The program receives a directory containing images in **PGM** format and a value `k`, which defines the number of clusters.
- It **reads and processes the images**, applying the **K-Means** algorithm for segmentation based on intensity patterns.
- The results can be analyzed using the **`histograma.py` script**, which provides a graphical visualization of the cluster distribution.

---

## 🔧 Dependencies
- **GCC (GNU Compiler Collection)** – Required to compile the C code (MinGW for Windows or GCC for Linux)
- **Make** – Necessary to run automated compilation commands (`mingw32-make` on Windows)
- **Python** – Used for running auxiliary scripts, such as `histograma.py`

---

## 📝 Authors
- **Yan Pedro Façanha Brasileiro** ([BrasileiroYan](https://github.com/BrasileiroYan))
- **Ricardo Magalhães Parente Frota** ([Ricardo-Parente](https://github.com/Ricardo-Parente))
- **Eduardo Parente Lima** ([duduxl91](https://github.com/duduxl91))
- **Italo Beserra de Oliveira** ([italobeserra](https://github.com/italobeserra))

](url)
