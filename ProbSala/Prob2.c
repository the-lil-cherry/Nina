#include <stdio.h>

int main (){
    int nota;
    printf("Digite sua nota: ");
    scanf("%d", &nota);

    if(nota >= 5){
        printf("Aprovado!!! :)\n");
    }
    else{
        printf("Reprovado :(((\n");
    }
}