#include <stdio.h>

int main (){
    int n, cont, eh_qua = 0, soma1, soma2, soma3 = 0, soma4 = 0;
    scanf("%d\n", &n);
    int A[n][n];
    for(int i = 0; i<n; i++){
        cont = 0;
        for (int j = 0; j<n; j++){
            scanf("%d", &A[i][j]);
            cont += A[i][j]; 
        }
    }

    for(int i = 0; i<n && eh_qua == 0; i++){
        soma1 = 0;
        soma2 = 0;
        
        for (int j = 0; j<n; j++){
            soma1 += A[i][j];
            soma2 +=A[j][i];
        }
        soma3 += A[i][i];
        soma4 += A[i][n-i-1];

        if(cont != soma1 || cont != soma2 ){
            eh_qua = 1;
        }
    }

    if( cont != soma3 || cont != soma4){
         eh_qua = 1;
    }
    
    if(eh_qua == 0){
        printf("A matriz A é um quadrado mágico\n");
    }
    else{
        printf("A matriz A não é um quadrado mágico\n");
    }
    
}