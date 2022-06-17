#include<stdio.h>
// ta lento mas funciona :) 

int main(){
    double x, eps, e, n;
    int i = 2;
    scanf("%lf", &x);
    scanf("%lf", &eps);
    e = 1.0;
    n = x;
    while (n <= eps || -n <=  eps){
        e += n;
        n *=x/i;
        i ++;
    }
    printf("%lf\n", e);
}