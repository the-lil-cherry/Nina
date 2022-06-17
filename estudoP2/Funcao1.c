#include <stdio.h>

int encaixa (int a, int b){
    int n = 1, resp = 0;
    while ((a%n) <= b && a > b){
        n *=10; 
        if(a%n == b){
            resp = 1;
        }
    }
    if(a == b){
            resp = 1;
        }
    return resp;
}

int main(){
    int a, b, c=0;
    scanf("%d %d", &a, &b);
    if (a < b ){
        c = a;
        a = b;
        b = c;
        c = 1;
    }
    
    while (encaixa(a,b) == 0 && a>b){
        a = a/10; 
    }

    if(encaixa(a,b) == 1){
        if (c == 0)
        {
            printf("b é um segmento de a\n");
        }
        else
        {
            printf("a é um segmento de b\n");
        }
        
    }
    else{
        printf("um não é segmento do outro\n");
    }
   

}