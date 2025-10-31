#ifndef HEAP_H
#define HEAP_H




/*Cada paciente tem cadastrado nome e prioridade.*/
struct paciente
{
    char nome[100];
    int prioridade;
};

void troca_pacientes(struct paciente *paciente1, struct paciente *paciente2);

void InicHeap(int tam, struct paciente v[]);

void InsereHeap(int tam, struct paciente v[]);

void Heapfy (int tam, struct paciente v[]);

int ChecaHeap(int tam, struct paciente v[]);

void RemoveHeap(int *tam, struct paciente v[], struct paciente alvo);

void ImprimeHeap(int tam, struct paciente v[]);

void SacodeHeap(int tam, struct paciente v[]);

void HeapSort(int tam, struct paciente v[]);

void AlteraHeap(int tam, struct paciente v[], int posicao, int prioridade);

#endif