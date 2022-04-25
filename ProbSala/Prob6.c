#include <stdio.h>
int main(){
    int n, soma;
    soma = 0;
    printf("Digite um número: ");
    scanf("%d", &n);
    while (n!=0){

        soma += n;
        printf("Digite um número: ");
        scanf("%d", &n);
    }
    printf("A soma da sequencia é: %d \n", soma);
}