#include <stdio.h>
#include <stdlib.h>
#include "opmatriz.h"
int main(){
    int n,m;//m sistemas, n incognitas
    float **matrizini=NULL;
    float **matrizresp=NULL;
    float **matrizL=NULL;
    float **matrizU=NULL;
    float **matrizinv=NULL;
    printf("digite numero de linhas do sistema\n");
    scanf("%d",&m);
    printf("digite numero de incognitas\n");
    scanf("%d",&n);
    matrizinv=inversa(&matrizini,&matrizresp,n,m,&matrizL,&matrizU);
    printf("matriz inversa:\n");
    imprimematriz(matrizinv,n,m);
    liberamatriz(&matrizini,m);
    liberamatriz(&matrizresp,m);
    liberamatriz(&matrizL,m);
    liberamatriz(&matrizU,m);
    return 0;
}
