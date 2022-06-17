#include <stdio.h>

void miau (int n, int *qnt, int *pri){
    *pri = 0;
    *qnt = 0;
   
    while(n>0){
        *pri = n; 
        n = n/10;
        *qnt +=1;
       
    }

}

int main(){
    int n, s;
    int qnt = 0, pri = 0;
    scanf("%d", &n);
    for (int i = 0; i<n; i++){
        scanf("%d", &s);
        miau(s, &qnt, &pri);
        printf("%d\n", qnt);
        printf("%d\n", pri);
    }
    
}