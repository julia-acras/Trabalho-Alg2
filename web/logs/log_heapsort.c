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

/*-------------------------Funções para Heap Sort----------------------*/
void InsereHeap(int tam, int v[])
{
    int i;

    i = tam;
    while((i > 1) && (v[i/2]< v[i]))
    {
        comparacoes++;
        troca(&v[i/2], &v[i]);
        trocas++;
        i=i/2;
    }
}

void Heapfy(int tam, int v[]) 
{
    int i;

    for (i = 2; i <= tam; i++) 
        InsereHeap(i, v);

}

void SacodeHeap(int tam, int v[]) 
{
    int i;
    i = 2;

    while (i <= tam) 
    {
        if (i < tam) 
        {
            comparacoes++; 
            if (v[i] < v[i+1]) 
            {
                i++;
            }
        }

        comparacoes++;
        if (v[i/2] >= v[i])
            break;
        
        troca(&v[i/2], &v[i]);
        trocas++;
        
        i*=2;
    }
}

void HeapSort(int tam, int v[]) 
{
    int i;

    Heapfy(tam, v);
    for (i = tam; i > 1; i--)
    {

        troca(&v[i], &v[1]);
        trocas++;
        SacodeHeap(i-1, v);
    }
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
    printf("Ordenando por Heap Sort...\n");
    comparacoes = 0;
    trocas = 0;
    HeapSort(1024, v);
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