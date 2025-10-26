//Arquivo algoritmos de ordenação

#include <stdio.h>
#include <stdlib.h>

long long comparacoes;
long long trocas;

//Função troca------------------------------------------------------
void troca(int *a, int *b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}
//------------------------------------------------------------------
//Select Sort-------------------------------------------------------
void select_sort(int tam, int vetor[]) 
{
  	int i, j, menor_elemento;

 	for (i = 0 ; i < (n-1) ; i++) 
    {
 		menor_elemento = i;
 		for (j = i+1 ; j < n ; j++) 
        {
			comparacoes++; 
 			if (vetor[j] < vetor[menor_elemento]) 
                menor_elemento = j;
 		}
 		troca(&vetor[menor_elemento], &vetor[i]);
		trocas++;
 	}
}
//-------------------------------------------------------------------


//Quick pivo sendo o primeiro---------------------------------
void particao_primeiro_elemento(int vetor[], int esq, int dir, int pos_pivo)
{
    int i, j, pivo;
    i = esq;
    j = dir;
    pivo = vetor[esq];

    while (i < j)
    {
        while(vetor[i] <= pivo && i < dir)
            i++;
        while(vetor[j] > pivo)
            j--;

        if(i < j)
        {
            troca(&vetor[i], &vetor[j])
        }
    }
    troca(&vetor[esq], &vetor[j]);
    *pos_pivo = j;
}

void quick_sort_primeiro_elemento(int vetor[], int esq, int dir)
{
    int pos_pivo;
    if(esq < dir)
    {
        particao_primeiro_elemento(vetor, esq, dir, &pos_pivo);
        quick_sort_primeiro_elemento(vetor, esq, pos_pivo-1);
        quick_sort_primeiro_elemento(vetor, pos_pivo+1, dir);
    }
}
//------------------------------------------------------------------

// Quick sort pivo sendo mediana -----------------------------------
int mediana(int a, int b, int c)
{
    if ((a >= b && a <= c) || (a <= b && a >= c)) 
        return (a);
    if ((b >= a && b <= c) || (b <= a && b >= c)) 
        return (b);
    return (c);
}

void particao_mediana(int vetor[], int esq, int dir, int *pos_pivo)
{   
    int i, j, pivo, meio;

    meio = esq + (dir - esq) / 2;
    pivo = mediana(vetor[esq], vetor[meio], vetor[dir]);

    if (pivo == vetor[meio])
    { 
        troca(&vetor[esq], &vetor[meio]);
        trocas++;
    }
    else if (pivo == vetor[dir]) 
    {    
        troca(&vetor[esq], &vetor[dir]);
        trocas++;
    }
    pivo = vetor[esq];
    i = esq;
    j = dir;

    while (i < j)
    {
        while (i < dir && vetor[i] <= pivo) 
        { 
            i++;
            comparacoes++
        }
        comparacoes++;

        while (j > esq && vetor[j]  > pivo) 
        {    
            j--;
            comparacoes++;
        }
        if (i < j)
        {   
            troca(&vetor[i], &vetor[j]);
            trocas++;
        }
    }

    troca(&vetor[esq], &vetor[j]);
    troca++;
    *pos_pivo = j;
}

void quick_sort_mediana(int vetor[], int esq, int dir)
{
    int pos_pivo;
    if(esq < dir)
    {
        particao_mediana(vetor, esq, dir, &pos_pivo);
        quick_sort_mediana(vetor, esq, pos_pivo-1);
        quick_sort_mediana(vetor, pos_pivo+1, dir);
    }
}
//------------------------------------------------------------------

//Quick com pivo sendo o ultimo-------------------------------------
void particao_ultimo_elemento(int vector[], int esq, int dir, int pos_pivo) {

    int i, j, pivo;
    i = esq;
    j = dir;
    pivo = vetor[dir]; 

	while (i < j)
    {
        while (i < dir && vetor[i] <= pivo)
            i++;
        while (j > esq && vetor[j] > pivo)
            j--;

        if (i < j)
        {
            troca(&vetor[i], &vetor[j]);
        }
    }

    troca(&vetor[dir], &vetor[i]);
    *pos_pivo = i;
}

void quick_sort_ultimo_elemento(int vetor[], int esq, int dir)
{
    int pos_pivo;
    if(esq < dir)
    {
        particao_ultimo_elemento(vetor, esq, dir, &pos_pivo);
        quick_sort_ultimo_elemento(vetor, esq, pos_pivo-1);
        quick_sort_ultimo_elemento(vetor, pos_pivo+1, dir);
    }
}
//------------------------------------------------------------------

//COLOCAR HEAP