//Arquivo algoritmos de ordenação

/*Implemente também os algoritmos de ordenação QuickSort e SelectSort. 

Implemente o QuickSort usando como pivô o elemento que é a 
mediana entre o primeiro, meio e último elementos do (sub-)vetor. 
Faça uma opção no menu para gerar um vetor de números aleatórios com 
1024 elementos e mostre a comparação do HeapSort com o QuickSort e o SelectSort. 
Qual foi melhor na prática? Para cada algoritmo mostre o número de comparações 
e trocas de elemento de lugar.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparacoes;
long long trocas;

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

    comparacoes++;
    if (pivo == vetor[meio])
    {
        troca(&vetor[esq], &vetor[meio]);
        trocas++;
    }
    else 
    {
        comparacoes++;
        if (pivo == vetor[dir]) 
        {
            troca(&vetor[esq], &vetor[dir]);
            trocas++;
        }
    }
    pivo = vetor[esq];
    i = esq;
    j = dir;

    while (i < j)
    {
        comparacoes++;
        while (i < dir && vetor[i] <= pivo) 
        { 
            i++;
            comparacoes+=2;
        }
        if(i < dir && vetor[i] > pivo)
            comparacoes++;

        else if (i >= dir)
            comparacoes++;

        while (j > esq && vetor[j]  > pivo) 
        {    
            j--;
            comparacoes+=2;
        }
        
        if(j > esq)
            comparacoes++;
        else if (i <= esq)
            comparacoes++;

        comparacoes++;
        if (i < j)
        {
            troca(&vetor[i], &vetor[j]);
            trocas++;
        }
    }
    comparacoes+=(j-i+1);

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
    //comparacoes++;
}
/*---------------------------------------------------------------------*/

/*-------------------------Funções para Heap Sort----------------------*/
void InsereHeap(int tam, int v[])
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

void Heapfy (int tam, int v[]) 
{
    int i;

    for (i = 2; i <= tam; i++) 
        InsereHeap(i, v);

    comparacoes+=(tam);

    //printf("Comparacoes no HeapFy: %d\n", comparacoes);
    //printf("Trocas no Heapfy: %d\n", trocas);

}

void SacodeHeap(int tam, int v[]) 
{
    int i;
    i = 2;

    while (i <= tam) 
    {
        //comparacoes++;
        //if (i < tam && v[i]< v[i+1])
        //{
            //i++;
            //comparacoes+=2; //se contar comparar i<j, mas acho q sao so indices do vetor
        //}

        comparacoes++; 
        if (i < tam) 
        {
            comparacoes++; 
            if (v[i] < v[i+1]) 
            {
                i++;
            }
        }

        comparacoes++;
        if (v[i/2] >= v[i])
            break;
        
        troca(&v[i/2], &v[i]);
        trocas++;
    }
    comparacoes+=(tam);
}

void HeapSort(int tam, int v[]) 
{
    int i;

    Heapfy(tam, v);
    for (i = tam; i > 1; i--)
    {

        troca(&v[i], &v[1]);
        trocas++;
        SacodeHeap(i-1, v);
    }
    comparacoes+=tam;
}

/*-----------------------Função imprime vetor--------------------------*/
void ImprimeVetor(int tam, int v[])
{
    int i;

    for(i = 1; i <= tam; i++)
        printf("%d ", v[i]);
    printf("\n");
}
/*---------------------------------------------------------------------*/

