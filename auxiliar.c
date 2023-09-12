#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"


int main(){

    // Inicializa uma semente aleatória com o tempo atual
    srand(time(NULL));

    int n1, m1, n2, m2;
	
    setbuf(stdin, NULL);
    printf("Digite 4 números inteiros representando as linhas e colunas de duas matrizes \n n1 m1 n2 m2: ");
    scanf("%d %d %d %d",&n1,&m1,&n2,&m2);

    double** M1 = criarMatrizAleatoria(n1, m1);
    double** M2 = criarMatrizAleatoria(n2, m2);

    salvarMatrizEmArquivo("M1",M1,n1,m1);
    salvarMatrizEmArquivo("M2",M2,n2,m2);

    for (int i = 0; i < n1; i++) {
        free(M1[i]);
    }for (int i = 0; i < n2; i++) {
        free(M2[i]);
    }

    free(M1);
    free(M2);

    return 0;
}
