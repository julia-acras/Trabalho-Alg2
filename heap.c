#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"


long long comparacoes = 0;
long long trocas = 0;

void troca_pacientes(struct paciente *paciente1, struct paciente *paciente2)
{
    struct paciente aux;
    
    aux = *paciente1;
    *paciente1 = *paciente2;
    *paciente2 = aux;
}

void InicHeap(int tam, struct paciente v[]) 
{
    for (int i = 1; i <= tam; i++) 
    {
        strcpy(v[i].nome, "");
        v[i].prioridade = 0;
    }
}


void InsereHeap(int tam, struct paciente v[])
{
    int i;

    i = tam;
    while((i > 1) && (v[i/2].prioridade > v[i].prioridade))
    {
        comparacoes+=2;
        troca_pacientes(&v[i/2], &v[i]);
        trocas++;
        i=i/2;
    }
}

void Heapfy (int tam, struct paciente v[]) 
{
    int i;

    for (i = 2; i <= tam; i++) 
        InsereHeap(i, v);
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

void RemoveHeap(int *tam, struct paciente v[])
{

    v[1] = v[*tam];
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
        if (i < tam) 
        {
            comparacoes++;
            if (v[i].prioridade > v[i+1].prioridade)
                i++;
        }

        comparacoes++;
        if (v[i/2].prioridade <= v[i].prioridade)
            break;
        
        troca_pacientes(&v[i/2], &v[i]);
        trocas++;
        i*=2;
    }
}

void HeapSort(int tam, struct paciente v[]) 
{
    int i;

    Heapfy(tam, v);
    for (i = tam; i > 1; i--)
    {
        troca_pacientes(&v[i], &v[1]);
        trocas++;
        SacodeHeap(i-1, v);
    }
}

int AlteraHeap(int tam, struct paciente v[], char nome[100], int prioridade) 
{
    if (v == NULL)
        return (0);

    for (int i = 1; i <= tam; i++)
    {
        if ((strcmp(v[i].nome, nome) == 0))
        {
            v[i].prioridade = prioridade;
            return (1);
        }
    }
    return(0);
}
