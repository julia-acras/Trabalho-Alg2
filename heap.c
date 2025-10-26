int checaheap( int v[]){
    int i=N;
    for ( i=N;i>1;i--){
        if (v[i]>v[i/2])
            return 0;}
    return 1;
}

void imprimeHeap(Paciente v[], int N) {
    for (int i = 1; i <= N; i++) {
        printf("%s (prioridade %d)\n", v[i].nome, v[i].prioridade);
    }
}
