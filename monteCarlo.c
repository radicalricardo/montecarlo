#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define SEED 666


void montecarlo(){

clock_t start = clock();

   int numIteracoes=0;
   double x,y, z, pi;
   int i,count=0; /* # of points in the 1st quadrant of unit circle */


   printf("Por favor insira o número de tentativas: ");
   scanf("%d",&numIteracoes);

   /* initialize random numbers */
   srand(SEED);
   count=0;
   for ( i=0; i<numIteracoes; i++) {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = x*x+y*y;
      if (z<=1) count++;
      }
      
   pi=(double)count/numIteracoes*4;
   printf("Número de Tentativas: %d , a estimativa do pi é %g \n",numIteracoes,pi);

clock_t stop = clock();
double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
printf("Time elapsed in ms: %f", elapsed);
}

int main() {

montecarlo();


}
