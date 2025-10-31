#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

/* Ideia fazer um vetor que vamos manipular com heap.
    Vetor de structs pacientes - cada elemento do vetor é uma struct paciente
    *InicHeap, InsereHeap, RemoveHeap, Heapfy, ChecaHeap, ImprimeHeap, HeapSort, AlteraHeap
*/

/*Quando executar as funções Heapfy e HeapSort deve ser reportado 
o número de comparações e trocas de elemento de posição que foram executadas.
*/

long long comparacoes;
long long trocas;

/*Cada paciente tem cadastrado nome e prioridade.*/
/*struct paciente
{
    char nome[100];
    int prioridade;
};*/

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
    while((i > 1) && (v[i/2].prioridade < v[i].prioridade))
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
        if (i < tam) 
        {
            comparacoes++;
            if (v[i].prioridade < v[i+1].prioridade)
                i++;
        }

        comparacoes++;
        if (v[i/2].prioridade >= v[i].prioridade)
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

void AlteraHeap(int tam, struct paciente v[], int posicao, int prioridade) 
{
    if ((v == NULL) || (posicao < 0) || (posicao >= tam))
        return;

    v[posicao].prioridade = prioridade;

    if (ChecaHeap(tam, v) == 0)
        Heapfy(tam, v);
}

//nao sei se pode :) mas foi o unico jeito q achei
int InserirPaciente(struct paciente novo, struct paciente v[], int *tam, int capacidade_fila) 
{
    if (*tam + 1 > capacidade_fila) 
        return(0);
    
    (*tam) ++;
    
    v[*tam] = novo;                   
    InsereHeap(*tam, v);               
    return(1);
}

int main()
{
    int tam;
    tam = 3;
    struct paciente fila[100];
    InicHeap(tam, fila);
    printf("testando heap\n");
    fila[1].prioridade = 99;
    fila[2].prioridade = 2;
    fila[3].prioridade = 59;
    strcpy(fila[1].nome, "julia");
    strcpy(fila[2].nome, "duda");
    strcpy(fila[3].nome, "elias");

    Heapfy(tam, fila);
    ImprimeHeap(tam, fila);
    printf("\n");
    HeapSort(tam, fila);
    ImprimeHeap(tam, fila);
    printf("\n");

    struct paciente novo; //pensar jeito melhor - por causa do menu
    novo.prioridade = 37;
    strcpy(novo.nome, "isadora");
    if(InserirPaciente(novo, fila, &tam, 100) == 1)
        ImprimeHeap(tam, fila);
    printf("\n");

    AlteraHeap(tam, fila, 2, 56);

    RemoveHeap(&tam, fila, fila[2]);
    ImprimeHeap(tam, fila);
    return(0);
}