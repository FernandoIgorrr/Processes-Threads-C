#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

void* _multiplicacaoComThreads(void* arg);

double** multiplicacaoComThreads(double** matriz1, double** matriz2, int n1, int m1, int P);

double** multiplicacaoConvencional(double** M1, int n1, int m1, double** M2, int n2, int m2);

double** criarMatrizAleatoria(int n1, int m1);

void salvarMatrizEmArquivo(char* nomeDoArquivo, double** matrix, int n1, int m1);

void salvarMatrizEmArquivoComTempo(char* nomeDoArquivo, double** matrix, int n1, int m1, double tempo);

double** lerMatrizDeArquivo(char* nomeDoArquivo);

char* toString(double** matriz, int n1, int m1);
#endif