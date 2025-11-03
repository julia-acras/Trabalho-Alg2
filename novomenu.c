#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

//long long comparacoes;
//long long trocas;

/*---------------------Função de troca de inteiros--------------------*/
void troca(int *a, int *b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}
/*---------------------------------------------------------------------*/

/*--------------------------Select Sort--------------------------------*/

/*Complexidade = O(n^2)
Trocas = n-1*/
void SelectSort(int tam, int vetor[]) 
{
  	int i, j, menor_elemento;

 	for (i = 1; i < tam; i++) 
    {
        comparacoes++;
 		menor_elemento = i;
 		for (j = i+1 ; j <= tam; j++) 
        {
			comparacoes+=2; 
 			if (vetor[j] < vetor[menor_elemento])
                menor_elemento = j;
 		}
 		troca(&vetor[menor_elemento], &vetor[i]);
		trocas++;
 	}
    if(i == tam)
        comparacoes++;
}
/*---------------------------------------------------------------------*/



/*-------------------------Quick Sort (pivo mediana)-------------------*/
int mediana(int a, int b, int c) 
{
    if ((a >= b && a <= c) || (a <= b && a >= c))
        return (a);
    if ((b >= a && b <= c) || (b <= a && b >= c))
        return (b);

    return (c);
}

void particao(int vetor[], int esq, int dir, int *pos_pivo)
{   
    int i, j, pivo, meio;

    meio = esq + (dir - esq) / 2;
    pivo = mediana(vetor[esq], vetor[meio], vetor[dir]);

    if (pivo == vetor[meio])
    {
        comparacoes++;
        troca(&vetor[esq], &vetor[meio]);
        trocas++;
    }
    else if (pivo == vetor[dir]) 
    {   
        comparacoes++;
        troca(&vetor[esq], &vetor[dir]);
        trocas++;
    }
    pivo = vetor[esq];
    i = esq;
    j = dir;

    while (i < j)
    {
        while (i < dir)
        { 
            if(vetor[i] <= pivo)
                i++;
            comparacoes+=2;
        }
        while (j > esq && vetor[j]  > pivo) 
        {    
            if(vetor[j]  > pivo)
                j--;
            comparacoes+=2;
        }
        comparacoes++;
        if (i < j)
        {
            troca(&vetor[i], &vetor[j]);
            trocas++;
        }
    }

    troca(&vetor[esq], &vetor[j]);
    trocas++;
    *pos_pivo = j;
}



void QuickSort(int vetor[], int esq, int dir)
{
    int pos_pivo;
    if(esq < dir)
    {
        comparacoes++;
        particao(vetor, esq, dir, &pos_pivo);
        QuickSort(vetor, esq, pos_pivo-1);
        QuickSort(vetor, pos_pivo+1, dir);
    }
}
/*---------------------------------------------------------------------*/

/*-------------------------Funções para Heap Sort----------------------*/
void InsereHeap_vetor(int tam, int v[])
{
    int i;

    i = tam;
    while((i > 1) && (v[i/2]< v[i]))
    {
        comparacoes+=2;
        troca(&v[i/2], &v[i]);
        trocas++;
        i=i/2;
    }
}

void Heapfy_vetor(int tam, int v[]) 
{
    int i;

    for (i = 2; i <= tam; i++) 
        InsereHeap_vetor(i, v);

    //printf("Comparacoes no HeapFy: %d\n", comparacoes);
    //printf("Trocas no Heapfy: %d\n", trocas);

}

void SacodeHeap_vetor(int tam, int v[]) 
{
    int i;
    i = 2;

    while (i <= tam) 
    {
        comparacoes++;
        if (i < tam) 
        {
            comparacoes++;
            if (v[i] < v[i+1])
                i++;
        }

        comparacoes++;
        if (v[i/2] >= v[i])
            break;
        
        troca(&v[i/2], &v[i]);
        trocas++;

        i*=2;
    }
}

void HeapSort_vetor(int tam, int v[]) 
{
    int i;

    Heapfy_vetor(tam, v);
    for (i = tam; i > 1; i--)
    {
        troca(&v[i], &v[1]);
        trocas++;
        SacodeHeap_vetor(i-1, v);
    }
}

