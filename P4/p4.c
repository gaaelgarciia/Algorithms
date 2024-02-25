/*
 * Miguel Marcos Trillo   miguel.marcos.trillo@udc.es
 * Gael Garcia Arias  	gael.garciaa@udc.es
 * Brais Bello Pardo  	brais.bello.pardo@udc.es
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#define K 1000
#define TAM_MAX 1000

typedef int **matriz;

matriz crearMatriz(int n) {
    int i;
    matriz aux;
    if ((aux = malloc(n*sizeof(int *))) == NULL)
        return NULL;
    for (i=0; i<n; i++)
        if ((aux[i] = malloc(n*sizeof(int))) == NULL)
            return NULL;
    return aux;
}

/* Inicializacion pseudoaleatoria [1..TAM_MAX] de un grafo completo
no dirigido con n nodos, representado por su matriz de adayencia */

void iniMatriz(matriz m, int n) {
    int i, j;
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            m[i][j] = rand() % TAM_MAX + 1;
    for (i=0; i<n; i++)
        for (j=0; j<=i; j++)
            if (i==j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

void liberarMatriz(matriz m, int n) {
    int i;
    for (i=0; i<n; i++)
        free(m[i]);
    free(m);
}

void dijkstra(matriz grafo, matriz distancias, int tam){
    int n, i, v = 0, aux, w, k;
    int *noVisitados = malloc(tam*sizeof(int));
    for(n = 0; n < tam; n++){
        for(i = 0; i < tam; i++){
            noVisitados[i] = 1;
            distancias[n][i] = grafo[n][i];
        }
        noVisitados[n] = 0;
        for(k = 0; k < tam - 1; k++){
            v=-1;
            aux = 0;
            do{
                if(noVisitados[aux] && (v == -1 || distancias[n][aux] < distancias[n][v])){
                    v = aux;
                }
                aux++;
            }while(aux < tam);
            noVisitados[v] = 0;
            for(w = 0; w < tam; w++){
                if(noVisitados[w] && distancias[n][w] > (distancias[n][v] + grafo[v][w]))
                    distancias[n][w] = distancias[n][v] + grafo[v][w];
            }
        }
    }
    free(noVisitados);
}


void printHeadline(float sub, float ajus, float sobre){
    char str2[18] = "";
    strcpy(str2, "t(n)/n^");

    printf("%15s%15s", "n", "t(n)");


    if (sub != 1.0) {
        if (sub == (int)sub) {
            printf("%25s%.0f", str2, sub);
        } else {
            printf("%21s%.3f",  str2, sub);
        }
    } else {printf("%26s", "t(n)/n");}

    if (ajus != 1.0) {
        if (ajus == (int)ajus) {
            printf("%25s%.0f",str2, ajus);
        } else {
            printf("%21s%.3f",  str2, ajus);
        }
    } else {printf("%26s",  "t(n)/n");}

    if (sobre != 1.0) {
        if (sobre == (int)sobre) {
            printf("%25s%.0f",str2, sobre);
        } else {
            printf("%21s%.3f", str2, sobre);
        }
    } else {printf("%26s", "t(n)/n");}
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



void listar_matriz(matriz v, int n){
    int i = 0;
    int j = 0;
    for(i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%4d ", v[i][j]);
        }
        printf("\n");
    }
}


double medicionTiempo(int n) {
    double t, ta, tb;
    double t1, t2;
    int i;
    matriz m= crearMatriz(n);;
    matriz distancias = crearMatriz(n);



    iniMatriz(m,n);
    ta = microsegundos();
    dijkstra(m,distancias,n);
    tb = microsegundos();
    t = tb - ta;

    if (t < 500) {
        ta = microsegundos();
        for (i = 1; i <= K; i++){
            iniMatriz(m,n);
            dijkstra(m,distancias,n);}
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 1; i <= K; i++) {
            iniMatriz(m, n);}

        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / K;
    }
    liberarMatriz(m,n);
    liberarMatriz(distancias, n);
    return t;

}
void iniMatrizPredeterminada1(matriz m) {
    m[0][0] = 0;
    m[0][1] = 1;
    m[0][2] = 8;
    m[0][3] = 4;
    m[0][4] = 7;
    m[1][0] = 1;
    m[1][1] = 0;
    m[1][2] = 2;
    m[1][3] = 6;
    m[1][4] = 5;
    m[2][0] = 8;
    m[2][1] = 2;
    m[2][2] = 0;
    m[2][3] = 9;
    m[2][4] = 5;
    m[3][0] = 4;
    m[3][1] = 6;
    m[3][2] = 9;
    m[3][3] = 0;
    m[3][4] = 3;
    m[4][0] = 7;
    m[4][1] = 5;
    m[4][2] = 5;
    m[4][3] = 3;
    m[4][4] = 0;
}
void iniMatrizPredeterminada2(matriz m){
    m[0][0]=0;
    m[0][1]=1;
    m[0][2]=4;
    m[0][3]=7;
    m[1][0]=1;
    m[1][1]=0;
    m[1][2]=2;
    m[1][3]=8;
    m[2][0]=4;
    m[2][1]=2;
    m[2][2]=0;
    m[2][3]=3;
    m[3][0]=7;
    m[3][1]=8;
    m[3][2]=3;
    m[3][3]=0;
}
void validar() {
    int n = 4;
    int n2 = 5;
    matriz m = crearMatriz(n);
    iniMatrizPredeterminada2(m);
    matriz distancias = crearMatriz(n);

    matriz m2 = crearMatriz(n2);
    iniMatrizPredeterminada1(m2);
    matriz distancias2 = crearMatriz(n2);


    printf("Matriz adyacencia:\n");
    listar_matriz(m2, n2);

    printf("Distancias mínimas:\n");
    dijkstra(m2, distancias2, n2);
    listar_matriz(distancias2, n2);

    printf("Matriz adyacencia:\n");
    listar_matriz(m, n);

    printf("Distancias mínimas:\n");
    dijkstra(m, distancias, n);
    listar_matriz(distancias, n);


    liberarMatriz(m2, n2);
    liberarMatriz(distancias2, n2);
    liberarMatriz(m, n);
    liberarMatriz(distancias, n);
}

void timetestSM( float sub, float ajus, float sobre){
    double t;
    int n;

    printf("\nAlgortimo de Dijkstra con inicialización aleatoria\n");
    printHeadline(sub, ajus, sobre);

    for(n = 10; n <= 1000 ; n *= 2){
        t = medicionTiempo(n);
        warning(t);
        printf("%12d%15.3f%26.8f%26.8f%26.8f\n", n, t, t/pow(n, sub), t/pow(n ,ajus), t/pow(n, sobre));
    }
}

int main() {
    int i;
    inicializar_semilla();
    validar();
    for(i = 0; i < 6; i++)
        timetestSM(2.65,2.855,3);
    return 0;
}