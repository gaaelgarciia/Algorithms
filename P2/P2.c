/*
Miguel Marcos Trillo    miguel.marcos.trillo@udc.es
Gael Garcia Arias   gael.garciaa@udc.es
Brais Bello Pardo   brais.bello.pardo@udc.es
 */

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

void ord_ins (int v[], int n){
    int x = 0;
    int j = 0, i = 0;
    for(i = 1; i < n; i++){
        x = v[i];
        j = i -1;
        while(j >= 0 && v[j] > x){
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = x;
    }
}

void ord_shell(int v[], int n){
    int incremento = n - 1;
    int tmp = 0;
    int j = 0, i = 0;
    bool seguir = true;
    do{
        incremento = incremento/2;
        for(i = incremento; i < n; i++){
            tmp = v[i];
            j = i;
            seguir = true;
            while((j - incremento) >= 0 && seguir){
                if(tmp < v[j - incremento]){
                    v[j] = v[j - incremento];
                    j = j - incremento;
                }
                else{
                    seguir = false;
                }
            }
            v[j] = tmp;
        }
    }while(incremento != 1);
}

void descendente(int v[], int n){
    int buff = n,i = 0;
    for(i = 0; i < n; i++){
        v[i] = buff;
        buff--;
    }
}

void ascendente(int v[], int n){
    int buff = 0, i = 0;
    for(i = 0; i < n; i++){
        v[i] = buff;
        buff++;
    }
}


void listar_vector(int v[], int n){
	int i = 0;
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

double medicionTiempo(int n, int tipo,int ord) {
    int v[n];
    double t, ta, tb;
    double t1, t2;
    int i;

    if (tipo == 1) {aleatorio(v, n);}
    else if (tipo == 2) {descendente(v, n);}
    else {ascendente(v, n);}
    ta = microsegundos();
    if(ord==1){ord_ins(v, n);}
    else{ord_shell(v,n);}
    tb = microsegundos();
    t = tb - ta;

    if (t < 500) {
        ta = microsegundos();
        for (i = 1; i <= K; i++) {
            if (tipo == 1) {aleatorio(v, n);}
            else if (tipo == 2) {descendente(v, n);}
            else {ascendente(v, n);}
            if(ord==1){ord_ins(v, n);}
            else{ord_shell(v,n);}
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 1; i <= K; i++) {
            if (tipo == 1) {aleatorio(v, n);}
            else if (tipo == 2) {descendente(v, n);}
            else {ascendente(v, n);}
        }
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / K;
    }
    return t;
}

void validar(int x){
    int n = 17, m = 10;
    int v[n];
    char str[15] = "";
    x == 1? strcpy(str, "Insercion") : strcpy(str, "Shell");
    printf("Inicializacion aleatroria\n");
    aleatorio(v,n);
    listar_vector(v,n);
    printf("Ordenado? 0\n");

    printf("Ordenacion por %s\n", str);
    x == 1? ord_ins(v,n) : ord_shell(v,n);
    listar_vector(v,n);
    printf("Ordenado? 1\n");

    printf("\nInicializacion descendente\n");
    descendente(v,m);
    listar_vector(v,m);
    printf("Ordenado? 0\n");

    printf("Ordenacion por %s\n", str);
    x == 1? ord_ins(v,m) : ord_shell(v,m);
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

void timetestSM(int tipo,int ord, float sub, float ajus, float sobre){
    char str[15] = "";
    double t;
    int n;

    ord == 1? strcpy(str, "inserción") : strcpy(str, "shell");

    if(tipo==1){printf("\nOrdenación por %s con inicialización aleatoria\n", str);}
    else if(tipo== 2){printf("\nOrdenación por %s con inicialización descendente\n", str);}
    else if(tipo==3){printf("\nOrdenación por %s con inicialización ascendente\n", str);}
    printHeadline(sub, ajus, sobre);

    for(n = 500; n <= 32000 ; n *= 2){
        t = medicionTiempo(n,tipo,ord);
        warning(t);
        printf("%12d%15.3f%15.8f%15.8f%15.8f\n", n, t, t/pow(n, sub), t/pow(n, ajus), t/pow(n, sobre));
    }
}

 int main(){
    int i;
    inicializar_semilla();
    validar(1);
    validar(2);
    for(i=0;i<3;i++){
    timetestSM(1,1, 1.8, 2, 2.2);
    timetestSM(2,1, 1.8, 2, 2.2);
    timetestSM(3,1, 0.8, 1, 1.2);
    timetestSM(1,2, 1, 1.15, 1.3);
    timetestSM(2,2, 1, 1.15, 1.3);
    timetestSM(3,2, 0.8, 1.12, 1.2);}
 }
