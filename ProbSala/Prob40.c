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