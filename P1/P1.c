#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#define K 100



double microsegundos();
int sumaSubMax1(int v[], int n);
int sumaSubMax2(int v[], int n);
void listar_vector(int v[], int n);
void inicializar_semilla();
void aleatorio(int v[], int n);
double medicionTiempoS1(int n);
double medicionTiempoS2(int n);
void test1();
void test2();
void timetestSM1();
void timetestSM2();

int main(){
	inicializar_semilla();
	test1();
	test2();
	timetestSM1();
	timetestSM1();
	timetestSM1();
	timetestSM2();
	timetestSM2();
	timetestSM2();
	return 0;
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

void aleatorio(int v[], int n){
	int i, m=2*n+1;
	for(i = 0; i < n; ++i)
		v[i] = (rand() % m) - n;
}

int sumaSubMax1(int v[], int n){
	int sumaMax = 0, estaSuma;
	for(int i = 0; i < n ; i++){
		estaSuma = 0;
		for(int j = i; j < n; j++){
			estaSuma += v[j];
			if(estaSuma > sumaMax)
				sumaMax = estaSuma;
		}
	}
	return sumaMax;
}

int sumaSubMax2(int v[], int n){
	int sumaMax = 0, estaSuma = 0;
	for(int j = 0; j < n ; j++){
			estaSuma += v[j];
			if(estaSuma > sumaMax)
				sumaMax = estaSuma;
			if(estaSuma < 0)
				estaSuma = 0;
		}
	return sumaMax;
}	

void listar_vector(int v[], int n){
	printf("[");
	for(int i = 0; i < n; ++i){
		(printf("%4d", v[i]));
	}
	printf("]");
}

double medicionTiempoS1(int n){
	int v[n];
	double t,ta,tb;
	aleatorio(v, n);
	ta = microsegundos();
	sumaSubMax1(v,n);
	tb = microsegundos();
	t = tb - ta;
	if(t < 500){
		double t1,t2;
		ta = microsegundos();
		for(int i = 1; i <= K; i++){
			aleatorio(v, n);
			sumaSubMax1(v, n);
		}
		tb = microsegundos();
		t1 = tb - ta;
		ta = microsegundos();
		for(int i = 1; i <= K; i++){
			aleatorio(v,n);
		}
		tb = microsegundos();
		t2 = tb - ta;
		t = (t1 - t2)/K;
	}
	return t;
}

double medicionTiempoS2(int n){
	int v[n];
	double t,ta,tb;
	aleatorio(v, n);
	ta = microsegundos();
	sumaSubMax2(v, n);
	tb = microsegundos();
	t = tb - ta;
	if(t < 500){
		double t1,t2;
		ta = microsegundos();
		for(int i = 1; i <= K; i++){
			aleatorio(v,n);
			sumaSubMax2(v, n);
		}
		tb = microsegundos();
		t1 = tb - ta;
		ta = microsegundos();
		for(int i = 1; i <= K; i++){
			aleatorio(v, n);
		}
		tb = microsegundos();
		t2 = tb - ta;
		t = (t1 - t2)/K;
	}
	return t;
}


void test1(){
	int n = 5;
	int v1[5] = {-9, 2, -5, -4, 6};
	int v2[5] = {4, 0, 9, 2, 5};
	int v3[5] = {-2, -1, -9, -7, -1};
	int v4[5] = {9, -2, 1, -7, -8};
	int v5[5] = {15, -2, -5, -4, 16};
	int v6[5] = {7, -5, 6, 7, -7};
	printf("\nTest 1:\n");
	printf("%22s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
	listar_vector(v1, n);
	printf("%15d%15d\n", sumaSubMax1(v1, n), sumaSubMax2(v1, n));
	listar_vector(v2, n);
	printf("%15d%15d\n", sumaSubMax1(v2, n), sumaSubMax2(v2, n));
	listar_vector(v3, n);
	printf("%15d%15d\n", sumaSubMax1(v3, n), sumaSubMax2(v3, n));
	listar_vector(v4, n);
	printf("%15d%15d\n", sumaSubMax1(v4, n), sumaSubMax2(v4, n));
	listar_vector(v5, n);
	printf("%15d%15d\n", sumaSubMax1(v5, n), sumaSubMax2(v5, n));
	listar_vector(v6, n);
	printf("%15d%15d\n", sumaSubMax1(v6, n), sumaSubMax2(v6, n));
	
}

void test2(){
	int s1, s2;
	int v[9];
	printf("\nTest 2:\n");
	printf("%38s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
	for(int i = 0; i < 10; i++){
		aleatorio(v, 9);
		listar_vector(v, 9);
		s1 = sumaSubMax1(v, 9);
		s2 = sumaSubMax2(v, 9);
		printf("%15d%15d\n", s1, s2);
	}

}

void warning(double t){
	if(t < 500)
		printf("(*)");
	else
		printf("%3s","");
}

void timetestSM1(){
	printf("\nSumaSubMax 1\n");
	printf("%15s%15s%15s%15s%15s\n","n","t(n)","t(n)/n^1.8","t(n)/n^2","t(n)/n^2.2");
	double t = 0;
	for(int n = 500; n <= 32000 ; n *= 2){
		t = medicionTiempoS1(n);
		warning(t);
		printf("%12d%15f%15f%15f%15f\n", n, t, t/pow(n, 1.8), t/pow(n, 2.0), t/pow(n, 2.2));
	}
}

void timetestSM2(){
	printf("\nSumaSubMax 2\n");
	printf("%15s%15s%15s%15s%15s\n","n","t(n)","t(n)/n^0.8","t(n)/n","t(n)/n^1.2");
	double t = 0;
	for(int n = 500; n <= 256000 ; n *= 2){
		t = medicionTiempoS2(n);
		warning(t);
		printf("%12d%15f%15f%15f%15f\n", n, t, t/pow(n, 0.8), t/n, t/pow(n, 1.2));
	}
}

