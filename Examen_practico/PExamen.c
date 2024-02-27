#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#define K 1000

double microsegundos(){
    struct timeval t;
    if(gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla(){
    srand(time(NULL));
}

void aleatorio(int v[], int n){
    int i, m=2*n+1;
    for(i = 0; i < n; ++i)
        v[i] = (rand() % m) - n;
}

void intercambiar(int v[], int x1, int x2){
    int tmp = v[x1];
    v[x1] = v[x2];
    v[x2] = tmp;
}

void auxOrd (int v[], int izq, int der){
    int piv, i = 0, j = 0;
    if(izq < der){
        piv = v[izq + 1];
        intercambiar(v,izq, izq+1);
        i = izq + 1;
        j = der;
        while(i <= j){
            while(i <= der && v[i] < piv)
                i += 1;
            while(v[j] > piv)
                j -= 1;
            if(i <= j){
                intercambiar(v, i, j);
                i += 1;
                j -= 1;
            }
        }
        intercambiar(v, izq, j);
        auxOrd(v, izq, j-1);
        auxOrd(v, j+1, der);
    }
}

void ordenar(int v[], int n){
    auxOrd(v, 0, n-1);
}

void descendente(int v[], int n){
    int buff = n,i;
    for(i = 0; i < n; i++){
        v[i] = buff;
        buff--;
    }
}

void ascendente(int v[], int n){
    int buff = 1, i;
    for(i = 0; i < n; i++){
        v[i] = buff;
        buff++;
    }
}


void listar_vector(int v[], int n){
    int i;
    printf("[");
    for(i = 0; i < n; ++i){
        (printf("%4d", v[i]));
    }
    printf("]\n");
}

void warning(double t){
    if(t < 500)
        printf("(*)");
    else
        printf("%3s","");
}

double medicionTiempo(int n, int tipo) {
    int v[n];
    double t, ta, tb;
    double t1, t2;
    int i;

    if (tipo == 1) {aleatorio(v, n);}
    else if (tipo == 2) {descendente(v, n);}
    else {ascendente(v, n);}
    ta = microsegundos();
    ordenar(v, n);
    tb = microsegundos();
    t = tb - ta;

    if (t < 500) {
        ta = microsegundos();
        if (tipo == 1) {for (i = 1; i <= K; i++) {aleatorio(v, n);ordenar(v, n);}}
        else if (tipo == 2) {for (i = 1; i <= K; i++) {descendente(v, n);ordenar(v, n);}}
        else {for (i = 1; i <= K; i++) {ascendente(v, n);ordenar(v, n);}}
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        if (tipo == 1) {for (i = 1; i <= K; i++) {aleatorio(v, n);}}
        else if (tipo == 2) {for (i = 1; i <= K; i++) {descendente(v, n);}}
        else {for (i = 1; i <= K; i++) {ascendente(v, n);}}
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / K;
    }
    return t;
}

void validar(){
    int n = 15;
    int m=10;
    int v[n];
    char str[15] = "";
    strcpy(str, "metodo examen");
    printf("\nInicializacion aleatoria\n");
    aleatorio(v,n);
    listar_vector(v,n);
    printf("Ordenado? 0\n");

    printf("Ordenacion por %s\n", str);
    ordenar(v, n);
    listar_vector(v,n);
    printf("Ordenado? 1\n");

    printf("\nInicializacion descendente\n");
    descendente(v, m);
    listar_vector(v,m);
    printf("Ordenado? 0\n");

    printf("Ordenacion por %s\n", str);
    ordenar(v, m);
    listar_vector(v, m);
    printf("Ordenado? 1\n");

    printf("\nInicializacion ascendente\n");
    ascendente(v, m);
    listar_vector(v,m);
    printf("Ordenado? 0\n");

    printf("Ordenacion por %s\n", str);
    ordenar(v, m);
    listar_vector(v, m);
    printf("Ordenado? 1\n");

}

void printHeadline(float sub, float ajus, float sobre){

    printf("%15s%15s", "n", "t(n)");

    if (sub != 1.0) {
        if (sub == (int)sub) {
            printf("%14s%.0f", "t(n)/n^", sub);
        } else {
            printf("%11s%.2f", "t(n)/n^", sub);
        }
    } else {printf("%15s", "t(n)/n");}

    if (ajus != 1.0) {
        if (ajus == (int)ajus) {
            printf("%14s%.0f", "t(n)/n^", ajus);
        } else {
            printf("%11s%.2f", "t(n)/n^", ajus);
        }
    } else {printf("%15s", "t(n)/n");}

    if (sobre != 1.0) {
        if (sobre == (int)sobre) {
            printf("%14s%.0f", "t(n)/n^", sobre);
        } else {
            printf("%11s%.2f", "t(n)/n^", sobre);
        }
    } else {printf("%15s", "t(n)/n");}
    printf("\n");
}

void timetestSM(int tipo, float sub, float ajus, float sobre){
    char str[15] = "";
    double t;
    int n;

    strcpy(str, "metodo examen");

    if(tipo==1){printf("\nOrdenación por %s con inicialización aleatoria\n", str);}
    else if(tipo== 2){printf("\nOrdenación por %s con inicialización descendente\n", str);}
    else if(tipo==3){printf("\nOrdenación por %s con inicialización ascendente\n", str);}
    printHeadline(sub, ajus, sobre);

    for(n = 500; n <= 64000 ; n *= 2){
        t = medicionTiempo(n,tipo);
        warning(t);
        printf("%12d%15.3f%15.8f%15.8f%15.8f\n", n, t, t/pow(n, sub), t/pow(n, ajus), t/pow(n, sobre));
    }
}

int main(){
    int i;
    inicializar_semilla();
    validar();
    for(i=0;i<3;i++){
        timetestSM(1, 0.8, 1.09, 1.2);
        timetestSM(2, 1.8, 2, 2.2);
        timetestSM(3, 1.8, 1.98, 2.2);
    }
}