/*-----------------------Função imprime vetor--------------------------*/
void ImprimeVetor_vetor(int tam, int v[])
{
    int i;

    for(i = 1; i <= tam; i++)
        printf("%d ", v[i]);
    printf("\n");
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

/*---------------------------Copiar vetor------------------------------*/
void GeraCopias(int base[], int tam, int copia_heap[], int copia_quick[], int copia_select[])
{
    int i;
    for (i = 1; i <= tam; i++) 
    {
        copia_heap[i] = base[i];
        copia_quick[i] = base[i];
        copia_select[i] = base[i];
    }
}
/*---------------------------------------------------------------------*/

/*----------------------------Heap-------------------------------------*/
/*void troca_pacientes(struct paciente *paciente1, struct paciente *paciente2)
{
    struct paciente aux;
    
    aux = *paciente1;
    *paciente1 = *paciente2;
    *paciente2 = aux;
}*/

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

int main()
{
    int caminho, tamanho_vetor = 1024, ordem, tamanho_fila = 0, capacidade_fila = 1000, imprime;
    struct paciente novo;
    struct paciente fila[1001];
    int v[tamanho_vetor+1]; //nossos algoritmos de ordenação manipulam a partir de v[1]
    int copia_quick[tamanho_vetor+1], copia_select[tamanho_vetor+1], copia_heap[tamanho_vetor+1]; //sera
    int saida;

    printf("MENU PRONTO SOCORRO \"HEAP OR QUICK\":\n");
    printf("ALERTA: Somente aperte botões sugeridos pelo menu.\n");
	printf("Se você apertar alguma tecla errada, REINICIE O PROGRAMA!\n");
	printf("\n");

    /*---Escolha de qual caminho seguir---*/
    printf("Tecle \"1\" para acessar o menu hospitalar.\n");
    printf("Tecle \"2\" para acessar a área de ordenação de vetores.\n");
    //printf("1 - Menu Pronto Socorro ""Heap or Quick\n");
    //printf("2 - Ordenação de vetor com números aleatórios\n");
    printf(">>");
    scanf("%d", &caminho);
    printf("\n");
    saida = 0;
    InicHeap(tamanho_fila, fila);
    if(caminho == 1)
    {
        printf("Você entrou no menu do pronto socorro Heap or Quick.\n");

        while (saida == 0)
        {

            printf("Tecle \"1\" para cadastrar novo paciente na fila.\n");
            printf("Tecle \"2\" para chamar próximo paciente da fila.\n");
            printf("Tecle \"3\" para imprimir os pacientes na fila.\n");
            printf("Tecle \"4\" para ordenar os pacientes na fila, conforme a prioridade.\n");
            printf("Tecle \"5\" para alterar a prioridade de paciente");
            printf("\n");
            printf(">>");
            scanf("%d", &ordem);
            printf("\n");
            if(ordem == 1)
            {
                /*Cadastro de novo paciente*/
                printf("Digite o nome do paciente: ");
                scanf("%s", novo.nome);
                printf("\n");
                printf("Digite a prioridade de %s: ", novo.nome);
                scanf("%d", &novo.prioridade);
                printf("\n");

                if((InserirPaciente(novo, fila, &tamanho_fila, capacidade_fila)) == 1)
                    printf("Fila atualizada! Quantidade de pessoas na fila: %d\n", tamanho_fila);
                else
                    printf("Fila nao atualizada, tente novamente.\n");

                printf("\n");
                printf("Deseja imprimir a fila?\n");
                printf("1 - SIM\n");
                printf("2 - NÃO\n");
                printf(">>");
                scanf("%d", &imprime);
                printf("\n");
                printf("\n");
                if(imprime == 1)
                {
                    printf(">>Fila: \n");
                    ImprimeHeap(tamanho_fila, fila);
                    printf("\n");
                }

            }

            else if(ordem == 2)
            {
            /*Chamar prox paciente na fila*/
                printf("Removendo primeiro paciente...\n");

                RemoveHeap(&tamanho_fila, fila);

                printf("Fila atualizada!\n");
                printf("Deseja imprimir a fila?\n");
                printf("1 - SIM\n");
                printf("2 - NÃO\n");
                printf(">>");
                scanf("%d", &imprime);
                printf("\n");
                if(imprime == 1)
                {
                    printf(">>Fila: \n");
                    ImprimeHeap(tamanho_fila, fila);
                    printf("\n");
                }
                

            }

            else if(ordem == 3)
            {
            //para imprimir os pacientes na fila
                printf(">>Fila: \n");
                ImprimeHeap(tamanho_fila, fila);
                printf("\n");
            }
            else if(ordem == 4)
            {
            //para ordenar os pacientes na fila, conforme a prioridade.
                printf("Ordenando a fila...\n");
                HeapSort(tamanho_fila, fila);
                printf(">>Fila ordenada:\n");
                ImprimeHeap(tamanho_fila, fila);
                printf("\n");
                printf("Deseja imprimir a fila?\n");
                printf("1 - SIM\n");
                printf("2 - NÃO\n");
                printf(">>");
                scanf("%d", &imprime);
                printf("\n");
                if(imprime == 1)
                {
                    printf(">>Fila: \n");
                    ImprimeHeap(tamanho_fila, fila);
                    printf("\n");
                }
                
            
            }
            else
            {   
                struct paciente alterar;
                int achou;
            //para alterar a prioridade de paciente
                printf("Digite o nome do paciente a ser alterado: ");
                scanf("%s", alterar.nome);
                printf("\n");
                printf("Digite a nova prioridade de %s: ", alterar.nome);
                scanf("%d", &alterar.prioridade);
                achou = 0;
                for (int i = 1; i <= tamanho_fila; i++)
                {
                    if ((strcmp(fila[i].nome, alterar.nome) == 0))
                    {
                        achou = 1;
                        AlteraHeap(tamanho_fila, fila, i, alterar.prioridade);
                    }
                }
                if(achou == 0)
                    printf("Paciente não encontrado.");
                if(achou == 1)
                {
                    printf("Prioridade alterada. Deseja ver a fila?\n");
                    printf("1 - SIM\n");
                    printf("2 - NÃO\n");
                    printf(">>");
                    scanf("%d", &imprime);
                    printf("\n");

                    if(imprime == 1)
                    {
                        printf(">>Fila: \n");
                        ImprimeHeap(tamanho_fila, fila);
                        printf("\n");
                    }
                }
            }
            printf("Deseja sair do menu?\n");
            printf("0 - NÃO\n");
            printf("1 - SIM\n");
            printf(">>");
            scanf("%d", &saida);
            printf("\n");
        }

    }
    else if (caminho == 2)
    {  
        printf("Você entrou na área de ordenação de vetor.\n");

        /*Faça uma opção no menu para gerar um vetor de números aleatórios com 1024
         elementos e mostre a comparação do HeapSort com o QuickSort e o SelectSort. 
         Qual foi melhor na prática? Para cada algoritmo mostre o número de comparações 
         e trocas de elemento de lugar.*/

        printf("Gerando vetor aleatório de 1024 elementos!\n");
        printf(">>");
        CriaVetor(v);
        printf("Vetor original:\n");
        ImprimeVetor_vetor(tamanho_vetor, v);
        printf("\n");

        GeraCopias(v, tamanho_vetor, copia_heap, copia_quick, copia_select);
        /*Ordenacao por Quick Sort---------------*/
        printf("Ordenação por Quick Sort:\n");
        comparacoes = 0;
        trocas = 0;
        QuickSort(copia_quick, 1, tamanho_vetor);
        //printf("Vetor ordenado por Quick Sort:\n");
        //ImprimeVetor(tamanho_vetor, copia_quick);
        printf("\n");
        printf("Comparações Quick Sort: %lld\n", comparacoes);
        printf("Trocas Quick Sort: %lld\n", trocas);
        printf("---------------------------------------------\n");
        /*--------------------------------------*/
        printf("\n");

        /*Ordenacao por Select Sort---------------*/
        printf("Ordenação por Select Sort:\n");
        comparacoes = 0;
        trocas = 0;
        SelectSort(tamanho_vetor, copia_select);
        //printf("Vetor ordenado por Select Sort:\n");
        //ImprimeVetor(tamanho_vetor, copia_select);
        printf("\n");
        printf("Comparações Select Sort: %lld\n", comparacoes);
        printf("Trocas Select Sort: %lld\n", trocas);
        printf("---------------------------------------------\n");
        /*--------------------------------------*/
        printf("\n");

        /*Ordenacao por Heap Sort---------------*/
        printf("Ordenação por Heap Sort:\n");
        comparacoes = 0;
        trocas = 0;
        HeapSort_vetor(tamanho_vetor, copia_heap);
        //printf("Vetor ordenado por Heap Sort:\n");
        //ImprimeVetor(tamanho_vetor, copia_heap);
        printf("\n");
        printf("Comparações Heap Sort: %lld\n", comparacoes);
        printf("Trocas Heap Sort: %lld\n", trocas);
        printf("---------------------------------------------\n");
        /*--------------------------------------*/
    }

    return (0);
}
