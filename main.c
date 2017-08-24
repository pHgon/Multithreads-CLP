#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bucket.h"



#define IMPRIMIRVETOR 0  // 0-desligado  1-ligado



void imprimeVetor(int v[], int tamVetor){
	int i, j;
	for(i=0, j=9; i<tamVetor; i++, j--){
		printf("%-10d  ",v[i]);
		if(j==0){
			printf("\n");
			j=10;
		}
	}
	printf("\n");
}

//Gio - Alterei a funcao para receber o vetor como parametro
//utilizei o vetor vOrder como uma copia do 'original', para que o v original nao seja ordenado, podendo ser utilizado em todos os testes
void testaBucketsPT (int v[], int tamVetor, int numBaldes){
	clock_t inicio, fim;
	int i, vOrder[tamVetor];

	for(i = 0; i<tamVetor; i++)
		vOrder[i] = v[i];

	if(IMPRIMIRVETOR){
		printf("\nVetor Aleatorio:\n");
		imprimeVetor(v, tamVetor);
	}
	
	if(numBaldes == 1 || numBaldes == 2 || numBaldes == 4 || numBaldes == 8){
		inicio = clock();
		bucket_sortPT(vOrder, tamVetor, numBaldes);
		fim = clock();

		printf("\nTamanho Vetor:     %-5d", tamVetor);
		printf("\nNúmero de Threads: %d", numBaldes);
		printf("\nTempo de Execução: %lf\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
	}
	else{
		printf("ERROR: Número de Buckets Inválido .. Programa Encerrado\n\n");
		exit(-1);
	}

	if(IMPRIMIRVETOR){
		printf("\nVetor Ordenado:\n");
		imprimeVetor(vOrder, tamVetor);
	}
}

void testaBucketsOMP (int v[], int tamVetor, int numBaldes){
	clock_t inicio, fim;
	int i, vOrder[tamVetor];
	for(i = 0; i<tamVetor; i++)
		vOrder[i] = v[i];

	if(IMPRIMIRVETOR){
		printf("\nVetor Aleatorio:\n");
		imprimeVetor(v, tamVetor);
	}
	
	if(numBaldes == 1 || numBaldes == 2 || numBaldes == 4 || numBaldes == 8){
		inicio = clock();
		bucket_sortOMP(vOrder, tamVetor, numBaldes);
		fim = clock();

		printf("\nTamanho Vetor:     %-5d", tamVetor);
		printf("\nNúmero de Threads: %d", numBaldes);
		printf("\nTempo de Execução: %lf\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
	}
	else{
		printf("ERROR: Número de Buckets Inválido .. Programa Encerrado\n\n");
		exit(-1);
	}

	if(IMPRIMIRVETOR){
		printf("\nVetor Ordenado:\n");
		imprimeVetor(vOrder, tamVetor);
	}
}


int main(void){


	// EXECUCOES PARA O TRABALHO

	//Gio - Trouxe o preenchemento do vetor para o main, para que possa ser usada a mesma sequencia aleatoria de numeros nos dois metodos (pthreads e open mp)
	int i, v1[1000], v10[10000], v20[20000];

	srand(time(NULL));
	for(i=0; i<1000; i++){
		v1[i] = rand()%RAND_MAX;
	}

	
	for(i=0; i<10000; i++){
		v10[i] = rand()%RAND_MAX;
	}

	for(i=0; i<20000; i++){
		v20[i] = rand()%RAND_MAX;
	}

	printf("\n\nParalelismo com POSIX Threads:\n");
	testaBucketsPT(v1, 1000, 1);
	testaBucketsPT(v1, 1000, 2);
	testaBucketsPT(v1, 1000, 4);
	testaBucketsPT(v1, 1000, 8);

	testaBucketsPT(v10, 10000, 1);
	testaBucketsPT(v10, 10000, 2);
	testaBucketsPT(v10, 10000, 4);
	testaBucketsPT(v10, 10000, 8);
	
	testaBucketsPT(v20, 20000, 1);
	testaBucketsPT(v20, 20000, 2);
	testaBucketsPT(v20, 20000, 4);
	testaBucketsPT(v20, 20000, 8);

	printf("\n\n");

	printf("\nParalelismo com Open MP:\n");
	testaBucketsOMP(v1, 1000, 1);
	testaBucketsOMP(v1, 1000, 2);
	testaBucketsOMP(v1, 1000, 4);
	testaBucketsOMP(v1, 1000, 8);

	testaBucketsOMP(v10, 10000, 1);
	testaBucketsOMP(v10, 10000, 2);
	testaBucketsOMP(v10, 10000, 4);
	testaBucketsOMP(v10, 10000, 8);
	
	testaBucketsOMP(v20, 20000, 1);
	testaBucketsOMP(v20, 20000, 2);
	testaBucketsOMP(v20, 20000, 4);
	testaBucketsOMP(v20, 20000, 8);
	printf("\n");
	return 0;
}