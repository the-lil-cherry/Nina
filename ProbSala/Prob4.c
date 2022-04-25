#include <stdio.h>

int main (){
    double nota;
    printf("Digite sua nota: ");
    scanf("%lf", &nota);
    if(nota <5){
        printf("R\n");
    }
    else{
        if (nota<7)
        {
            printf("C\n");
        }
        else{
            if (nota < 8.5)
            {
                printf("B\n");
            }
            else{
                printf("A\n");
            }
            
        }
        
    }
}