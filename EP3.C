#include <stdio.h>
#include <stdlib.h>
int *leituraArq(char *nomeArq, int *w, int *h);
void salvarEmArq(char *nomeArq, int *I, int w, int h);
int *invertida(int *I, int w, int h);
int *binarizar(int *I, int w, int h, int t);
int *filtro(int *I, int w, int h, int d, int tipo);

int main (){
    char opcao;
    char nomeArq[256];
    int w, h, escolha = 0, valor = 0, valor2 =0;
    int *I;
    int *R;
    int *aux;

    

    //scanf("%s", nomeArq);

    //I = leituraArq(nomeArq, &w, &h);
    while(escolha == 0 ){

        printf("----------------------------------\n");
        printf("Escolha uma Opção\nQ. Quit\nL. Ler um arquivo \nS. Salvar imagem em arquivo\nM. Manter entrada anterior\n");
        printf("\nB. Binarizar a imagem\nC. Contorno da imagem\nI. Inverter a imagem\nF. Filtrar a imagem\nR. Rotular os componentes conexos\n");
        scanf(" %s", &opcao);
        if (opcao == 'L' || opcao == 'l'){
            printf("\nDigite o nome do arquivo de entrada: ");
            scanf("%s", nomeArq);
            I = NULL;
            I = leituraArq(nomeArq, &w, &h);
            printf("\nLido com sucesso!");
            printf("\nTamanho da imagem: %d x %d", w, h);
        }
        else if(opcao == 'Q'|| opcao == 'q'){
            escolha =1;
        }
        else if(opcao == 'S'|| opcao == 's'){
            printf("\nDigite o nome do novo arquivo: ");
            scanf("%s", nomeArq);
            salvarEmArq(nomeArq, I,  w,  h);
            printf("\nSalvo com sucesso em %s !", nomeArq);

        }
        else if(opcao == 'B'|| opcao == 'b'){ 
            printf("\nDigite o limiar: ");
            scanf("%d", &valor);
           
            R = binarizar(I, w, h, valor );
            printf("\nImagem binarizada!");

            aux = I;
            I = R;
            R = aux;

        }
        else if(opcao == 'm'|| opcao == 'M'){
            I = R;
            free(aux);
            free(R);
        }
        else if(opcao == 'I' || opcao == 'i'){

            R = invertida(I, w, h);
            printf("\nImagem invertida!");
            aux = I;
            I = R;
            R = aux;

        }
        else if(opcao == 'F'|| opcao == 'f'){
            printf("\nDigite o tipo do filtro: ");
            scanf("%d", &valor);
            printf("\nDigite o tamanho do filtro: ");
            scanf("%d", &valor2);
            R = filtro(I, w, h, valor2, valor);
            aux = I;
            I = R;
            R = aux;
        }else if(opcao == 'R'|| opcao == 'r'){
            escolha = 1;
        }
        else if(opcao == 'c'|| opcao == 'C'){
            R = filtro(I, w, h, 3, 1);
            for (int i = 0; i < w*h; i++)
            {
                R[i] = I[i] - R[i];
                
                aux = I;
                I = R;
                R = aux;
            }
            
        }
        
        printf("\n----------------------------------\n");

    }


}

int *leituraArq(char *nomeArq, int *w, int *h){
    FILE *arq;
    char miau[256];
    int *I;

    arq = fopen(nomeArq, "r");
    fscanf(arq, "%s", miau);
    fscanf(arq, "%d", w);
    fscanf(arq, "%d", h);
    fscanf(arq, "%s", miau);
    I = (int *)(malloc(*h * (*w) * sizeof(int)));
    

    for(int i = 0; i< (*w)*(*h); i++){
        fscanf(arq, "%d",  &I[i]);
    }

    fclose(arq);
    return I;
}

void salvarEmArq(char *nomeArq, int *I, int w, int h){
    
    FILE *arq;

    arq = fopen(nomeArq, "a");
    fprintf(arq, "P2 \n");
    fprintf(arq, "%d %d \n", w, h);
    fprintf(arq, "255\n");
    for(int j = 0; j<w*h; j++){
        fprintf(arq, "%d ", *(I+j));
        if((j+1)%w == 0){
            fprintf(arq, "\n");
        }
    }
    fclose(arq);

}

