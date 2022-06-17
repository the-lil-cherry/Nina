#include <stdio.h>

int contadigitos(int n, int d){
    int acu = 0;
    
    while(n!=0){
        if(n%10 == d){
           acu ++;
        }
        n = n/10;
    }
    return acu;
}

int main(){
    int a, b, permutacao = 1;
    scanf("%d", &a);
    scanf("%d", &b);

    for(int i = 1; i<=9; i++){
        if (contadigitos(a, i) != contadigitos(b, i)){
           permutacao = 0;
        }
    }
    if (permutacao == 0)
    {
        printf("A não é permutação de B\n");
    }
    else{
        printf("A é permutação de B\n");
    }
 
}