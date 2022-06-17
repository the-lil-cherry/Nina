#include <stdio.h>

int main (){
    int n = 1;
    double d = 1.89;
    char c = 'a';
    int *miau;
    double *num;
    char *ch;
    printf("%d\n", n);
    printf("%d\n", *miau);
    printf("%f\n", d);
    printf("%f\n", *num);
    printf("%c\n", c);
    printf("%c\n", *ch);

    //miau = &n;
    *miau = n;
    num = &d;
    ch = &c;

    *miau = 2;

    printf("\nmudança: \n");
    printf("%d\n", n);
    printf("%d\n", *miau);
    printf("%f\n", d);
    printf("%f\n", *num);
    printf("%c\n", c);
    printf("%c\n", *ch);

}