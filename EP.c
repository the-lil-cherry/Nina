#include <stdio.h>
#include <stdlib.h>

int main(){
    int opcao, num;
    int dep = 0,  jogos = 0, ganhou = 0;
    printf("\n=================================================\n"
        "[ depuração = DESLIGADO / jogos jogados = %d]\n"
        "1. Continuar a jogar\n"
        "2. Alternar modeo depuração e continuar a jogar\n"
        "3. Parar \n"
        "Escolha uma opção: ", jogos);

    scanf("%d", &opcao);
    printf("=================================================\n");
    
    while(opcao!=3){

        int centena = 0, dezena = 0, unidade = 0;
        int tentativas = 6;
        int chute;
        num = rand()%1000;
        int cen, dez, uni;
        cen = num/100;
        dez = (num%100)/10;
        uni = (num%100)%10;
    

        if(opcao == 2){
            if(dep == 0){
                dep = 1;
            }
            else{
                dep = 0;
            }
        }
        if (dep == 1){
            printf("Número a ser adivinhado: %d \n", num);
        }

       while(tentativas > 0){
            
            printf("Restam %d tentativas\n", tentativas);
            printf("Sua próxima tentativa (dígito de 0 a 9): \n");
            scanf("%d", &chute);
            tentativas -=1;

            if(cen == chute){
                centena = 1;
            }
            if (dez == chute){
                dezena = 1;
            }

            if(uni == chute){
                unidade = 1;
            }

            if(centena != 1){
                printf("Você ja acertou os seguintes dígitos: _");
                if(dezena != 1){
                    printf(" _ ");
                    if(unidade != 1){
                        printf("_ \n");
                    }
                    else{
                        printf("%d \n", uni);
                    }
                }
                else{
                    printf(" %d ", dez);
                    if(unidade != 1){
                        printf("_ \n");
                    }
                    else{
                        printf("%d \n", uni);
                    }
                }

            }
            else{
                printf("Você ja acertou os seguintes dígitos: %d", cen);
                if(dezena != 1){
                    printf(" _ ");
                    if(unidade != 1){
                        printf("_ \n");
                    }
                    else{
                        printf("%d \n", uni);
                    }
                }
                else{
                    printf(" %d ", dez);
                    if(unidade != 1){
                        printf("_ \n");
                    }
                    else{
                        printf("%d \n", uni);
                    }
                }
            }
            
            if(centena == 1 && dezena == 1 && unidade == 1){
                tentativas = 0;
                printf("Você GANHOU!!! :)) \n");
                ganhou +=1;
            }
       }
       if(centena == 0 || dezena == 0 || unidade == 0){
            printf("Você PERDEU!! :(( \n");
       }
       
       jogos +=1;

       printf("\n=================================================\n");
       if (dep == 1){
           printf( "[ depuração = LIGADO / jogos jogados = %d]\n", jogos);
       }
       else{
           printf( "[ depuração = DESLIGADO / jogos jogados = %d]\n", jogos);
       }
       printf("1. Continuar a jogar\n"
        "2. Alternar modeo depuração e continuar a jogar\n"
        "3. Parar \n"
        "Escolha uma opção: ");
        scanf("%d", &opcao);
        printf("=================================================\n");
       
    }
    printf("Você jogou %d e venceu %d vezes!", jogos, ganhou);
}
    
   
