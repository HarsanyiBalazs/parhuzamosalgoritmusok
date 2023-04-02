#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct thread_data
{
    int lower;
    int higher;
    int* number;
}thread_data;


const int N_THREADS = 30;
int even_numbers=0;

void* get_even_numbers(void* param)
{

    struct thread_data *datas= (struct thread_data*)param;
    for(;datas->lower<datas->higher;datas->lower++)
    {
        if((datas->number[datas->lower]%2) == 0)
        {
            even_numbers++;
        }
    }
}

int main()
{
    pthread_t threads[N_THREADS];
    struct thread_data datas;
    int n = 30000;
    int i;
    datas.lower=0;
    int plus=n/N_THREADS;;

    srand( time(0));

    datas.number =  (int*)malloc(n * sizeof(int));
    if (datas.number == NULL) {
        printf("Memory not allocated.\n");
        return 1;
    }

    for(i=0;i<n;i++)
    {
            rand();
            datas.number[i]=rand();
    }

    for(i=0;i<n;i++)
    {
        printf("%d\n",datas.number[i]);
    }

    printf("create threads\n");
    for (i = 0; i < N_THREADS; ++i)
    {
        datas.higher = (i+1)*plus;
        pthread_create(&threads[i], NULL, get_even_numbers , (void*)&datas );
    }

    printf("join threads\n");
    for ( i = 0; i < N_THREADS; i++)
    {
        pthread_join(threads[i],NULL);
    }
    printf("%d",even_numbers);
    return 0;
}
