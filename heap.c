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
    for (int i = N - 1; i > 0; i--){
        if (v[i].prioridade > v[i/2].prioridade)
            return 0;
    }
    return 1;
}

/*void RemoveHeap (int N, struct paciente V[], struct paciente p)
{
    int i; 

    while ((i <= N) && ((strcmp(V[i].nome, p.nome) != 0) && (V[i].prioridade != p.prioridade))) i++;
    {
        for (i; i <= N; i++) 
            V[i] = V[i + 1];
    }   
    (N)--;

    if (checaheap(V, N) == 0) Heapfy(N, V);
}*/



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
    printf("DEBUG: vetor=%p  tam=%d  posicao=%d\n", (void*)vetor, tam, posicao);

    if (vetor == NULL) {
        printf("ERRO: vetor NULL!\n");
        return;
    }
    if (posicao < 0 || posicao >= tam) {
        printf("ERRO: indice fora do limite!\n");
        return;
    }

    printf("DEBUG: alterando prioridade de %s (antes %d) para %d\n",
           vetor[posicao].nome, vetor[posicao].prioridade, prioridade);

    vetor[posicao].prioridade = prioridade;

    if (!checaheap(vetor, tam))
        Heapfy(tam, vetor);
}



int main(void) {
    printf("=== TESTE DO SEU HEAP DE PACIENTES ===\n");

    // inicia heap com tamanho 5
    int N = 5;
    struct paciente *fila = InicHeap(N);
    if (fila == NULL) {
        printf("Erro ao alocar heap!\n");
        return 1;
    }

    // preenche alguns pacientes
    strcpy(fila[0].nome, "Ana");
    fila[0].prioridade = 3;
    strcpy(fila[1].nome, "Bruno");
    fila[1].prioridade = 5;
    strcpy(fila[2].nome, "Carlos");
    fila[2].prioridade = 1;
    strcpy(fila[3].nome, "Daniela");
    fila[3].prioridade = 4;
    strcpy(fila[4].nome, "Eduardo");
    fila[4].prioridade = 2;

    printf("\nHeap inicial:\n");
    imprimeHeap(fila, N);

    // testa AlteraHeap
    printf("\nAlterando prioridade de Carlos para 6...\n");
    AlteraHeap(fila, 2, 6, 5);
    imprimeHeap(fila, N);

    // testa HeapSort
    printf("\nAplicando HeapSort...\n");
    HeapSort(fila, N);
    imprimeHeap(fila, N);

    // testa RemoveHeap
    //printf("\nRemovendo paciente Bruno (prio 5)...\n");
    //struct paciente alvo;
    //strcpy(alvo.nome, "Bruno");
    //alvo.prioridade = 5;
    //RemoveHeap(N, fila, alvo);
    //imprimeHeap(fila, N - 1);

    free(fila);
    printf("\n=== FIM DO TESTE ===\n");
    return 0;
}