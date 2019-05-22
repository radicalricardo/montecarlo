#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#define NUM_THREADS 2
#define SEED 666

struct nIter
{
   int nIter;
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
   printf("Time elapsed in ms: %f", elapsed);
}


void main() { /*2 threads*/

   int n;
   struct nIter tidArgs;

   printf("Por favor insira o número de tentativas: ");
   scanf("%d",&n);

   tidArgs.nIter = n; 

   pthread_t thread1_id;
   pthread_t thread2_id;

   pthread_create (&thread1_id, NULL, monteCarlo, &tidArgs);
   pthread_create (&thread2_id, NULL, monteCarlo, &tidArgs);
   pthread_exit(NULL);
}