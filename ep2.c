#include <stdio.h>
#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 /* zona de alerta */
#define DELTA_ALARME 60
#define EPS_COS 0.000001 /* precisao para calculo do cosseno */
#define EPS 0.01 /* precisao para valores envolvendo metros */


double dist(double H, double cos);
double cosseno(double theta, double epsilon);
int localiza (double xi, double yi, double div, 
			  double xj, double yj, double djv, 
			  double xk, double yk, double dkv, 
			  double *xv, double *yv);
int iguais(double x, double y);
double raiz(double x, double epsilon);
double velocidade(double x0, double y0, double x1, double y1, double deltaT);
double S(double x0, double y0, double x1, double y1);
int intercepta(double x0, double y0, double x1, double y1, double *x, double*y);


int main(){
	FILE *input;
	char filename[256];
	int n, v, ant, i, colinear1, colinear2, alarme = 0;
	double x, y, h, theta, deltaT, cosx, xv, yv, spd, spc, xi, yi, delta_inter, dora, dord;
	int Ant[6];
	double X[6], Y[6], H[6], Theta[6], dav[6], Local[4];
	colinear1 = 0;
	colinear2 = 0;
	printf("Programa-demo para o Sistema de Monitoramento\n\n\n\n\n");
	printf("Digite o nome do arquivo: \n");
	scanf("%s", filename);
	input = fopen(filename, "r");
	if(input == NULL){
		printf("Nao foi possivel abrir o arquivo");
		return 0;
	}	
	fscanf(input, "%d", &n);
	printf("Numero de casos a serem analisados: %d\n\n\n", n);
	while(n>0){
		/*Leitura dados*/
		fscanf (input, "%d", &v);
		for(i = 0; i < 3; i++){	
			fscanf(input, "%d", &ant);
			fscanf(input, "%lf %lf %lf %lf", &x, &y, &h, &theta);
			Ant[i] = ant;
			X[i] = x;
			Y[i] = y;
			H[i] = h;
			Theta[i] = theta;
			cosx = cosseno(theta, EPS_COS);
			dav[i] = dist(H[i], cosx);

		}
		fscanf(input, "%lf", &deltaT);
		for(i = 3; i < 6; i++){
			fscanf(input, "%d", &ant);		
			fscanf(input, "%lf %lf %lf %lf", &x, &y, &h, &theta);
			Ant[i] = ant;
			X[i] = x;
			Y[i] = y;
			H[i] = h;
			Theta[i] = theta;
			cosx = cosseno(theta, EPS_COS);
			dav[i] = dist(H[i], cosx);
		}
		
		/*Localizacoes*/
		if(localiza(X[0], Y[0], dav[0], 
				    X[1], Y[1], dav[1],
				    X[2], Y[2], dav[2],
				    &xv, &yv)){;
			Local[0] = xv;
			Local[1] = yv;
			colinear1 = 0;
		}
		else{
			colinear1 = 1;
		}
		if(localiza(X[3], Y[3], dav[3],
				    X[4], Y[4], dav[4],
				    X[5], Y[5], dav[5],
				    &xv, &yv)){;
		Local[2] = xv;
		Local[3] = yv;
		colinear2 = 0;
		}
		else{
			colinear2 = 1;
		}

		/*Espaco percorrido*/
		spc = S(Local[0], Local[1], Local[2], Local[3]);
		
		/*Velocidade*/
		spd = velocidade(Local[0], Local[1], Local[2], Local[3], deltaT);

		/*Distancia da origem*/
		dora = S(Local[0], Local[1], 0, 0);
		dord = S(Local[2], Local[3], 0, 0);

		
		/*Impressao de dados*/
		printf ("\n\nIDENTIFICACAO: veiculo %d\n\n", v);
		printf("Antenas na posicao previa\n");
		printf(" id |       posicao       |   H(m)  | theta(graus) | distancia (m)\n");
		for(i = 0; i < 3; i++){
			printf(" %.2d |", Ant[i]);			
			printf("(%8.2lf, %8.2lf) |%8.2lf |  %8.2lf    | %8.2lf\n", X[i], Y[i], H[i], Theta[i], dav[i]);
		}
		if(colinear1 == 1){
			printf("\nNao foi possivel calcular a localizacao inicial do veiculo %d\n\n", v);
			printf("Nao foi possivel calcular a situacao do veiculo %d\n\n", v);
		}
		else{
			printf("\nLocalizacao Previa: (%.2lf, %.2lf)\n", Local[0], Local[1]);
			printf("\nIntervalo de Tempo: %.2lf segundos\n\n", deltaT);
			printf("Antenas na posicao atual\n");
			printf(" id |       posicao        |   H(m)  | theta(graus) | distancia (m)\n");
			for(i = 3; i < 6; i++){
				printf(" %.2d | ", Ant[i]);
				printf("(%8.2lf, %8.2lf) |%8.2lf |  %8.2lf    | %8.2lf\n", X[i], Y[i], H[i], Theta[i], dav[i]);
			}
			if(colinear2 == 1){
				printf("Nao foi possivel calcular a localizacao atual do veiculo %d\n\n", v);
				printf("Nao foi possivel calcular a situacao do veiculo %d\n\n", v);
			}
			else{
				printf("\nLocalizacao Atual: (%.2lf , %.2lf)\n\n", Local[2], Local[3]);
				printf("Distancia percorrida: %.2lf m\n", spc);
				printf("Velocidade: %.2lf m/s\n\n", spd);
				printf("Distancia da origem: %.2lf m\n", dord);
				if(spd!=0){
					printf("Veiculo em movimento ");
				}
				else{
					printf("Veiculo estacionado ");
				}
				if (dord <= RAIO_ZA && dord > RAIO_AP){
					printf("na ZONA DE ALERTA\n\n");
					if((intercepta(Local[0], Local[1], Local[2], Local[3], &xi, &yi))&&(dord < dora)){	
						printf("\nTrajetoria INTERCEPTARA AP\n");
						spc = S(Local[2], Local[3], xi, yi);
						delta_inter = spc/spd;
						if (delta_inter <= DELTA_ALARME){
							alarme = 2;
						}
						printf("Distancia atual a AP e de %.2lf metros\n", spc);
						printf("Interseccao ocorrera em %.2lf segundos, ", delta_inter);
						printf("na coordenada (%.2lf, %.2lf)\n\n\n", xi, yi);
						
					}
					else if (spd != 0){
						printf("Trajetoria NAO INTERCEPTARA AP\n\n\n");
					}
				}
				if(dord <= RAIO_AP){
					printf("na AP\n\n");
					alarme = 1;
				}
				if(dord > RAIO_ZA){
					printf("FORA da zona de alerta\n\n");
				}
				if(alarme == 1){
					printf("*************************************\n");
					printf("  ALARME, ALARME, ALARME, ALARME !!\n");
					printf("       Veiculo esta na AP !\n" );
					printf("*************************************\n\n\n\n");
				}
				else if(alarme == 2){
					printf("*************************************\n");
					printf("  ALARME, ALARME, ALARME, ALARME !!\n");
					printf("       Invasao iminente !\n" );
					printf("*************************************\n\n\n\n");	
				}
				alarme = 0;
			}
		}
		n--;
	}
	fclose(input);
	return 0;
}				
		

