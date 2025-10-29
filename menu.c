/*O Pronto Socorro "Heap or Quick" é muito importante na sua comunidade, 
atendendo todo tipo de emergência médica. Quando chega ao Pronto Socorro, 
o paciente é imediatamente encaminhado para a Enfermeira Chefe da Recepção. 
Ela é uma senhora muito experimente e imediatamente determina a prioridade 
do paciente e faz seu cadastramento na Fila de Prioridades.

Programe uma Fila de Prioridades para a Enfermeira Chefe, 
implementando o Tipo Abstrato de Dados Heap. 
Cada paciente tem cadastrado nome e prioridade.*/

/*Explique sua implementação das operações, em particular as operações 
RemoveHeap e AlteraHeap. Faça uma interface caprichada (menu de opções) 
para a Enfermeira Chefe usar seu sistema.*/

/*Faça uma opção no menu para gerar um vetor de números aleatórios 
com 1024 elementos e mostre a comparação do HeapSort com o QuickSort e o SelectSort. 
Qual foi melhor na prática? Para cada algoritmo mostre o número de comparações 
e trocas de elemento de lugar.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int caminho;
    printf("MENU PRONTO SOCORRO HEAP OR QUICK:\n");
    printf("ALERTA: Somente aperte botões sugeridos pelo menu.\n");
	printf("Se você apertar alguma tecla errada, REINICIE O PROGRAMA!\n");
	printf("\n");

    printf("Escolha qual caminho seguir:\n");
    printf("1 - Menu Pronto Socorro ""Heap or Quick\n");
    printf("2 - Ordenação de vetor com números aleatórios\n");
    printf(">>");
    scanf("%d", &caminho);
    printf("\n");
    if(caminho == 1)
    {
        printf("Você entrou no menu do pronto socorro Heap or Quick.\n");
    }
    else if (caminho == 2)
    {  
        printf("Você entrou na área de ordenação de vetor.\n");
    }



    return (0);
}

