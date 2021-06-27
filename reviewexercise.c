#include <stdio.h>

FILE *out;

void f(int *x, int y);

int main(void){

    out = fopen("output.txt", "w");

    int a[5], i, b=16;

    for(i=0;i<5;i++){
        a[i]=2*i;
    }
    f(a,b);
    for(i=0;i<5;i++){
        fprintf(out, "\n%d", a[i]);
    }
    fprintf(out, "\n%d", b);
}

void f(int *x, int y){
    int i;
    for(int i=0; i<5; i++){
        *(x+i)+=2;
        y+=2;
    }
}