/*--------Função de Comparar Algoritmos--------------------------------*/
/*void compara_algoritmos(int n, const int base[]) {

    // cópias
    int a[1025], b[1025], c[1025];

    for (int i = 1; i <= n; i++) {
        a[i] = base[i];
        b[i] = base[i];
        c[i] = base[i];
    }
    long long compS, trocS, compQ, trocQ, compH, trocH;
    // --- Selection ---
    comparacoes = 0; trocas = 0;
    SelectSort(n, a);
    compS = comparacoes; trocS = trocas;

    // --- Quick ---
    comparacoes = 0; trocas = 0;
    QuickSort(b, 1, n);
    compQ = comparacoes; trocQ = trocas;

    // --- Heap ---
    comparacoes = 0; trocas = 0;
    HeapSort(n, c);
    compH = comparacoes; trocH = trocas;

    printf("\n=== COMPARACAO (N=%d; mesmo vetor-base) ===\n", n);
    printf("%-10s | %15s | %12s | %s\n",
           "Metodo", "Comparacoes", "Trocas", "OK?");
    printf("-----------+-----------------+--------------+-----\n");
    printf("%-10s | %15lld | %12lld\n", "Selection", compS, trocS);
    printf("%-10s | %15lld | %12lld\n", "Quick",     compQ, trocQ);
    printf("%-10s | %15lld | %12lld\n", "Heap",      compH, trocH);

    const char* melhor = "Selection";
    long long mC = compS, mT = trocS;

    if (compQ < mC || (compQ == mC && trocQ < mT)) {
        melhor = "Quick"; mC = compQ; mT = trocQ;
    }
    if (compH < mC || (compH == mC && trocH < mT)) {
        melhor = "Heap";  mC = compH; mT = trocH;
    }

    printf("\nMelhor na pratica: %s\n", melhor);
}*/
/*---------------------------------------------------------------------*/

/*-------------------Área de espaço para criar vetor-------------------*/
long aleat (long min, long max)
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

int main() 
{
    int metodo, n;
    
    n = 1024;
    int v[1025];
    CriaVetor(v);
    
    printf("\nVetor original:\n");
    ImprimeVetor(n, v);

    printf("\nEscolha o método:\n");
    printf("1 - Selection Sort\n");
    printf("2 - Quick Sort\n");
    printf("3 - Heap Sort\n");
    printf("-> ");
    scanf("%d", &metodo);

    comparacoes = 0;
    trocas = 0;

    if (metodo == 1)
        SelectSort(n, v);
    else if (metodo == 2)
        QuickSort(v, 1, n);
    else if(metodo == 3)
        HeapSort(n, v);

    printf("\nVetor ordenado:\n");
    ImprimeVetor(n, v);

    printf("\nComparações: %lld\n", comparacoes);
    printf("Trocas: %lld\n", trocas);

    return (0);
}


/*int main()
{
    int n = 20, metodo;
    int v[21] = {
        0, 10, 5, 3, 1, 1, 1, 1, 2, 1, 1, 1, 5, 2, 1, 1, 1, 2, 1, 1, 1
      };

      printf("\nVetor original:\n");
      ImprimeVetor(n, v);
  
      printf("\nEscolha o método:\n");
      printf("1 - Selection Sort\n");
      printf("2 - Quick Sort\n");
      printf("3 - Heap Sort\n");
      printf("-> ");
      scanf("%d", &metodo);
  
      comparacoes = 0;
      trocas = 0;
  
      if (metodo == 1)
          SelectSort(n, v);
      else if (metodo == 2)
          QuickSort(v, 1, n);
      else if(metodo == 3)
          HeapSort(n, v);
  
      printf("\nVetor ordenado:\n");
      ImprimeVetor(n, v);
  
      printf("\nComparações: %lld\n", comparacoes);
      printf("Trocas: %lld\n", trocas);
  
      return (0);
}*/



/*int main(){
    int caminho;
    printf("MENU PRONTO SOCORRO HEAP OR QUICK:\n");
    printf("\n");
    printf("Escolha qual caminho seguir:\n");
    printf("1 - Menu Pronto Socorro \"Heap or Quick\"\n");
    printf("2 - Ordenação de vetor com números aleatórios\n");
    printf(">>");
    scanf("%d", &caminho);
    printf("\n");

    if (caminho == 1){
        printf("Você entrou no menu do pronto socorro Heap or Quick.\n");
    }
    else if (caminho == 2){
        printf("Você entrou na área de ordenação de vetor.\n");

        const int N = 1024;
        int base[1025];
        srand((unsigned)time(NULL));  // aleatoriedade
        CriaVetor(base);
        compara_algoritmos(N, base);
    }

    return 0;
}*/