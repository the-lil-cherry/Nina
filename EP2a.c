#include <stdio.h>

#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 
#define DELTA_ALARME 60
#define EPS_COS 0.000001 
#define EPS 0.01 

//criando as funções

double cosseno(double theta, double epsilon){
    theta = (theta*PI)/180;
    double cosx = 1;
    double n;
    int f = 2;
    n = -1*(theta*theta)/f;

    while( n >= epsilon || -n >= epsilon ){
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

        pij = pij/(2*(xi - xj));
        qij = qij/(xi - xj);

        if(xi - xk != 0){
            pik = pik/(2*(xi - xk));
            qik = qik/(xi - xk);
            *yv = (pij - pik)/(qik - qij);
        }
        else{
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
            qjk = qjk/(xj - xk);
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
            }
        }
    }
    else{
        if(200 < x1 && x1 > -200 ){
            intercepta = 1;

        }
    }
    return intercepta;
}

double velocidade(double x0, double y0, double x1, double y1, double tempo){
    double vm, d;
    d = distancia(x0, y0, x1, y1);
    vm = d/tempo;
    return vm;
}


int main(){

    int qnt, i=0, j = 0, veiculo, n = 0;
    FILE *arq;
    double antenas[3][5];
    double tempo, tempointer;
    char filename[256];

    double div, djv, dkv, xvp, yvp, xva, yva;
    // xvp e yvp são coordenadas do veiculo na posição previa
    // xva e yva são coordenadas do veiculo na posição atual
    int existe;

    double vm;
    double xf, yf;

    int fora = 0;

    printf("\nPrograma-demo para o Sistema de Monitoramento\n \n \n");
    printf("Digite o nome do arquivo com os dados a serem processados\n");

    scanf("%s",filename);
    arq = fopen("entrada_exemplo2.txt", "r");
    if(arq == NULL){
        printf("Não foi possível abrir o arquivo");
    }
    fscanf(arq, "%d", &qnt);
    printf("Número de casos a serem analisados: %d\n\n", qnt);
    
    for(i = 0; i<qnt; i++){
        fora =0;
        fscanf(arq, "%d", &veiculo);

        printf("\nIDENTIFICAÇÃO: veículo %d\n\n", veiculo);
        printf("========================= Antenas na posição previa =========================\n\n");
         printf("   id    |        posição        |   H(m)   |  theta(graus)  | distância (m)\n");

        while(n < 3){
            for(j = 0; j <5; j++){
                fscanf(arq, "%lf", &antenas[n][j]);
            }
            dkv = antenas[n][3] * cosseno(antenas[n][4], EPS_COS);
            printf("%8.0f | ( %8.2f, %8.2f) | %8.2f |  %9.2f     | %8.2f ", antenas[n][0], antenas[n][1], antenas[n][2], antenas[n][3], antenas[n][4], dkv);

            n +=1;
            printf("\n");
        }
        printf("\n============================================================================\n\n");

        n = 0;

        djv = antenas[1][3] * cosseno(antenas[1][4], EPS_COS);
        div = antenas[0][3] * cosseno(antenas[0][4], EPS_COS);
        existe = localiza(antenas[0][1], antenas[0][2], div, antenas[1][1], antenas[1][2], djv, antenas[2][1], antenas[2][2], dkv, &xvp, &yvp);

        if(existe == 1){
            printf("\nLocalização prévia: (%5.2f, %5.2f)\n\n", xvp, yvp);
        
            fscanf(arq, "%lf", &tempo);
            printf("Intervalo de tempo: %.2f segundos\n\n", tempo);

            printf("========================= Antenas na posição atual =========================\n\n");
            printf("   id    |        posição        |   H(m)   |  theta(graus)  | distância (m)\n");
            while(n <3){
                for(j = 0; j <5; j++){
                    fscanf(arq, "%lf", &antenas[n][j]);
                }
                dkv = antenas[n][3] * cosseno(antenas[n][4], EPS_COS);
                printf("%8.0f | ( %8.2f, %8.2f) | %8.2f |  %9.2f     | %8.2f \n", antenas[n][0], antenas[n][1], antenas[n][2], antenas[n][3], antenas[n][4], dkv );

                n +=1;
            }
            printf("\n============================================================================\n\n");

            n = 0;

            djv = antenas[1][3] * cosseno(antenas[1][4], EPS_COS);
            div = antenas[0][3] * cosseno(antenas[0][4], EPS_COS);
            existe = localiza(antenas[0][1], antenas[0][2], div, antenas[1][1], antenas[1][2], djv, antenas[2][1], antenas[2][2], dkv, &xva, &yva);
            if(existe ==1){
                printf("\nLocalização atual: ( %8.2f, %8.2f ) \n\n", xva, yva);

                printf("Distância percorrida: %.2fm\n", distancia(xvp, yvp, xva,yva));

                vm = velocidade(xvp, yvp, xva, yva, tempo);
                printf("Velocidade: %.f m/s\n\n", vm);

                printf("Distância da origem: %.2fm \n", distancia(0, 0, xva,yva));

                if(vm > EPS){
                    printf("Veículo em movimento");
                    if(distancia(0,0, xva, yva) < 200 && distancia(0,0, xva, yva) > -200 ) {
                        printf(" na AP\n");
                        printf("\n*************************************\n  ALARME, ALARME, ALARME, ALARME !!\n        Veículo está na AP!\n*************************************\n\n\n\n");
                    }
                    else{
                        if(distancia(0,0,xva, yva) <2000 && distancia(0,0,xva, yva) > -2000 ){
                            printf(" na ZONA DE ALERTA\n");
                            if(intercepta(xvp, yvp, xva, yva, &xf, &yf) == 1){
                                if(distancia(xvp, yvp, xf, yf) > distancia(xva, yva, xf, yf) && distancia(xvp, yvp, xf, yf) > distancia(xvp, yvp, xva, yva)){
                                    tempointer = (distancia(xva, yva, xf, yf))/vm;
                                    if(tempointer > 0 && fora == 0 ){
                                        printf("\nTrajetoria interceptará AP\n");
                                        printf("A distância do ponto atual até AP é de %.2fm\n",distancia(xva, yva, xf,yf));
                                        printf("A intersecção ocorrerá em %.2f segundos nas coordenadas (%8.2f, %8.2f)\n", tempointer, xf, yf);
                                        if(tempointer <60){
                                            printf("\n*************************************\n  ALARME, ALARME, ALARME, ALARME !!\n        Invasão iminente!\n*************************************\n\n\n\n"); 
                                        }
                                    }
                                }
                                else{
                                    printf("Trajetória não interceptara AP\n\n\n\n");
                                }
                            }
                            else{
                                printf("Trajetória não interceptara AP\n\n\n\n");
                            }
                        }
                        else{
                            printf(" FORA da zona de alerta\n\n\n\n");
                            fora = 1;
                        }
                    }
                }
                else{
                    printf("Veiculo estacionado");
                    if(distancia(0,0, xva, yva) < 200 && distancia(0,0, xva, yva) > -200 ) {
                        printf(" na AP\n");
                        printf("\n*************************************\n  ALARME, ALARME, ALARME, ALARME !!\n        Veículo está na AP!\n*************************************\n\n\n\n");
                    }
                    else{
                        if(distancia(0,0,xva, yva) <2000 && distancia(0,0,xva, yva) > -2000){
                            printf(" na ZONA DE ALERTA\n\n\n\n");
                        }
                        else{
                            printf(" FORA da zona de alerta\n\n\n\n");
                        }
                    }
                }
            }
            else{
                printf("\nNão foi possível calcular a localização atual do veículo %d.\n", veiculo);
                printf("Não foi possível determinar a situação do veículo %d.\n\n\n\n", veiculo);
            }
        }
        else{
            fscanf(arq, "%lf", &tempo);
            while(n <3){
                for(j = 0; j <5; j++){
                    fscanf(arq, "%lf", &antenas[n][j]);
                }
            n +=1;
            }
            printf("\nNão foi possível calcular a localização inicial do veículo %d.\n", veiculo);
            printf("Não foi possível determinar a situação do veículo %d.\n\n\n\n", veiculo);
        }
        n = 0;
    }
    fclose(arq);
}