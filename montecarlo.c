#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

struct parametros   //Guardamos aqui os parâmetros da thread em forma de estrutura
{
   int numeroIteracoes; //O número de iterações do algoritmo
   int numeroThreads;   //E o número de threads que iremos usar
};


void* monteCarlo(void* parameters){

    struct parametros* p = (struct parametros*) parameters;
    double x, y, z, pi;
    int i;
    int* count = malloc(sizeof(int)); //Inicializamos uma variável ponteiro de int, com o tamanho de um inteiro
    *count = 0; //Damos-lhe o primeiro valor, 0
    int seed = time(NULL) ^ pthread_self();  //Seed baseada no tempo actual do sistema e no ID da thread, para as threads não terem a mesma seed
    //Algoritmo
    for ( i=0; i < p->numeroIteracoes / p->numeroThreads; i++) { //Dividimos o algoritmo pelo número de threads que tamos a usar
        x = (double)rand_r(&seed)/RAND_MAX;
        y = (double)rand_r(&seed)/RAND_MAX;
        z = x*x+y*y;
        if (z<=1)
            *count = *count + 1;
        }    
    printf("ThreadID: %d, Count: %d\n", pthread_self(), *count); //Print para mostrar os valores contados por cada thread
    return (void*) count;
}


void main() 
{
    struct parametros argumentosThread; //Fazemos uma nova estrutura para passar como argumento à thread

    void* aux;
    int* values[255];
    int i;
    double pi;
    pthread_t* thread_IDS = malloc(argumentosThread.numeroThreads *sizeof(pthread_t)); //bruxaria do guiao2prog2
    double pontosCirculo;
    int x, y;

    printf("Insira o número de iterações.\n");
    scanf("%i", &x);

    printf("Insira o número de threads.\n");
    scanf("%i", &y);

    
    clock_t start = clock();
    argumentosThread.numeroIteracoes = x;
    argumentosThread.numeroThreads = y;  

    for (i=0;i<argumentosThread.numeroThreads;i++)
    {
        pthread_create (thread_IDS+i, NULL, monteCarlo, &argumentosThread); //criar a thread
    }

    for (i=0;i<argumentosThread.numeroThreads;i++)
    {
        pthread_join(*(thread_IDS+i),&aux);   //RECEBE OS VALORES (neste caso o count do algoritmo da montecarlo, divididos por thread)
        values[i] = (int *) aux;              //SOMA OS VALORES NUMA ARRAY!!! (um elemento da array por cada thread com o seu valor de count)
    }

    for (i=0; i<argumentosThread.numeroThreads;i++)
    {
        pontosCirculo = pontosCirculo + *values[i]; //SOMA TODOS OS VALORES DA ARRAY!!! 
    }
    clock_t stop = clock();

    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Pontos dentro do círculo: %.0f\n", pontosCirculo);
    pi = pontosCirculo/argumentosThread.numeroIteracoes*4;
    printf("Estimativa do pi: %g\n", pi);
    printf("Tempo de execução do programa total: %.0f ms\n", elapsed);
    
    pthread_exit(NULL); 

}