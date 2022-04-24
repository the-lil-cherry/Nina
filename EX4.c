#include <stdio.h>
int main(){
    int n, x, cont, m, eh_palin;
    scanf("%d", &n);
    x = 1;
    cont = 0;
    m = n;
    eh_palin = 0;
    
    while(n >= x){
        cont +=1;
        x *=10;
    }

    for(int i = 0; i< cont; i++){
        x /=10;
        int a, b;
        a = n/x;
        n = n%x;
        b = m%10;
        m = m/10;

        if(a != b){
            eh_palin = 1;
        }
    }

    if(eh_palin != 0){
        printf("Não é Palíndromo\n");
    }
    else{
        printf("É Palíndromo\n");
    }
}