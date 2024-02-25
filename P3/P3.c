/*
 * Miguel Marcos Trillo   miguel.marcos.trillo@udc.es
 * Gael Garcia Arias  	gael.garciaa@udc.es
 * Brais Bello Pardo  	brais.bello.pardo@udc.es
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#define K 1000
#define TAM 256000

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

void aleatorio(int v[], int n){
    int i, m=2*n+1;
    for(i = 0; i < n; ++i)
        v[i] = (rand() % m) - n;
}

void printHeadline(float sub, float ajus, float sobre, int ord){
    char str1[18] = "";
    char str2[18] = "";
    strcpy(str1, "t(n)/(n*log(n))^");
    strcpy(str2, "t(n)/n^");

    printf("%15s%15s", "n", "t(n)");


    if (sub != 1.0) {
        if (sub == (int)sub) {
            printf("%25s%.0f", ord==1? str1 : str2, sub);
        } else {
            printf("%22s%.2f", ord==1? str1 : str2, sub);
        }
    } else {printf("%26s", ord==1? "t(n)/(n*log(n))" : "t(n)/n");}

    if (ajus != 1.0) {
        if (ajus == (int)ajus) {
            printf("%25s%.0f", ord==1? str1 : str2, ajus);
        } else {
            printf("%22s%.2f", ord==1? str1 : str2, ajus);
        }
    } else {printf("%26s", ord==1? "t(n)/(n*log(n))" : "t(n)/n");}

    if (sobre != 1.0) {
        if (sobre == (int)sobre) {
            printf("%25s%.0f", ord==1? str1 : str2, sobre);
        } else {
            printf("%22s%.2f", ord==1? str1 : str2, sobre);
        }
    } else {printf("%26s", ord==1? "t(n)/(n*log(n))" : "t(n)/n");}
    printf("\n");
}


double microsegundos(){
    struct timeval t;
    if(gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla(){
    srand(time(NULL));
}

void warning(double t){
    if(t < 500)
        printf("(*)");
    else
        printf("%3s","");
}



void listar_vector(int v[], int n){
    int i = 0;
    printf("[");
    for(i = 0; i < n; ++i){
        (printf("%4d", v[i]));
    }
    printf("]\n");
}

struct monticulo{
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo * pmonticulo;

int Size(pmonticulo m){
    return m->ultimo+1;
}

void Inicializar_Monticulo(pmonticulo m){
    m->ultimo = -1;
}

bool Monticulo_Vacio(pmonticulo m){
    return Size(m) == 0;
}

void Copiar(int v[], int n, pmonticulo m){
    int i;
    for(i = 0; i < n; i++){
        m->vector[i] = v[i];
    }
}

void Hundir(pmonticulo m, int i){
    int j; //Variable auxiliar
    int burbuja; //Variable auxiliar
    int hijoIzqPos;
    int hijoDerPos;
    do{
        j = i;
        hijoIzqPos = 2*i + 1;
        hijoDerPos = 2*i + 2;
        if(hijoIzqPos <= m->ultimo && m->vector[hijoIzqPos] <  m->vector[i]){
            i = hijoIzqPos;
        }
        if(hijoDerPos <= m->ultimo && m->vector[hijoDerPos] < m->vector[i]){
            i = hijoDerPos;
        }


        burbuja = m->vector[i];
        m->vector[i] = m->vector[j];
        m->vector[j] = burbuja;

    } while (j != i);
}


void crearMonticulo(int v[], int n, pmonticulo m){
    int i;  //Variable auxiliar
    Copiar(v,n,m);
    m->ultimo = (n - 1);
    for(i = Size(m)/2; i >= 0; i = i - 1){
        Hundir(m, i);
    }
}

int quitarMenor(pmonticulo m){
    int x = 0;
    if(Monticulo_Vacio(m)){
        printf("Monticulo vacio");
        return -1;
    }

    else{
        x = m->vector[0];
        m->vector[0] = m->vector[m->ultimo];
        m->ultimo = m->ultimo - 1;
        if(!Monticulo_Vacio(m))
            Hundir(m, 0);
    }
    return x;
}

void OrdenarPorMonticulos(int v[], int n){
    int i;
    struct monticulo m;
    Inicializar_Monticulo(&m);
    crearMonticulo(v, n, &m);
    for(i = 0; i < n; i++)
        v[i] = quitarMenor(&m);
}

void listar_monticulo(pmonticulo m){
    int i = 0;
    printf("[");
    for(i = 0; i < Size(m); ++i){
        (printf("%4d", m->vector[i]));
    }
    printf("]\n");
}

double medicionTiempo(int n, int tipo, int ord) {
    int v[n];
    double t, ta, tb;
    double t1, t2;
    int i;
    struct monticulo m;
    Inicializar_Monticulo(&m);

    if (tipo == 1) {aleatorio(v, n);}
    else if (tipo == 2) {descendente(v, n);}
    else {ascendente(v, n);}
    if(ord == 1){ta = microsegundos(); OrdenarPorMonticulos(v,n); tb = microsegundos();}
    if(ord == 2){ta = microsegundos(); crearMonticulo(v, n, &m); tb = microsegundos();}
    t = tb - ta;

    if (t < 500) {
        ta = microsegundos();
        if (tipo == 1 && ord == 1) {for (i = 1; i <= K; i++){aleatorio(v, n); OrdenarPorMonticulos(v,n);}}
        else if (tipo == 2 && ord == 1) {for (i = 1; i <= K; i++){descendente(v, n); OrdenarPorMonticulos(v,n);}}
        else if(tipo == 3 && ord == 1) {for (i = 1; i <= K; i++){ascendente(v, n); OrdenarPorMonticulos(v,n);}}
        else if (tipo == 1 && ord == 2) {for (i = 1; i <= K; i++){aleatorio(v, n); crearMonticulo(v, n, &m);}}
        else if (tipo == 2 && ord == 2) {for (i = 1; i <= K; i++){descendente(v, n); crearMonticulo(v, n, &m);}}
        else if(tipo == 3 && ord == 2) {for (i = 1; i <= K; i++){ascendente(v, n); crearMonticulo(v, n, &m);}}
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
    int i,n = 10;
    int v[n];
    struct monticulo m;

    printf("Inicializacion aleatoria:\n");
    aleatorio(v,n);
    listar_vector(v,n);
    printf("Ordenado? 0\n");

    printf("Ordenacion por montículos:\n");
    OrdenarPorMonticulos(v,n);
    listar_vector(v,n);
    printf("Ordenado? 1\n");

    printf("Test creación montículo:\n");
    aleatorio(v, n);
    listar_vector(v, n);
    crearMonticulo(v, n, &m);
    listar_monticulo(&m);

    printf("Test quitarMenor:\n");

    listar_monticulo(&m);
    for(i = 0; i < 5; i++){quitarMenor(&m); listar_monticulo(&m);}
    printf("Se han llevado a cabo %d operaciones quitarMenor\n", i);


}

void timetestSM(int tipo, int ord, float sub, float ajus, float sobre){
    char str[30] = "";
    double t;
    int n;
    ord == 1? strcpy(str, "Ordenación por monticulos") : strcpy(str, "Creacion de monticulo");
    if(tipo==1){printf("\n%s con inicialización aleatoria\n", str);}
    else if(tipo== 2){printf("\n%s con inicialización descendente\n", str);}
    else if(tipo==3){printf("\n%s con inicialización ascendente\n", str);}
    printHeadline(sub, ajus, sobre, ord);

    for(n = 500; n <= 32000 ; n *= 2){
        t = medicionTiempo(n,tipo, ord);
        warning(t);
        if(ord==1)
            printf("%12d%15.3f%26.8f%26.8f%26.8f\n", n, t, t/pow(n*log(n), sub), t/pow(n*log(n), ajus), t/pow(n*log(n), sobre));
        else
            printf("%12d%15.3f%26.8f%26.8f%26.8f\n", n, t, t/pow(n, sub), t/pow(n, ajus), t/pow(n, sobre));
    }
}

int main() {
    int i;
    inicializar_semilla();
    validar();
    for(i=0;i<3;i++){
        timetestSM(1,2, 0.8, 1, 1.2);
        timetestSM(1,1, 0.8, 1, 1.2);
        timetestSM(2,1, 0.8, 0.98, 1.2);
        timetestSM(3,1, 0.8, 0.978, 1.2);
    }
    return 0;
}
