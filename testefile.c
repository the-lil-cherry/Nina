#include <stdio.h>

int main(){
    int qnt, i=0, veiculo, n = 0;
    FILE *arq;
    double antenas[3][5];
    double tempo;
    arq = fopen("entrada_exemplo1.txt", "r");
    fscanf(arq, "%d", &qnt);
    

    for(i = 0; i<qnt; i++){
        fscanf(arq, "%d", &veiculo);

        printf("\nveículo: %d\n", veiculo);
        while(n <3){
            for(int j = 0; j <5; j++){
            fscanf(arq, "%lf", &antenas[n][j]);
            printf("%.2f\n", antenas[n][j]);
        }
            n +=1;
            printf("\n");
        }
        
        n = 0;
        fscanf(arq, "%lf", &tempo);
        
        printf("\n2pt\n \n");
        while(n <3){
            for(int j = 0; j <5; j++){
            fscanf(arq, "%lf", &antenas[n][j]);
            printf("%.2f\n", antenas[n][j]);
        }
        printf("\n");
            n +=1;
        }
        n = 0;

        
    }

    fclose(arq);


}