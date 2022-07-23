#include <stdio.h>
int main(){
    int n, m, aux = 0, j = 0;
    printf("\nDigite m e n: ");
    scanf("%d %d", &m,&n);
    int V[m], V2[n+m];

    printf("\nDigite a primeira sequência: ");

    for(int i = 0; i<m; i++){
        scanf("%d", &V[i]);
    }

    printf("\nDigite a segunda sequência: " );

    for(int i = 0; i<n+m; i++){
        if(i<n){
            scanf("%d", &V2[i]);
        }
        else{
            V2[i] = V[j];
            j ++;
        }
    }

    for(int i = 0; i<n+m; i++){
        for(int j = 0; j<n+m; j++){
            if(V2[i]<V2[j]){
                aux = V2[i];
                V2[i] = V2[j];
                V2[j] = aux;
            }
        }
    }

    printf("\nSequência ordenada com números de ambas, sem repetição: ");

    for(int i = 0; i<n+m; i++){
        if(V2[i] != V2[i + 1]){
            printf("%d ", V2[i]);
        }
    }
}