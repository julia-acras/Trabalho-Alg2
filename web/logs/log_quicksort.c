#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparacoes;
long long trocas;


void troca(int *a, int *b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

/*-------------------------Quick Sort (pivo mediana)-------------------*/
int mediana(int a, int b, int c) 
{
    if ((a >= b && a <= c) || (a <= b && a >= c))
        return (a);
    if ((b >= a && b <= c) || (b <= a && b >= c))
        return (b);

    return (c);
}

void particao(int vetor[], int esq, int dir, int *pos_pivo)
{   
    int i, j, pivo, meio;

    meio = esq + (dir - esq) / 2;
    pivo = mediana(vetor[esq], vetor[meio], vetor[dir]);

    if (pivo == vetor[meio])
    {
        troca(&vetor[esq], &vetor[meio]);
        trocas++;
    }
    else if (pivo == vetor[dir]) {
            troca(&vetor[esq], &vetor[dir]);
            trocas++;
        }
    pivo = vetor[esq];
    i = esq + 1;
    j = dir;

    while (i < j)
    {
        while (i <= dir && vetor[i] <= pivo) 
        { 
            i++;
            comparacoes++;
        }
        while (j >= esq+1 && vetor[j]  > pivo) 
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
    trocas++;
    *pos_pivo = j;
}

void QuickSort(int vetor[], int esq, int dir)
{
    int pos_pivo;
    if(esq < dir)
    {
        particao(vetor, esq, dir, &pos_pivo);
        QuickSort(vetor, esq, pos_pivo-1);
        QuickSort(vetor, pos_pivo+1, dir);
    }
    //comparacoes++;
}
/*---------------------------------------------------------------------*/

/*-------------------Área de espaço para criar vetor-------------------*/
long aleat(long min, long max)
{
  return((rand() % (max - min + 1)) + min);
}

void CriaVetor(int v[]) 
{
    int i; 

	for (i = 1; i <= 1024; i++) 
		v[i] = aleat(0,2048);
}
/*---------------------------------------------------------------------*/

/*-----------------------Função imprime vetor--------------------------*/
void ImprimeVetor_pt1(int tam, int v[])
{
    int i;

    for(i = 1; i <= 50; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void ImprimeVetor_pt2(int tam, int v[])
{
    int i;

    for(i = 974; i <= tam; i++)
        printf("%d ", v[i]);
    printf("\n");
}
/*---------------------------------------------------------------------*/

int main() 
{


    int v[1025];
    srand(time(NULL));
    printf("Criando vetor aleatório de 1024 elementos...\n");
    CriaVetor(v);
    printf("Imprimindo 50 primeiros elementos:\n");
    ImprimeVetor_pt1(1024, v);
    printf("\n");
    printf("Imprimindo 50 ultimos elementos:\n");
    ImprimeVetor_pt2(1024, v);
    printf("\n");
    printf("Ordenando por Quick Sort...\n");
    comparacoes = 0;
    trocas = 0;
    QuickSort(v, 1, 1024);
    printf("Imprimindo 50 primeiros elementos do vetor ordenado:\n");
    ImprimeVetor_pt1(1024, v);
    printf("\n");
    printf("Imprimindo 50 ultimos elementos do vetor ordenado:\n");
    ImprimeVetor_pt2(1024, v);
    printf("\n");
    printf("Comparações: %lld\n", comparacoes);
    printf("Trocas: %lld\n", trocas);
    printf("\n");
    
    return(0);
        
}