int *invertida(int *I, int w, int h){
    int *R;
    int i;
    
    R = (int *)malloc(w*h*(sizeof(int)));

    for(i = 0; i<w*h; i++){
        R[i] = 255 - *(I + i);
    }
    return R;
}

int *binarizar(int *I, int w, int h, int t){
    int *R;
    int i;
    R = (int *)malloc(w*h*(sizeof(int)));
    for (i = 0 ; i<w*h; i++){
        if(*(I+i)>=t){
            R[i] = 255;
        }
        else{
            R[i] = 0;
        }
    }
    return R;
}


int *filtro(int *I, int w, int h, int d, int tipo){
    int i, j, k,l, i1 = 0, erro = 0, aux = 0, cont = 0;
    int **Matrizao;
    int scan[w*h];
    int *R, *R2, *R3;
    int m = 0, n = 0, p=0;


    if(d%2 != 1){
        printf("Não foi possível realizar o filtro");
        erro = 1;
    }
    else{
        R = (int *)malloc((w + d-1)*(h)* sizeof(int ));
        R3 = (int *)malloc(w*h*(sizeof(int)));
        
        for( i = 0; i<(w + d-1) * h; i++){
            
            if(i<((d/2)*h)){
                //CIMA
                R[i] = *(I+(m%h));
                m ++;
            }
            else{
                if(i > (w + d/2)*h){
                    //BAIXO
                    R[i] = *(I+(m%h)+(w-1)*(h-1)+h);
                    m ++;
                }
                else{
                    //MEIO
                    R[i] = *(I+n);
                    n ++;
                }
            }
        }
        
        R2 = (int *)malloc((w + d-1)*(h + d-1)* sizeof(int));
        //ESQUERDA
        for( i = 0; i<=(h + d-1); i++){
            for( j = 0; j<=(d-1)/2; j++){
                R2[i*(h +d-1) +j ] = R[i*h];
            }
        }
        //DIREITA
        for( i = 0; i<=(h +d-1); i++){
            for( j = (w +d-1) - (d-1)/2; j<(w +d-1); j++){
                R2[i*(h +d-1) +j ] = R[i*h + w -1];
            }
        }
        //CENTRO
        for( i = ((d-1)/2)-1; i<(w + d-1)*(h + d-1); i++){

            if(i%(w +d -1) >= (d-1)/2 && i%(w+d-1)< w + (d-1)/2){
                R2[i] = R[i1];
                i1 ++;
            } 
        }
        free(R);
        R = NULL;
        Matrizao = (int **)malloc((w + d-1)*(h + d-1)*sizeof(int *));
        for( i = 0; i < (w+ d-1); i++){
            Matrizao[i] = (int*)malloc((h+d-1)*sizeof(int));
        }

        for( i = 0; i < (w+ d-1); i++){
            for( j = 0; j < (h+ d-1); j++){
            Matrizao[i][j] = R2[cont];
            cont++;
            }
        }
        free(R2);
        R2 = NULL;

        for(i = (d-1)/2; i< h+(d-1)/2; i++){
            for(j = (d-1)/2; j<w + (d-1)/2; j++){
                aux = 0;
                for(k = i-(d-1)/2; k<= i+(d-1)/2; k++){
                    for(l = j-(d-1)/2; l<=j+(d-1)/2; l++){
                        scan[aux] = Matrizao[k][l];
                        aux++;
                    }
                }

                cont = 0;

                for(k=0; k < d*d; k++){
                    for(l = 0; l < (d*d)-1; l++){
                        if(scan[l] > scan[l+1]){
                            cont = scan[l];
                            scan[l] = scan[l+1];
                            scan[l+1] = cont;
                        }
                    }

                    if(tipo == 1){
                    R3[p] = scan[0];
                    p++;
                }
                    else if(tipo == 2){
                    R3[p] = scan[((d*d)-1)/2];
                    p++;
                }
                    else if(tipo == 3){
                    R3[p] = scan[(d*d) - 1];
                    p++;
                }
                }
            }
        }
    }

    return R3;
}