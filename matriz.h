#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

void* _multiplicacaoComProcessos(void* arg);

double** multiplicacaoComProcessos(double** matriz1, double** matriz2, int linhas, int colunas, int elementosPorProcesso);

void* _multiplicacaoComThreads(void* arg);

double** multiplicacaoComThreads(double** matriz1, double** matriz2, int linhas, int colunas, int elementosPorThread);

double** multiplicacaoConvencional(double** colunas, int linhasM1, int colunasM1, double** M2, int linhasM2, int colunasM2);

double** criarMatrizAleatoria(int linhas, int colunas);

void salvarMatrizEmArquivo(char* nomeDoArquivo, double** matrix, int linhas, int colunas);

void salvarMatrizEmArquivoComTempo(char* nomeDoArquivo, double** matrix, int linhas, int colunas, double tempo);

double** lerMatrizDeArquivo(char* nomeDoArquivo);

int* lerLinhasColunas(char* nomeDoArquivo);

char* toString(double** matriz, int linhas, int colunas);
#endif