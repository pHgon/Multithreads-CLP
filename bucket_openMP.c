#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "bucket.h"
 

void bucket_sortOMP(int v[], int tam, int numBaldes){
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

    omp_set_num_threads(numBaldes); //Define numero de threads

    #pragma omp parallel for //Quebra de laço em tarefas
        for(int i=0; i<numBaldes; i++){
            bubbleOMP(buckets[i].balde, buckets[i].topo);
        }

    //Esta so executa quando o pragma for terminar
    // Retorna os elementos dos baldes para o vetor principal
    for(i=0, j=0;j<numBaldes;j++){    //poe os elementos dos baldes de volta no vetor
        for(k=0;k<buckets[j].topo;k++){
            v[i]=buckets[j].balde[k];
             i++;
        }
    }
    
}


void bubbleOMP(int v[], int topo){
    for(int lenght=topo-1; lenght>0; --lenght){
        for(int i=0; i<lenght; ++i){
            if(v[i]>v[i+1]){
                int aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
            }
        }
    }
}