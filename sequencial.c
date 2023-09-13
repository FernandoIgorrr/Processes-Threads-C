#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"

int main(int argc, char *argv[]){

     if (argc < 3) {
        printf("Uso: %s string1 string2\n", argv[0]);
        return 1; 
    }

    char* nome1 = argv[1];
    char* nome2 = argv[2];

    double** M1;
    double** M2;
    double** M3;

    M1 = lerMatrizDeArquivo(nome1);
    M2 = lerMatrizDeArquivo(nome2);

    clock_t inicio, fim;
    double tempoDecorrido;

    int linhasM1 = lerLinhasColunas(nome1)[0];
    int colunasM1 = lerLinhasColunas(nome1)[1];
   
    int linhasM2 = lerLinhasColunas(nome2)[0];
    int colunasM2 = lerLinhasColunas(nome2)[1];

    // free(nome1);
    // free(nome2);

    // Marca o tempo inicial
    inicio = clock();
    // Chama a função convencional de multiplicação de matrizes
    M3 = multiplicacaoConvencional(M1,linhasM1,colunasM1,M2,linhasM2,colunasM2);
    // Marca o tempo final
    fim = clock();

    tempoDecorrido = (double)(fim - inicio) / CLOCKS_PER_SEC*1000;
    printf("Multiplicação de matrizes convencional \n");

    printf("=================================================\n");

    printf("Tempo de execução: %.4lf milissegundos [ms]\n",tempoDecorrido);

    printf("=================================================\n");

    salvarMatrizEmArquivoComTempo("M3s",M3,linhasM1,colunasM2,tempoDecorrido);

            // TESTES PARA VER AS MATRIZES //

    // if (M1 != NULL) {
    //     // Imprime a representação de string da matriz
    //     printf("Matriz M1:\n%s\n",toString(M1, linhasM1, colunasM2));
    // } else {
    //     printf("Erro na alocação de memória.\n");
    // }

   
    
    // if (M2 != NULL) {
    //     // Imprime a representação de string da matriz
    //     printf("Matriz M2:\n%s\n",toString(M2, linhasM2, colunasM2));
    // } else {
    //     printf("Erro na alocação de memória.\n");
    // }

    
    // printf("--------------------------------------------------------------------\n");

    // if (M3 != NULL) {
    //     // Imprime a representação de string da matriz
    //     printf("Matriz Resultado da multiplicação entre a M1 e M2 :\n%s\n",toString(M3, linhasM1, colunasM2));
    // } else {
    //     printf("Erro na alocação de memória.\n");
    // }

    for (int i = 0; i < linhasM1; i++) {
        free(M1[i]);
    }
    for (int i = 0; i < linhasM2; i++) {
        free(M2[i]);
     }

    for (int i = 0; i < linhasM1; i++) {
        free(M3[i]);
    }

    free(M1);
    free(M2);
    free(M3);


    return 0;
}
