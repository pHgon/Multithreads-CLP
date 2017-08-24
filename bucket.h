#define tam_bucket 100

typedef struct {
	int topo;
	int balde[20000];
}bucket;

void bucket_sortPT(int v[], int tam, int numBaldes);
void bucket_sortOMP(int v[], int tam, int numBaldes);
void *bubble(void *str);  
void bubbleOMP(int vetor[], int tam);