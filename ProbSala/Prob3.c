#include <stdio.h>

int main(){
    int nota;
    printf("Digite sua nota: ");
    scanf("%d", &nota);
    if( nota >= 4 && nota <=6){
        printf("Tá encima do muro \n");
    }
    else{
        printf("Ta suave :) \n");
    }
}