#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"


int main(int argc, char *argv[]){

    if (argc != 5) {
        printf("Digite exatamente 4 números inteiros iguais ou maiores que 2! \n");
        return 1;
    }

    
    // Inicializa uma semente aleatória com o tempo atual
    srand(time(NULL));

    int linhaM1  = atoi(argv[1]);
    int colunaM1 = atoi(argv[2]);
    int linhaM2  = atoi(argv[3]);
    int colunaM2 = atoi(argv[4]);

    double** M1 = criarMatrizAleatoria(linhaM1, colunaM1);
    double** M2 = criarMatrizAleatoria(linhaM2, colunaM2);

    salvarMatrizEmArquivo("M1",M1,linhaM1,colunaM1);
    salvarMatrizEmArquivo("M2",M2,linhaM2,colunaM2);

    for (int i = 0; i < linhaM1; i++) {
        free(M1[i]);
    }for (int i = 0; i < linhaM2; i++) {
        free(M2[i]);
    }

    free(M1);
    free(M2);

    return 0;
}
