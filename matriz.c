#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double** multiplcaConvencional(double** M1, int n1, int m1, double** M2, int n2, int m2){

	// Verifica se as matrizes podem ser multiplicadas
	if (m1 != n2) {
        printf("Erro: As matrizes não podem ser multiplicadas.\n");
        return NULL;
    }


	// Aloque memória para a matriz resultado
	double** resultado = (double**)malloc(n1 * sizeof(double*));
    for (int i = 0; i < n1; i++) {
        resultado[i] = (double*)malloc(m2 * sizeof(double));
    }

	// Realiza a multiplicação das matrizes
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            resultado[i][j] = 0.0;
            for (int k = 0; k < m1; k++) {
                resultado[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

	return resultado;
}

double** criarMatrizAleatoria(int n1, int m1){
	if (n1 < 2 || m1 < 2) {
        printf("Erro: A matrize tem que ser pelo menos 2x2.\n");
        return NULL;
    }

	// Inicialize a semente aleatória com o tempo atual
    srand(time(NULL));

	// Aloca memória e cria a matriz
	double** matriz = (double**)malloc(n1 * sizeof(double*));
    for (int i = 0; i < n1; i++) {
        matriz[i] = (double*)malloc(m1 * sizeof(double));
    }

	// Preenche a matriz com valores aleatórios
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            matriz[i][j] = ((double)rand() / RAND_MAX) * 10.0; // Gera números aleatórios entre 0 e 10
        }
    }

	return matriz;
}

void salvarMatrizEmArquivo(char* nomeDoArquivo, double** matriz, int n1, int m1){
	//Abre o arquivo para escrita
    FILE* arquivo = fopen(nomeDoArquivo, "w");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

	// Escreve as dimensões da matriz no arquivo
    fprintf(arquivo, "%d\t%d\n", n1, m1);

	// Escreve os elementos da matriz no arquivo
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            fprintf(arquivo, "%lf\t", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
	fclose(arquivo);
}