#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


const int N_THREADS = 60;

void* wait_one_sec(void* _)
{
    printf("start\n");
    Sleep(1000);
    printf("over\n");
    
}

int main(int argc, char* argv[])
{
    clock_t end,start;
    start = clock();
    double timespent;
    pthread_t threads[N_THREADS];
    int i;

    printf("create threads\n");
    for (i = 0; i < N_THREADS; ++i) 
    {
        pthread_create(&threads[i], NULL, wait_one_sec , NULL);
    }

    printf("join threads\n");
    for ( i = 0; i < N_THREADS; i++)
    {
        pthread_join(threads[i],NULL);
    }
    

    end= clock();
    timespent = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time spent: %lf\n",timespent);
    return 0;
}