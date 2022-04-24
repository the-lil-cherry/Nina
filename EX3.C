#include <stdio.h>

int main (){
    int n, acu, resto;
    
    printf("Digite um número: ");
    scanf("%d", &n);
    resto = n;

    for(int i = 2; i<n; i ++ ){
        acu = 0;

         while(resto%i == 0){
            resto = resto/i;
            acu +=1;
        }
        if(acu !=0){
            printf("fator %d multiplicidade %d\n", i, acu);
        }
        
    }

}