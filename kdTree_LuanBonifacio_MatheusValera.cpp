#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "meuconio.h"
#include <math.h>
#include <time.h>
#define k 2
#define TLN 15

struct kdtree
{
    int ponto[k];
    struct kdtree *esq, *dir;  
};typedef struct kdtree Tree;

void geraPontos(int pontosN[TLN][k], int TL)
{
    int i,j;
    for(i=0; i<TL; i++)
        for(j=0;j<k;j++)
            pontosN[i][j] = rand() % 100;
}

void ordenaMat(int pontosN[TLN][k], int num)
{
    int i,aux[2];
    while(i<TLN)
    {
        for(i=0; i<TLN-1; i++)
            if(pontosN[i][num] > pontosN[i+1][num])
            {
                aux[0] = pontosN[i][0];
                aux[1] = pontosN[i][1];
                pontosN[i][0] =pontosN[i+1][0];
                pontosN[i][1] = pontosN[i+1][1];
                pontosN[i+1][0] = aux[0];
                pontosN[i+1][1] = aux[1];
            }
        i++;
    }
}

Tree *criaNo(int *pontos)
 {
    Tree *NC = (Tree*)malloc(sizeof(Tree));
    NC->ponto[0] = pontos[0];
    NC->ponto[1] = pontos[1];
    NC->esq = NC->dir = NULL;
    return NC;
 }

Tree *insereKDTree(int pontosN[TLN][k], Tree **raiz, int ini, int fim, int n)
{
    int numero, meio;
    if(ini <= fim)
    {
        numero = n%k;
        ordenaMat(pontosN,numero);
        meio = (ini+fim)/2;
        *raiz = criaNo(pontosN[meio]);
        insereKDTree(pontosN, &(*raiz)->esq , ini, meio-1, n+1);
        insereKDTree(pontosN, &(*raiz)->esq , meio+1, fim, n+1); 
    }
}

void busca(Tree *raiz, int coo[k], int raio)
{
	if(raiz != NULL)
	{
		if(sqrt(pow(coo[0] - raiz->ponto[0],2) + pow(coo[1] - raiz->ponto[1],2)) < raio)
			printf("(%d,%d)\t",raiz->ponto[0],raiz->ponto[1]);
		busca(raiz->esq, coo, raio);
		busca(raiz->dir, coo, raio);
	}	
}

int main(void)
{
    int pontosN[TLN][k],p,raio,i=0;
    Tree *raiz = NULL;
    
    geraPontos(pontosN,TLN);
    insereKDTree(pontosN,&raiz,0,TLN,0);
    textcolor(2);
    srand(time(NULL));
    gotoxy(5,1);printf("Luan: 26.19.1171-6");
    gotoxy(53,1);printf("** Kd-Tree **");
    gotoxy(95,1);printf("Matheus: 26.19.1235-6");
    while(i < 5)
    {
    	printf("\n\n %d.a Tentativa:  ",i+1);
    	p = rand() % 15;
   		raio = rand() % 100;
   		printf("\nRAIO: %d\n",raio);
		busca(raiz,pontosN[p],raio);
		i++;
	}
	textcolor(7);
    return 1;
}
