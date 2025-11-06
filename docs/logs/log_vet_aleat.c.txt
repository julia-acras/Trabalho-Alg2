#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int v_aleat[1025];
    srand(time(NULL));
    printf("Criando vetor aleatório de 1024 elementos...\n");
    CriaVetor(v_aleat);
    printf("Imprimindo 50 primeiros elementos:\n");
    ImprimeVetor_pt1(1024, v_aleat);
    printf("\n");
    printf("Imprimindo 50 ultimos elementos:\n");
    ImprimeVetor_pt2(1024, v_aleat);
    printf("\n");

    return(0);
}
