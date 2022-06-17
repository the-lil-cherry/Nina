#include <stdio.h>

#define EPS_COS 0.000001
#define EPS 0.01 
#define PI 3.14159

double cosseno(double theta, double epsilon){
    theta = (theta*PI)/180;
    double cosx = 1;
    double n;
    int f = 2;
    n = -1*(theta*theta)/f;

   while( n >= epsilon|| -n >= epsilon ){
        cosx +=n;
        f +=1;
        n *=theta/f;
        f +=1;
        n *=(-1)*theta/f;
    }
    return cosx;
}

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

int localiza(double xi, double yi, double div,double xj, double yj, double djv,
double xk, double yk, double dkv,
double *xv, double *yv){
    double pij, qij, pik, qik, pjk, qjk;
    int existe = 1;


	pik = (xi*xi - xk*xk + yi*yi - yk*yk - div*div + dkv*dkv);
	qik = yk - yi;
	
	pij = (xi*xi - xj*xj + yi*yi - yj*yj - div*div + djv*djv);
	qij = yj - yi;
	
	pjk = (xj*xj - xk*xk + yj*yj - yk*yk - djv*djv + dkv*dkv);
	qjk = yk - yj;
	
    if(xi - xj !=0){

        //ok 
        pij = pij/(2*(xi - xj));
        qij = qij/(xi - xj);

        if(xi - xk != 0){
            //ok
            pik = pik/(2*(xi - xk));
            qik = qik/(xi - xk);

            *yv = (pij - pik)/(qik - qij);

        }
        else{
            //ok
            pjk = pjk/(2*(xj - xk));
            qjk = qik/(xj - xk);

            *yv = (pij - pjk)/(qjk - qij);

        }
    }
    else{
    
        if(xi - xk !=0 && xj - xk != 0){
            
            pik = pik/(2*(xi - xk));
            qik = qik/(xi - xk);

            pjk = pjk/(2*(xj - xk));
            qjk = qik/(xj - xk);

            *yv = (pik - pjk)/(qjk - qik);

        }
        else{
            existe = 0;
        }
            
    }

    if(existe > 0){
        if(pij + qij*(*yv) == pik + qik*(*yv) || pij + qij*(*yv) == pjk +qjk*(*yv)){
            *xv = pij + qij*(*yv);
        }
        else{
            *xv = pik + qik*(*yv);
        }
    }
    return existe;
}

double distancia(double x0, double y0, double x1, double y1){
    double d;
    d = (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0);
    d = raiz(d, EPS);
    return d;
}

double velocidade(double x0, double y0, double x1, double y1, double tempo){
    double vm, d;
    d = (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0);
    d = raiz(d, EPS) ;
    vm = d/tempo;
    return vm;
    
}

int intercepta (double x0, double y0, double x1, double y1, double *x, double *y){
    double m, b, delta, r = 200.00, vm, x2;
    int intercepta = 0;
    if(x1 - x0 != 0){
        //adotando a equação y = ax + b, m = a
        m = (y1 - y0)/(x1 -x0);
        b = y1 - m*x1;
        delta = (2*b*m)*(2*b*m) - 4*(1 + m*m)*(b*b - r*r);
        if(delta >0){
            intercepta = 1;
            *x = (-(2*b*m) + raiz(delta, EPS))/(2*(1+m*m));
            *y = m*(*x) + b;
            x2 = (-(2*b*m) - raiz(delta, EPS))/(2*(1+m*m));
            
            if(distancia(x1, y1, *x, *y) > distancia(x1, y1, x2 ,  m*(x2) + b) && distancia(x0, y0,x1, y1) > 200){
                *x =  (-(2*b*m) - raiz(delta, EPS))/(2*(1+m*m));
                *y = m*(*x) + b;
                printf("x = %f y = %f", *x, *y);
            }
        }
    }
    else{
        if(200 < x1 && x1 < 200 ){
            intercepta = 1;

        }
    }
    return intercepta;
}

int main(){
    double xv, yv;


    intercepta(-200.00,  600.00,  -100.00,  300.00, &xv, &yv);
    printf("x: %f y: %f\n", xv, yv);
    


}

