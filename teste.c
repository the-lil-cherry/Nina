#include <stdio.h>
#define EPS 0.001

double raiz(double x, double epsilon){
    double r, f;
    r = x;
    f = 0.5*(r + x/r);
    while((r - f) > epsilon){
        r = f;
        f = 0.5*(r + x/r);
    }
    return r;
}

double velocidade(double x0, double y0, double x1, double y1, double tempo){
    double vm, d;
    d = (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0);
    d = raiz(d, EPS);
    vm = d/tempo;
    return vm;
}

int main(){
    double miau;
    miau = velocidade(0,0, 4,3,1);
    printf("%4.2f", miau);

}