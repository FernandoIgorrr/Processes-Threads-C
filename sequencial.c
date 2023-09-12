#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"

int main(){

    char nome1[10],nome2[10]; 
    double** M1;
    double** M2;
    double** M3;

    setbuf(stdin, NULL);
    printf("Digite os nomes dos dois arquivos separados por um espaço \n Arquivo1: Arquivo2: ");
    scanf("%s %s", &nome1, &nome2);

    M1 = lerMatrizDeArquivo(nome1);
    M2 = lerMatrizDeArquivo(nome2);


    clock_t inicio, fim;
    double tempoDecorrido;

    // Marca o tempo inicial
    inicio = clock();

    // Chama a função convencional de multiplicação de matrizes
    M3 = multiplicacaoConvencional(M1,5,3,M2,3,5);
    
    // Marca o tempo final
    fim = clock();

    tempoDecorrido = (double)(fim - inicio) / CLOCKS_PER_SEC*1000;
    printf("Multiplicação de matrizes convencional \n");

    printf("=================================================\n");

    printf("Tempo de execução: %.4lf milissegundos [ms]\n",tempoDecorrido);

    printf("=================================================\n");

    salvarMatrizEmArquivoComTempo("M3",M3,5,5,tempoDecorrido);
            // TESTES PARA VER AS MATRIZES //

    // if (M1 != NULL) {
    //     // Imprime a representação de string da matriz
    //     printf("Matriz M1:\n%s\n",toString(M1, 5, 3));
    // } else {
    //     printf("Erro na alocação de memória.\n");
    // }
    
    // if (M2 != NULL) {
    //     // Imprime a representação de string da matriz
    //     printf("Matriz M2:\n%s\n",toString(M2, 3, 5));
    // } else {
    //     printf("Erro na alocação de memória.\n");
    // }
    // printf("--------------------------------------------------------------------\n");
    // if (M3 != NULL) {
    //     // Imprime a representação de string da matriz
    //     printf("Matriz Resultado da multiplicação entre a M1 e M2 :\n%s\n",toString(M3, 5, 5));
    // } else {
    //     printf("Erro na alocação de memória.\n");
    // }



    return 0;
}
