#include <stdio.h>

int main(){
    int n, seq, maior;
     scanf("%d", &n);
     maior = 0;

     while (n>0){
         scanf("%d", &seq);
         if(seq>maior){
             maior = seq;
         }
         n=n-1;
     }
     printf("o número é %d", maior);
}