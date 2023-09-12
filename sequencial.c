#include <stdio.h>
#include <stdlib.h>
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

    M3 = multiplicacaoConvencional(M1,12,7,M2,7,12);

            // TESTES PARA VER AS MATRIZES //

    if (M1 != NULL) {
        // Imprime a representação de string da matriz
        printf("Matriz M1:\n%s\n",toString(M1, 12, 7));
    } else {
        printf("Erro na alocação de memória.\n");
    }
    
    if (M2 != NULL) {
        // Imprime a representação de string da matriz
        printf("Matriz M2:\n%s\n",toString(M2, 7, 12));
    } else {
        printf("Erro na alocação de memória.\n");
    }
    printf("--------------------------------------------------------------------\n");
    if (M3 != NULL) {
        // Imprime a representação de string da matriz
        printf("Matriz Resultado da multiplicação entre a M1 e M2 :\n%s\n",toString(M3, 12, 12));
    } else {
        printf("Erro na alocação de memória.\n");
    }

    return 0;
}