/*Funcao distancia antena-veiculo*/
double dist(double H, double cos){
	double dav;
	dav = H*cos;
	return dav;
}


/*Funcao cosseno*/
double cosseno(double theta, double epsilon){
	double cosx, termo, n, x;
	x = (theta*PI)/180;
	cosx = 1;
	termo = 1;
	for(n = 0; termo > epsilon; n+=4){
		termo = termo*x*x/((n+1)*(n+2));
		cosx = cosx - termo;
		termo = termo*x*x/((n+3)*(n+4));
		cosx = cosx + termo;
	}
	return cosx;
}


/*Funcao Localizacao do Veiculo*/
int localiza (double xi, double yi, double div, 
			  double xj, double yj, double djv, 
			  double xk, double yk, double dkv, 
			  double *xv, double *yv){	
	double x, y, d;
	if(iguais(xi, xj)){
		x = xi;
		y = yi;
		d = div;
		xi = xk;
		yi = yk;
		div = dkv;
		xk = x;
		yk = y;
		dkv = d;
	}
	if(iguais(xi, xk)){
		xi = xj;
		xj = xk;
	}
	if((xi != xj)&&(xi != xk)){
		double pij, pik, qij, qik;
		pij = (xi*xi - xj*xj + yi*yi - yj*yj - div*div + djv*djv)/(2*(xi - xj));
		pik = (xi*xi - xk*xk + yi*yi - yk*yk - div*div + dkv*dkv)/(2*(xi - xk));
		qij = (yj - yi)/(xi - xj);
		qik = (yk - yi)/(xi - xk);
		*yv = (pik - pij)/(qij - qik);
		*xv = pij + qij**yv;
		return 1;
	}
	else{
		return 0;
	}
}

/*Compara Reais*/
int iguais(double x, double y) {
	if(x-y < EPS && y-x < EPS)
	return 1;
	else{
	return 0;
	}	
}

/*Calculo Raiz*/
double raiz(double x, double epsilon){
	double r1, r2;
	r1 = (x+1)/2;
	r2 = (r1 + (x/r1))/2;
	while((r1 - r2 > epsilon)||(r2 - r1 > epsilon)){
		r1 = r2;
		r2 = (r2 + (x/r2))/2;
	}
	if (r2 == 0){
		return 0;
	}
	else{
		return r2;	
	}
}


/*Calculo espaco percorrido*/
double S(double x0, double y0, double x1, double y1){
	double spc, x;
	x = (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0);
	if (x == 0){
		spc = 0;
	}
	else{
		spc = raiz(x, EPS);
	}
	return spc;
}



/*Calculo Velocidade Media*/
double velocidade(double x0, double y0, double x1, double y1, double deltaT){
	double spd;
	if(x0 == x1 && y0 == y1){
		spd = 0;
	}
	else{
		spd = (S(x0, y0, x1, y1))/deltaT;
	}
	return spd;
}

/*Intercepta?*/
int intercepta(double x0, double y0, double x1, double y1, double *x, double*y){
	double m, c, delta, xa, ya, xb, yb, da, db;
	m = (y1-y0)/(x1 - x0);
	c = y0 - m*x0;
	delta = 4*m*m*c*c - 4*(1 + m*m)*(c*c - 40000);
	if (delta > 0){
		xa = (-2*m*c + raiz(delta, EPS))/(2*(1 + m*m));
		xb = (-2*m*c - raiz(delta, EPS))/(2*(1 + m*m));
		ya = m*xa + c;
		yb = m*xb + c;
		da = S(x1, y1, xa, ya);
		db = S(x1, y1, xb, yb);
		if(da < db){
			*x = xa;
			*y = ya;
		}
		else{
			*x = xb;
			*y = yb;
		}
		return 1;
	}
	else{
		return 0;
	}
}