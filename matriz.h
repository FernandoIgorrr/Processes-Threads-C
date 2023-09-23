#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

void _multiplicacaoComProcessos(double** M1, double** M2, double** resultado, int linhaParaIniciar, int colunaParaIniciar, int linhaParaFinalizar, int colunaParaFinalizar, int elementosPorProcesso, int colunas);

double** multiplicacaoComProcessos(double** M1, double** M2, int linhas, int colunas, int elementosPorProcesso);

void* _multiplicacaoComThreads(void* arg);

double** multiplicacaoComThreads(double** M1, double** M2, int linhas, int colunas, int elementosPorThread);

double** multiplicacaoConvencional(double** colunas, int linhasM1, int colunasM1, double** M2, int linhasM2, int colunasM2);

double** criarMatrizAleatoria(int linhas, int colunas);

void salvarMatrizEmArquivo(char* nomeDoArquivo, double** matriz, int linhas, int colunas);

void salvarMatrizEmArquivoComTempo(char* nomeDoArquivo, double** matriz, int linhas, int colunas, double tempo);

void salvarTemposEmArquivo(char* diretorio, char* nomeDoArquivo, double* tempo, int num_tempos, int linhas, int colunas);

void salvarTempoEmArquivo(char* diretorio, char* nomeDoArquivo, double tempo, int linhas, int colunas);

double** lerMatrizDeArquivo(char* nomeDoArquivo);

int* lerLinhasColunas(char* nomeDoArquivo);

char* toString(double** matriz, int linhas, int colunas);
#endif