#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"

int main(int argc, char *argv[]){

    if (argc < 4) {
        printf("Uso: %s string1 string2\n", argv[0]);
        return 1;
    }

    char *nome1 = argv[1];
    char *nome2 = argv[2];
    int P       = atoi(argv[3]);

    int linhas      = lerLinhasColunas(nome1)[0];
    int linhasM2    = lerLinhasColunas(nome2)[0];
    int colunas     = lerLinhasColunas(nome2)[1];

    if(P > linhas*colunas){
        printf("O número de elementos por processo é maior do que o número de elementos total da matriz resultado!\n");
        return 1;
    }

    double** M1;
    double** M2;
    double** M3;

    M1 = lerMatrizDeArquivo(nome1);
    M2 = lerMatrizDeArquivo(nome2);

    M3 = multiplicacaoComProcessos(M1,M2,linhas,colunas,P);

    salvarMatrizEmArquivo("M3p",M3,linhas,colunas);

    return 0;
}