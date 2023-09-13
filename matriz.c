#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include "matriz.h"

#define MAX_THREADS 1000

typedef struct {
    double** matriz1;
    double** matriz2;
    double** resultado;
    //int linhas;
    int colunas;
    //int id_thread;
    int elementosPorThread;
   // int num_threads;
    int linha_inicio;
    int coluna_inicio;
    int linha_fim;
    int coluna_fim;
    double tempo;
} ProcessesArgs;

typedef struct {
    double** matriz1;
    double** matriz2;
    double** resultado;
    //int linhas;
    int colunas;
    //int id_thread;
    int elementosPorThread;
   // int num_threads;
    int linha_inicio;
    int coluna_inicio;
    int linha_fim;
    int coluna_fim;
    double tempo;
} ThreadArgs;


void* _multiplicacaoComProcessos(void* arg){
    
}

double** multiplicacaoComProcessos(double** matriz1, double** matriz2, int linhas, int colunas, int elementosPorProcesso){

    double** resultado = (double**)malloc(linhas * sizeof(double*));
    for (int i = 0; i < linhas; i++) {
        resultado[i] = (double*)malloc(colunas * sizeof(double));
    }

    int numProcessos = ceil((linhas*colunas) / elementosPorProcesso);

    if(((linhas*colunas) % elementosPorProcesso) != 0){
        numProcessos++;
    }

    int inicio = 0;

    for (int i = 0; i < numProcessos; i++) {

        pid_t pid = fork();

        if (pid == 0) {
            multiplicarParteMatriz(matrizA, matrizB, resultado, inicio, fim);
            exit(0);
        } else if (pid < 0) {
            perror("Erro na criação do processo filho");
            exit(1);
        }

        inicio = fim;
    }
}

// Função que executa cada thread
void* _multiplicacaoComThreads(void* arg) {
    
    ThreadArgs* args = (ThreadArgs*)arg;
    
    clock_t inicioTempo = clock();
    //printf("Thread: [ %d ] ([ %d | %d ]) => \n",args->id_thread,args->linha_inicio,args->coluna_inicio);

    for (int count = 0,i = args->linha_inicio; i < args->linha_fim + 1; i++) {  
       for(int j = ((i > args->linha_inicio) ? 0 : args->coluna_inicio); (j < args->coluna_fim + 1) || (count < args->elementosPorThread)  ; j++,count++){
            if(j == args->colunas){
                break;
            }
            args->resultado[i][j] = 0;
            //printf("\tresultado[%d][%d]\n",i,j);
            for(int k = 0; k < args->colunas;k++){
                args->resultado[i][j] += args->matriz1[i][k] * args->matriz2[k][j];
            }
        }
    }

    clock_t fimTempo = clock();
    args->tempo = (double)(fimTempo - inicioTempo) / CLOCKS_PER_SEC*1000;
    // printf("THREAD:  %d  :====>\n",args->id_thread);
    // printf("%s\n",toString(args->resultado,args->linhas,args->colunas));
    // printf("===================================================\n");
    // for(int i = 0;i<args->linhas;i++){
    //     free(args->resultado[i]);

    // }
    // free(args->resultado);
    pthread_exit(NULL);
}

// Função para multiplicar matrizes usando threads
double** multiplicacaoComThreads(double** matriz1, double** matriz2, int linhas, int colunas, int elementosPorThread) {
    // printf("LINHAS: %d\n",linhas);
    // printf("COLUNAS: %d\n",colunas);
    // Aloqca memória para a matriz de resultado
    double** resultado = (double**)malloc(linhas * sizeof(double*));
    for (int i = 0; i < linhas; i++) {
        resultado[i] = (double*)malloc(colunas * sizeof(double));
    }

    // Cria  as threads
    pthread_t threads[MAX_THREADS];
    ThreadArgs thread_args[MAX_THREADS];

    int num_threads = ceil((linhas*colunas) / elementosPorThread);

    if(((linhas*colunas) % elementosPorThread) != 0){
        num_threads++;
    }

    //printf("Numeros de Threads:  %d\n\n\n",num_threads);


    for (int i = 0; i < num_threads; i++) {

        int elementoParaIniciar = (i*elementosPorThread) + 1;
        int linhaParaIniciar    = (elementoParaIniciar - 1) / colunas;
        int colunaParaIniciar   = (elementoParaIniciar - 1) % colunas;


        int elementoParaFinalizar = ((((i+1)*elementosPorThread) + 1) > linhas*colunas) ? (linhas*colunas) : (((i+1)*elementosPorThread));
        int linhaParaFinalizar    = ((elementoParaFinalizar - 1) / colunas);
        int colunaParaFinalizar   = (elementoParaFinalizar - 1) % colunas;

        //  printf("Elemento para começar:      [ %d | %d ]\n",linhaParaIniciar,colunaParaIniciar);
        //  printf("Elemento para finalizar:    [ %d | %d ]\n",linhaParaFinalizar,colunaParaFinalizar);
        //  printf("====================================\n");

        thread_args[i].matriz1              = matriz1;
        thread_args[i].matriz2              = matriz2;
        thread_args[i].resultado            = resultado;
        //thread_args[i].linhas               = linhas;
        thread_args[i].colunas              = colunas;
        //thread_args[i].id_thread            = i;
        thread_args[i].elementosPorThread   = elementosPorThread;
        //thread_args[i].num_threads          = num_threads;
        thread_args[i].linha_inicio         = linhaParaIniciar;
        thread_args[i].coluna_inicio        = colunaParaIniciar;
        thread_args[i].linha_fim            = linhaParaFinalizar;
        thread_args[i].coluna_fim           = colunaParaFinalizar;


        pthread_create(&threads[i], NULL, _multiplicacaoComThreads, &thread_args[i]);
        

        //_multiplicacaoComThreads(&thread_args[i]);
    }

    // Aguarde as threads terminarem
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        char str[100] ;
        char texto[100] ;
        sprintf(str, "%d", i);
        snprintf(texto, sizeof(texto), "thread_%s", str);
        salvarMatrizEmArquivoComTempo(texto,thread_args[i].resultado,linhas,colunas,thread_args[i].tempo);
        //printf("Tempo da thread %d: %lf segundos\n", i, thread_args[i].tempo);
    }

    //printf("%s kkkk ",toString(resultado,linhas,colunas));
    return resultado;
}

