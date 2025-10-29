#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Ideia fazer um vetor que vamos manipular com heap.
    Vetor de structs pacientes - cada elemento do vetor é uma struct paciente
    *InicHeap, InsereHeap, RemoveHeap, Heapfy, ChecaHeap, ImprimeHeap, HeapSort, AlteraHeap
*/

/*Quando executar as funções Heapfy e HeapSort deve ser reportado o número de comparações e trocas 
    de elemento de posição que foram executadas.
*/

long long comparacoes;
long long trocas;

struct paciente
{
    char nome[100];
    int prioridade;
};

void troca_pacientes(struct paciente *paciente1, struct paciente *paciente2)
{
    struct paciente aux;
    
    aux = *paciente1;
    *paciente1 = *paciente2;
    *paciente2 = aux;
}

struct paciente *InicHeap(int tam)
{
    struct paciente *fila;

    fila = malloc((tam+1) * sizeof(struct paciente));

    if (fila == NULL)
        return(NULL);

    return(fila);
}


void InsereHeap(int tam, struct paciente v[])
{
    int i;

    i = tam;
    while((i > 1) && (v[i/2].prioridade < v[i].prioridade))
    {
        comparacoes+= 2;
        troca_pacientes(&v[i/2], &v[i]);
        trocas++;
    }
}




void Heapfy (int tam, struct paciente v[]) 
{
    int i;

    for (i = 2; i <= tam; i++) 
        InsereHeap(i, v);

    //printf("Comparacoes no HeapFy: %d\n", comparacoes);
    //printf("Trocas no Heapfy: %d\n", trocas);

}

int ChecaHeap(int tam, struct paciente v[])
{
    int i;
    
    for (i = 2; i <= tam; i++)
    {
        if (v[i].prioridade > v[i/2].prioridade)
            return (0);
    }
    return (1);
}

void RemoveHeap(int *tam, struct paciente v[], struct paciente alvo)
{
    int i;

    if (*tam <= 0) 
        return;
    
    i = 1;
    while (i <= *tam && (strcmp(v[i].nome, alvo.nome) != 0 || v[i].prioridade != alvo.prioridade))
        i++;

    if (i > *tam) 
        return;

    v[i] = v[*tam];
    (*tam)--;

    if (*tam < 1)
        return; 

    if (ChecaHeap(*tam, v) == 0)
        Heapfy(*tam, v);
}



void ImprimeHeap(int tam, struct paciente v[]) 
{
    int i;

    for (i = 1; i <= tam; i++)
        printf("%s (prioridade %d)\n", v[i].nome, v[i].prioridade);
}

void SacodeHeap(int tam, struct paciente v[]) 
{
    int i;
    i = 2;

    while (i <= tam) 
    {
        comparacoes++;
        if (i < tam && v[i].prioridade < v[i+1].prioridade)
        {
            i++;
            comparacoes++;
        }

        if (v[i/2].prioridade >= v[i].prioridade)
        { 
            comparacoes++;
            break;
        }
        
        troca_pacientes(&v[i/2], &v[i]);
        trocas++;
    }
}

void HeapSort(int tam, struct paciente v[]) 
{
    int i;

    Heapfy(tam, v);
    for (i = tam; i > 1; i--) {
        troca_pacientes(&v[i], &v[1]);
        trocas++;
        SacodeHeap(i-1, v);
    }
}

void AlteraHeap(int tam, struct paciente v[], int posicao, int prioridade) 
{
    if ((v == NULL) || (posicao < 0) || (posicao >= tam))
        return;

    v[posicao].prioridade = prioridade;

    if (ChecaHeap(tam, v) == 0)
        Heapfy(tam, v);
}
