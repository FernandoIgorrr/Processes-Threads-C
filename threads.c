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
        printf("O número de elementos por thread é maior do que o número de elementos total da matriz resultado!\n");
        return 1;
    }

    double** M1;
    double** M2;
    double** M3;



    M1 = lerMatrizDeArquivo(nome1);
    M2 = lerMatrizDeArquivo(nome2);
    printf("TESTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");

    M3 = multiplicacaoComThreads(M1,M2,linhas,colunas,P);


    // for(int i = 0;i < linhas;i++){
    //     free(M1[i]);
    // }
    // for(int i = 0;i < linhasM2;i++){
    //     free(M2[i]);
    // }

    // free(M1);
    // free(M2);
    

    // printf("Linhas: %d\n", linhas);
    // printf("Colunas: %d\n", colunas);

    
    printf("Matriz resultado => \n%s\n",toString(M3,linhas,colunas));
    

    salvarMatrizEmArquivo("M3tt",M3,linhas,colunas);

    return 0; 
}