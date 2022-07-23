#include <stdio.h>
int main(){
    int miau = 0;
    
    int n;
    scanf("%d", &n);
    int M[n][n];
    for(int i = 0; i<n ; i++){
        for (int j = 0; j<n; j++){
            scanf("%d", &M[i][j]);
        }
    }
    for(int i = 0; i<n ; i++){
        for (int j = 0; j<n; j++){
            
            if(M[j][i] != M[i][j]){
                miau = 1;
            }
            
        }
    }
    if(miau){
        printf("Não simétrica");
    }
    else{
        printf("Simétrica");
    }
}

/*
void lematriz(int m, int n, int M[MAX][MAX]){

}

void impmatriz(int m, int n, int M[MAX][MAX]){

}

int main(){
    int n, M[MAX][MAX];
    int i, j, simetrica = 1;
    scanf("%d, &n);
    lematrz(n, n, M[MAX][MAX]);
    for(i = 0; i < n-1 && simétrica; i++){
        for (j = i +1; j<n && simetrica; j++){
            if(M[i][j] != M[j][i]){
                simetrica = 0;
            }
        }
    }
    if (simetrica){
        printf("Sim\n");
    }
    else{
        printf("Não\n");
    }
}
*/