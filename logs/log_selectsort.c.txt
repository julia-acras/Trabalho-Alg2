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

/*--------------------------Select Sort--------------------------------*/
void SelectSort(int tam, int vetor[]) 
{
  	int i, j, menor_elemento;

 	for (i = 1; i < tam; i++) 
    {
        //comparacoes++;
 		menor_elemento = i;
 		for (j = i+1 ; j <= tam; j++) 
        {
			comparacoes++; 
 			if (vetor[j] < vetor[menor_elemento])
                menor_elemento = j;
 		}
 		troca(&vetor[menor_elemento], &vetor[i]);
		trocas++;
 	}
    //if(i == tam)
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
    printf("Ordenando por Select Sort...\n");
    comparacoes = 0;
    trocas = 0;
    SelectSort(1024, v);
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