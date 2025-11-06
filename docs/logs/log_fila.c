#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


long long comparacoes = 0;
long long trocas = 0;

#undef QTD
#define QTD 26   // tamanho máximo de cada string

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

/*-----------------------Inserir paciente------------------------------*/
int InserirPaciente(struct paciente novo, struct paciente v[], int *tam, int capacidade_fila) 
{
    if (*tam + 1 > capacidade_fila) 
        return(0);
    
    (*tam) ++;
    
    v[*tam] = novo;                   
    InsereHeap(*tam, v); 

    return(1);
}
/*---------------------------------------------------------------------*/

/*-------------------Área de espaço para criar vetor-------------------*/
long aleat(long min, long max)
{
  return((rand() % (max - min + 1)) + min);
}
/*---------------------------------------------------------------------*/


int main()
{
    struct paciente fila[28];
    struct paciente novo;
    int tamanho_fila = 26;

    for (int i = 1; i <= 26; i++)
    {
        fila[i].nome[0] = 'A' + (i - 1);
        fila[i].nome[1] = '\0';              // termina a string
        fila[i].prioridade = aleat(1, 100); // prioridade de 1 a 100
    }

    strcpy(novo.nome, "Julia");
    novo.prioridade = 61;

    printf("\n");

    /*---------------------------------------------------------------------*/
    printf("Inserindo paciente Julia...\n");

    if((InserirPaciente(novo, fila, &tamanho_fila, 28)) == 1)
    {
        HeapSort(tamanho_fila, fila);
        printf("Fila atualizada! Quantidade de pessoas na fila: %d\n", tamanho_fila);
        printf(">>Fila: \n");
        ImprimeHeap(tamanho_fila, fila);
        printf("\n");
    }
    else
        printf("Fila nao atualizada, tente novamente.\n");
    /*---------------------------------------------------------------------*/
    printf("Removendo primeiro paciente...\n");
    printf("\n");
    
    RemoveHeap(&tamanho_fila, fila);
    HeapSort(tamanho_fila, fila);

    printf(">>Fila: \n");
    ImprimeHeap(tamanho_fila, fila);
    printf("\n");
    /*---------------------------------------------------------------------*/
    printf("Ordenando a fila...\n");
    HeapSort(tamanho_fila, fila);
    printf(">>Fila ordenada:\n");
    ImprimeHeap(tamanho_fila, fila);
    printf("\n");
    /*---------------------------------------------------------------------*/
    printf("Alterando prioridade de Julia de 61 para 24...\n");
    if(AlteraHeap(tamanho_fila, fila, novo.nome, 24) == 0)
        printf("Paciente não encontrado.\n");
    else if(AlteraHeap(tamanho_fila, fila, novo.nome, 24) == 1)
        HeapSort(tamanho_fila, fila);
    printf(">>Fila: \n");
    ImprimeHeap(tamanho_fila, fila);
    printf("\n");
    /*---------------------------------------------------------------------*/
    return(0);
}