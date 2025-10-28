#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Ideia fazer um vetor que vamos manipular com heap.
    Vetor de structs pacientes - cada elemento do vetor é uma struct paciente
    *InicHeap, InsereHeap, RemoveHeap, Heapfy, ChecaHeap, ImprimeHeap, HeapSort, AlteraHeap
*/


struct paciente
{
    char nome[100];
    int prioridade;
};

struct paciente *InicHeap(int tam)
{
    struct paciente *fila;

    fila = malloc(tam * sizeof(struct paciente));

    if (fila == NULL)
        return(NULL);

    return(fila);
}


void InsereHeap(int tam, struct paciente vetor[])
{
    int i, j;
    struct paciente aux;

    j = tam+1;
    while(j > 1 && vetor[i/2].prioridade < vetor[i].prioridade)
    {
        //troca
        aux = vetor[i/2];
        vetor[i/2] = vetor[i];
        vetor[i] = aux;
        i = i/2;
    }
}

void Heapfy (int N, struct paciente V[]) 
{
    int j;
    for (j = 1; j < N; j++) 
        InsereHeap(j,V);
}

int checaheap(struct paciente v[], int N){
    int i=N;
    for ( i=N;i>1;i--){
        if (v[i].prioridade>v[i/2].prioridade)
            return 0;}
    return 1;
}

void RemoveHeap (int N, struct paciente V[], struct paciente p)
{
    int i; 

    while ((i <= N) && ((strcmp(V[i].nome, p.nome) != 0) && (V[i].prioridade != p.prioridade))) i++;
    {
        for (i; i <= N; i++) 
            V[i] = V[i + 1];
    }   
    (N)--;

    if (checaheap(V, N) == 0) Heapfy(N, V);
}



void imprimeHeap(struct paciente v[], int N) {
    for (int i = 1; i <= N; i++) {
        printf("%s (prioridade %d)\n", v[i].nome, v[i].prioridade);
    }
}

void SacodeHeap(int tam, struct paciente v[]) {
    int i = 2;
    struct paciente aux;

    while (i <= tam) {
        if (i < tam && v[i].prioridade < v[i + 1].prioridade)
            i++;
        if (v[i/2].prioridade >= v[i].prioridade)
            break;
        aux = v[i/2];
        v[i/2] = v[i];
        v[i] = aux;
        i *= 2;
    }
} 

void HeapSort(struct paciente vetor[], int N) {
    int i;
    struct paciente aux;

    Heapfy(N, vetor);
    for (i = N; i > 1; i--) {
        aux = vetor[1];
        vetor[1] = vetor[i];
        vetor[i] = aux;
        SacodeHeap(i-1, vetor);
    }
}


void AlteraHeap(struct paciente vetor[], int posicao, int prioridade, int tam) {
    vetor[posicao].prioridade = prioridade;
    if (!checaheap(tam, vetor)) 
        Heapfy(tam, vetor);
}


