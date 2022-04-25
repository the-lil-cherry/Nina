#include <stdio.h>
int main(){
    int n,a, mdc;
    scanf("%d", &n);
    scanf("%d", &a);
    for(int i = 1; i<n; i++){
        mdc = 1;
        int b,x;
        scanf("%d", &b);
        for (int j = 2; j <= a; j++){
            while(a%j == 0 && b%j == 0){
                a = a/j;
                b = b/j;
                mdc *=j;
            }
        }
        a = mdc;    
    }
    printf("%d\n", mdc);

}