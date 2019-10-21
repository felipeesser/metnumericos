#include "opmatriz.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void alocarMatriz(float ***matriz,int n,int m){
    int cont=0;
    float teclado;
    (*matriz)=(float**)malloc(m * sizeof(float*));
    for(int i=0;i<m;i++){
        *((*matriz)+i)=(float*)malloc(n * sizeof(float*));
        for(int j=0;j<n;j++){
            printf("digite  x%d:\n",cont);
            scanf("%f",&teclado);
            *(*((*matriz)+i)+j)=teclado;
            cont++;
        }
    }
}
void imprimematriz(float **matriz,int n,int m){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
                if(j==n-1)
                    printf("%f\n",matriz[i][j]);//formatação em colunas
                else
                    printf("%f ",matriz[i][j]);
        }
    }
}
void liberamatriz(float ***matriz,int m){
    for(int i=0;i<m;i++){
        free(*((*matriz)+i));
    }
    free((*matriz));
}
void troca(float ***matriz,int linha_ant,int linha_nova,int n){//troca uma linha por outra
    float temp;
    for(int i=0;i<n;i++){
        temp=*(*((*matriz)+linha_ant)+i);
        *(*((*matriz)+linha_ant)+i)=*(*((*matriz)+linha_nova)+i);
        *(*((*matriz)+linha_nova)+i)=temp;
    }
}
void escalonar(float ***matriz,int n,int m,float ***matriz2,int imprime){//matriz2->resultado do sistema/matriz->coeficientes do sistema
    float pivot,matrizl,operador1;//operador1->variável feita para evitar ambiguidade de multiplicação
    int linha,cont=0;
    for(int i=0;i<m-1;i++){//último pivot está na linha anterior à última linha
        //parte para achar o pivot de maior valor
        int trocou=0;
        pivot=*(*((*matriz)+i)+i);
        for(int j=i+1;j<m;j++){
                if(abs(*(*((*matriz)+j)+i))>abs(pivot)){
                            trocou=1;
                            linha=j;
                            pivot=*(*((*matriz)+j)+i);
                    }
        }
        if(trocou){
        troca(matriz,i,linha,n);
        troca(matriz2,i,linha,1);
        }
        //escalonamento de fato
        for(int a=i+1;a<m;a++){
            for(int b=i;b<n;b++){
                if(*(*((*matriz)+a)+i)!=0){
                    if(b==i){//posições da diagonal principal
                        operador1=*(*((*matriz)+i)+b);//pivot
                        matrizl=*(*((*matriz)+a)+b)/operador1;//operador que formará a matrizL
                        operador1=*(*((*matriz2)+i)+0);//operações devem repercutir na matriz resposta do sistema
                        *(*((*matriz2)+a)+0)=*(*((*matriz2)+a)+0)-((matrizl) * (operador1));
                        *(*((*matriz)+a)+b)=matrizl;//posições de coeficientes zeraos recebem operadores que formarão matrizL
                    }
                    else{
                        operador1=*(*((*matriz)+i)+b);
                        *(*((*matriz)+a)+b)=*(*((*matriz)+a)+b)-(matrizl * operador1);
                    }
                }
            }
            if(imprime){
                cont++;
                printf("%d procedimento feito no sistema:\n",cont);//iterações realizadas
                imprimematriz((*matriz),n,m);
                printf("%d procedimento feito no sistema resposta:\n",cont);
                imprimematriz((*matriz2),1,m);
            }
        }
    }
//utiliza a matriz2 para guardar as váriaveis do sistema
    float soma=0;
    for (int k=m-1;k>=0;k--){
        soma=*(*((*matriz2)+k)+0);
        for(int l=n-1;l>=k;l--){
            if(k==l){
                operador1=*(*((*matriz)+k)+l);
                *(*((*matriz2)+k)+0)=soma/operador1;
            }
            else{
                operador1=*(*((*matriz2)+l)+0);
                soma=soma-(*(*((*matriz)+k)+l)*operador1);
            }
        }
    }
}//fim do escalonar
void alocarMatrizLU(float ***matriz,int n,int m,float ***matrizL,float ***matrizU){
    (*matrizL)=(float**)malloc(m * sizeof(float*));
    (*matrizU)=(float**)malloc(m * sizeof(float*));
    for(int i=0;i<m;i++){
        *((*matrizL)+i)=(float*)malloc(n * sizeof(float*));
        *((*matrizU)+i)=(float*)malloc(n * sizeof(float*));
        for(int j=0;j<n;j++){
                if(i==j)*(*((*matrizL)+i)+j)=1;
                else if(j>i)*(*((*matrizL)+i)+j)=0;
                else *(*((*matrizL)+i)+j)=*(*((*matriz)+i)+j);
                if(i>j)*(*((*matrizU)+i)+j)=0;
                else*(*((*matrizU)+i)+j)=*(*((*matriz)+i)+j);;
        }
      }
}
void criacan(float ***matriz,int m){
    int n=1;
    (*matriz)=(float**)malloc(m * sizeof(float*));
    for(int i=0;i<m;i++){
        *((*matriz)+i)=(float*)malloc(n * sizeof(float*));
        for(int j=0;j<n;j++){
                *(*((*matriz)+i)+j)=0;
        }
      }
}
void modifican(float ***matriz,int m,int e){
    int n=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
                if (i==e)*(*((*matriz)+i)+j)=1;
                else*(*((*matriz)+i)+j)=0;
        }
    }
}
void criainv(float ***matriz,int n,int m){
    (*matriz)=(float**)malloc(m * sizeof(float*));
    for(int i=0;i<m;i++){
        *((*matriz)+i)=(float*)malloc(n * sizeof(float*));
        for(int j=0;j<n;j++){
            *(*((*matriz)+i)+j)=0;
        }
    }
}
void modifinv(float ***matriz,int e,int m,float ***matrizresp){//insere coluna na matriz inversa
    for(int i=0;i<m;i++){
            *(*((*matriz)+i)+e)=*(*((*matrizresp)+i)+0);
    }
}
float** inversa(float ***matriz,float ***matriz2,int n,int m,float ***matrizL,float ***matrizU){
    printf("preenchimento do sistema:\n");
    alocarMatriz(matriz,n,m);//preenche sistema
    printf("preenchimento do sistema resposta:\n");
    alocarMatriz(matriz2,1,m);//preenche resposta sistema
    escalonar(matriz, n,m,matriz2,1);
    alocarMatrizLU(matriz,n,m,matrizL,matrizU);
    printf("MatrizL:\n");
    imprimematriz((*matrizL),n,m);
    printf("MatrizU:\n");
    imprimematriz((*matrizU),n,m);
    float **matrizcan=NULL;
    float **matrizinv=NULL;
    criainv(&matrizinv,n,m);
    criacan(&matrizcan,m);
    for(int i=0;i<m;i++){
        modifican(&matrizcan,m,i);
        escalonar(matrizL,n,m,&matrizcan,0);
        escalonar(matrizU,n,m,&matrizcan,0);
        modifinv(&matrizinv,i,m,&matrizcan);
    }
    liberamatriz(&matrizcan,m);//libera canonica
return matrizinv;
}
