#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <windows.h>

int max_depth=50;
int current_depth=0;
int sum2=0;
pthread_mutex_t value_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct thread_data
{
    int low;
    int upp;
    int* numbers;
    int size;
}thread_data;


int sum_seq(int numbers[],int n)
{
    int i;
    int sum=0;

    for(i=0;i<n;i++)
    {
        sum += numbers[i];
    }
    return sum;
}

void* sum_posix(void* param)
{
    current_depth++;
    struct thread_data *datas= (struct thread_data*)param;
    pthread_t thread1,thread2;

    int i;
    struct thread_data datalower;
    struct thread_data dataupper;
    datalower.low= datas->low;
    datalower.upp=(int)((round(((double)(datas->upp)+(datas->low))/2)-1));
    dataupper.low=(int)(round(((double)(datas->upp)+(datas->low))/2));
    dataupper.upp=datas->upp;
    datalower.size= datas->size;
    dataupper.size= datas->size;
    datalower.numbers=(int*)malloc((datas->size) * sizeof(int));
    dataupper.numbers=(int*)malloc((datas->size) * sizeof(int));


    for(i=0;i<datas->size;i++)
    {
        datalower.numbers[i]=datas->numbers[i];
        dataupper.numbers[i]=datas->numbers[i];
    }



    if(datas->low==datas->upp)
    {
        pthread_mutex_lock(&value_mutex);
        sum2 += datas->numbers[datas->low];
        pthread_mutex_unlock(&value_mutex);

    }
    else if(current_depth==max_depth)
    {
        for(i=datas->low;i<=datas->upp;i++)
        {
            pthread_mutex_lock(&value_mutex);
            sum2 += datas->numbers[i];
            pthread_mutex_unlock(&value_mutex);
        }

    }
    else
    {


        pthread_create(&thread1, NULL, sum_posix , (void*)&datalower );


        if(current_depth==max_depth)
        {
                for(i=dataupper.low;i<=dataupper.upp;i++)
                    {
                        pthread_mutex_lock(&value_mutex);
                        sum2 += dataupper.numbers[i];
                        pthread_mutex_unlock(&value_mutex);
                    }
        }
        else
        {

            pthread_create(&thread2, NULL, sum_posix , (void*)&dataupper );
            pthread_join(thread2,NULL);
        }
        pthread_join(thread1,NULL);
    }

}

int main()
{
    int n = 30;
    int numbers[n];
    int i;
    int sum1=0;
    pthread_t thread;

    struct thread_data datas;
    datas.size=n;
    datas.numbers =  (int*)malloc(n * sizeof(int));
    datas.low=0;
    datas.upp=n-1;

    clock_t start,end;
    double timespent;


    srand(time(0));

    for(i = 0; i<n;i++)
    {
        numbers[i]=rand();
        datas.numbers[i]=numbers[i];
    }


    sum1= sum_seq(numbers,n);


    start=clock();
    pthread_create(&thread, NULL, sum_posix , (void*)&datas );
    pthread_join(thread,NULL);
    end = clock();
    timespent = ((double)(end-start))/ CLOCKS_PER_SEC;

    printf("sum: %d\n",sum1);
    printf("sum2: %d timespent: %lf\n",sum2,timespent);


    return 0;
}
