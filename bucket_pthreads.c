#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "bucket.h"
 

void bucket_sortPT(int v[], int tam, int numBaldes){
	pthread_t ordena[numBaldes];  // Threads que ordenam os buckets
    bucket buckets[numBaldes];
    int i, j, k, contRegra;

    // Inicia Variaveis com 0
    for (i = 0; i < numBaldes; i++){ 
        buckets[i].topo = 0;
    }

    // Conjunto de REGRAS para divisao dos baldes
    switch(numBaldes){
    	case 1:
    		for (i = 0; i < tam; i++){
    			buckets[0].balde[buckets[0].topo] = v[i];
            	buckets[0].topo++;
    		}
    		break;
    	case 2:
    		contRegra = RAND_MAX / numBaldes;
    		for (i = 0; i < tam; i++){
        		if (v[i] <= contRegra){
            		buckets[0].balde[buckets[0].topo] = v[i];
            		buckets[0].topo++;
        		}
        		else{
        			buckets[1].balde[buckets[1].topo] = v[i];
            		buckets[1].topo++;
        		}
    		}
    		break;
    	case 4:
    		contRegra = RAND_MAX / numBaldes;
    		for (i = 0; i < tam; i++){
        		if (v[i] <= contRegra){
            		buckets[0].balde[buckets[0].topo] = v[i];
            		buckets[0].topo++;
            		continue;
        		}
        		if (v[i] <= contRegra*2){
            		buckets[1].balde[buckets[1].topo] = v[i];
            		buckets[1].topo++;
            		continue;
        		}
        		if (v[i] <= contRegra*3){
            		buckets[2].balde[buckets[2].topo] = v[i];
            		buckets[2].topo++;
            		continue;
        		}
            	buckets[3].balde[buckets[3].topo] = v[i];
            	buckets[3].topo++;
            	continue;
    		}
    		break;
    	case 8:
    		contRegra = RAND_MAX / numBaldes;
    		for (i = 0; i < tam; i++){
        		if (v[i] <= contRegra){
            		buckets[0].balde[buckets[0].topo] = v[i];
            		buckets[0].topo++;
            		continue;
        		}
        		if (v[i] <= contRegra*2){
            		buckets[1].balde[buckets[1].topo] = v[i];
            		buckets[1].topo++;
            		continue;
        		}
        		if (v[i] <= contRegra*3){
            		buckets[2].balde[buckets[2].topo] = v[i];
            		buckets[2].topo++;
            		continue;
        		}
        		if (v[i] <= contRegra*4){
            		buckets[3].balde[buckets[3].topo] = v[i];
            		buckets[3].topo++;
            		continue;
        		}
        		if (v[i] <= contRegra*5){
            		buckets[4].balde[buckets[4].topo] = v[i];
            		buckets[4].topo++;
            		continue;
        		}
        		if (v[i] <= contRegra*6){
            		buckets[5].balde[buckets[5].topo] = v[i];
            		buckets[5].topo++;
            		continue;
        		}
        		if (v[i] <= contRegra*7){
            		buckets[6].balde[buckets[6].topo] = v[i];
            		buckets[6].topo++;
            		continue;
        		}
        		buckets[7].balde[buckets[7].topo] = v[i];
            	buckets[7].topo++;
            	continue;
            }
    		break; 
    }

    /*for(i=0; i<numBaldes; i++)
    	printf("balde: %d  quant: %d\n", i, buckets[i].topo);
    printf("\n");*/

    // Cria as Threads e inicia as funcoes
    for(int i=0; i<numBaldes; i++){
		if(pthread_create(&ordena[i], NULL, bubble, (void*)&buckets[i])){
			printf("\nERROR: Criação de Thread de Ordenação\n\n");
			exit(-1);
		}
	}

	// Espera ate que todas as threads terminem de executar
	for(int i=0; i<numBaldes; i++){
		pthread_join(ordena[i], NULL);
	}	

	// Retorna os elementos dos baldes para o vetor principal
	for(i=0, j=0;j<numBaldes;j++){    //poe os elementos dos baldes de volta no vetor
		for(k=0;k<buckets[j].topo;k++){
			v[i]=buckets[j].balde[k];
			i++;
		}
	}
}


void *bubble(void *str){
	bucket *aux = (bucket*)str;

	int i,j,temp,flag;
	if(aux->topo){
		for(j=0;j<aux->topo-1;j++){
			flag=0;
			for(i=0;i<aux->topo-1;i++){
				if(aux->balde[i+1]<aux->balde[i]){
					temp=aux->balde[i];
					aux->balde[i]=aux->balde[i+1];
					aux->balde[i+1]=temp;
					flag=1;
				}
			}
			if(!flag)
				pthread_exit(NULL);
		}
	}
	pthread_exit(NULL);
}