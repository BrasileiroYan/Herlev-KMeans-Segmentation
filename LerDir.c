#include <dirent.h>
#include <stdio.h>
 
int main(void)
{
    // Inicio da medição do tempo
    DIR *d;
    struct dirent *dir;
    d = opendir("./images");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            


            printf("%s\n", dir->d_name);


						// Leitura da Imagem -PGM


						
						
						// Saída.


             
        }
        closedir(d);
    }
    // Fim da medição do tempo           
    return(0);
}
