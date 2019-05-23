#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#define SEED 1234

struct nIter    //dicionario
{
   int nIter;
   int nThread;
};

void* monteCarlo(void* parameters){

   clock_t start = clock();

   struct nIter* p = (struct nIter*) parameters;
   double x, y, z, pi;
   int i;
   int count; /* # of points in the 1st quadrant of unit circle */

   /* initialize random numbers */
   srand(SEED);
   for ( i=0; i < p->nIter; i++) {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = x*x+y*y;
      if (z<=1) count++;
      }
      
   pi=(double)count/p->nIter*4;
   printf("Número de Tentativas: %d , a estimativa do pi é %g \n",p->nIter,pi);

   clock_t stop = clock();
   double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
   printf("Time elapsed in ms: %f\n", elapsed);
}


void main() { /*2 threads*/

    int n;
    int i;
    int j1;
    int j2;
    int numIter;
    int respostas[];

    struct nIter tidArgs; //buscar argumentos global q é o numero de iterações
    pthread_t tid;


    printf("\nPor favor insira o número de tentativas: \n");
    scanf("%d",&j1);
    tidArgs.nIter = j1; //numero de iteracoes
    printf("\nPor favor insira o número de threads: \n");
    scanf("%d",&j2);
    tidArgs.nThread = j2; //numero de threads

    numIter = tidArgs.nIter/tidArgs.nThread;
    // '&tidArgs/ 2'     e colocar no thread_create , isto faz com que corra 2vezes



    for(i = 0; i < tidArgs.nThread; i++){ 
    pthread_create (&tid, NULL, monteCarlo, &numIter);
    pthread_join(&tid, respostas[i]);
    }

    pthread_exit(NULL);   
}
