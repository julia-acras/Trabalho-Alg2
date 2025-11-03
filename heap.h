#ifndef HEAP_H
#define HEAP_H

extern long long comparacoes;
extern long long trocas;


/*Cada paciente tem cadastrado nome e prioridade.*/
struct paciente
{
    char nome[100];
    int prioridade;
};

void InicHeap(int tam, struct paciente v[]);

void InsereHeap(int tam, struct paciente v[]);

void Heapfy (int tam, struct paciente v[]);

int ChecaHeap(int tam, struct paciente v[]);

void RemoveHeap(int *tam, struct paciente v[]);

void ImprimeHeap(int tam, struct paciente v[]);

void SacodeHeap(int tam, struct paciente v[]);

void HeapSort(int tam, struct paciente v[]);

int AlteraHeap(int tam, struct paciente v[], char nome[100], int prioridade); 

#endif