double** multiplicacaoConvencional(double** M1, int linhasM1, int colunasM1, double** M2, int linhasM2, int colunasM2){

	// Verifica se as matrizes podem ser multiplicadas
	if (colunasM1 != linhasM2) {
        printf("Erro: As matrizes não podem ser multiplicadas.\n");
        return NULL;
    }


	// Aloque memória para a matriz resultado
	double** resultado = (double**)malloc(linhasM1 * sizeof(double*));
    for (int i = 0; i < linhasM1; i++) {
        resultado[i] = (double*)malloc(colunasM2 * sizeof(double));
    }


	// Realiza a multiplicação das matrizes
    for (int i = 0; i < linhasM1; i++) {
        for (int j = 0; j < colunasM2; j++) {
            resultado[i][j] = 0.0;
            for (int k = 0; k < colunasM1; k++) {
                resultado[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    // for (int i = 0; i < linhasM1; i++) {
    //     for (int j = 0; j < colunasM2; j++) {
    //         printf("[%.2lf]\t",resultado[i][j]);
    //     }
    //     printf("\n");
    // }

	return resultado;
}

double** criarMatrizAleatoria(int linhas, int colunas){
	if (linhas < 2 || colunas < 2) {
        printf("Erro: A matrize tem que ser pelo menos 2x2.\n");
        return NULL;
    }

	// Aloca memória e cria a matriz
	double** matriz = (double**)malloc(linhas * sizeof(double*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (double*)malloc(colunas * sizeof(double));
    }
	// Preenche a matriz com valores aleatórios
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = ((double)rand() / RAND_MAX) * 10.0; // Gera números aleatórios entre 0 e 10
        }
    }
	return matriz;
}

void salvarMatrizEmArquivo(char* nomeDoArquivo, double** matriz, int linhas, int colunas){

	//Abre o arquivo para escrita
    FILE* arquivo = fopen(nomeDoArquivo, "w");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

	// Escreve as dimensões da matriz no arquivo
    fprintf(arquivo, "%d\t%d\n", linhas, colunas);

	// Escreve os elementos da matriz no arquivo
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(arquivo, "%lf\t", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
	fclose(arquivo);
}

void salvarMatrizEmArquivoComTempo(char* nomeDoArquivo, double** matriz, int linhas, int colunas, double tempo){

	//Abre o arquivo para escrita
    FILE* arquivo = fopen(nomeDoArquivo, "w");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve o tempo que durou a multiplicação
    fprintf(arquivo, "%lf\n", tempo);

	// Escreve as dimensões da matriz no arquivo
    fprintf(arquivo, "%d\t%d\n", linhas, colunas);

	// Escreve os elementos da matriz no arquivo
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(arquivo, "%lf\t", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }

	fclose(arquivo);
}

double** lerMatrizDeArquivo(char* nomeDoArquivo){
    
    int linhas, colunas;
    FILE *arquivo = fopen(nomeDoArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    fscanf(arquivo, "%d %d", &linhas, &colunas);

    double **matriz = (double **)malloc(linhas * sizeof(double *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (double *)malloc(colunas * sizeof(double));
    }

     for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (fscanf(arquivo, "%lf", &matriz[i][j]) != 1) {
                printf("Erro ao ler elementos da matriz.\n");
                return NULL;
            }
        }
    }
    fclose(arquivo);

    return matriz;
}

int* lerLinhasColunas(char* nomeDoArquivo){
   
    int linhas, colunas;
    FILE *arquivo = fopen(nomeDoArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    fscanf(arquivo, "%d %d", &linhas, &colunas);

    int* linhas_colunas = (int*)malloc(2 * sizeof(int));
    linhas_colunas[0]   = linhas;
    linhas_colunas[1]   = colunas;

    return linhas_colunas;
}
char* toString(double** matriz, int linhas, int colunas){

    int     posicao         = 0;
    int     tamanhoMaximo   = linhas*colunas*15;
    char*   str             = (char*)malloc(tamanhoMaximo * sizeof(char));;

    // Falha na alocação de memória
    if (str == NULL) {
        return NULL; 
        printf("É NULL\n\n");
    }


    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
           posicao += snprintf(str + posicao, tamanhoMaximo - posicao, "[%lf]\t", matriz[i][j]);
        }
         // AdicionA uma quebra de linha no final de cada linha da matriz
        posicao += snprintf(str + posicao, tamanhoMaximo - posicao, "\n");
    }

    return str;
}