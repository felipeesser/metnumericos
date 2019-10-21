#ifndef OPMATRIZ_H_INCLUDED
#define OPMATRIZ_H_INCLUDED
void alocarMatriz(float ***matriz,int n,int m);//aloca e preenche uma matriz mxn(input pelo teclado)
void imprimematriz(float **matriz,int n,int m);//imprime na tela matriz mxn
void liberamatriz(float ***matriz,int m);//desaloca espaço da memória de uma matriz
void troca(float ***matriz,int linha_ant,int linha_nova,int n);//troca todos os elementos de uma linha por outra
void escalonar(float ***matriz,int n,int m,float ***matriz2,int imprime);//escalona a matriz, resolve o sistema,colocando o resultado na matriz2 e ipreme processos realizados
void alocarMatrizLU(float ***matriz,int n,int m,float ***matrizL,float ***matrizU);//aloca e preenche matrizesLU
void criacan(float ***matriz,int m);//aloca matriz canônica e preenche com 0
void modifican(float ***matriz,int m,int e);//insere 1 na matriz canônica conforme a posição e
void criainv(float ***matriz,int n,int m);//aloca e preenche a matriz inversa com 0
void modifinv(float ***matriz,int e,int m,float ***matrizresp);//insere coluna na matriz inversa
float** inversa(float ***matriz,float ***matriz2,int n,int m,float ***matrizL,float ***matrizU);//imprime matrizLU e escalona as duas para gerar a inversa
#endif // OPMATRIZ_H_INCLUDED
