#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


int main()
{
    int i;
    int n = 30;
    int numbers[n];
    int sum1=0;
    int sum2=0;

    clock_t start,end;
    double timespent1,timespent2;

    srand(time(0));

    for(i=0;i<n;i++)
    {
        numbers[i]= rand();
    }

    start=clock();
    #pragma omp parallel
    {
        int j;
        #pragma omp for
        for(j=0;j<n;j++)
        {
            #pragma omp critical
            sum1 += numbers[j];
        }
    }
    end = clock();
    timespent1 = ((double)(end-start))/ CLOCKS_PER_SEC;

    start=clock();
    #pragma omp parallel
    {
        int j;
        #pragma omp for reduction (+:sum2)
        for(j=0;j<n;j++)
        {
            #pragma omp critical
            sum2 += numbers[j];
        }
    }
    end = clock();
    timespent2 = ((double)(end-start))/ CLOCKS_PER_SEC;

    printf("sum1:%d timespent:%lf\n",sum1,timespent1);
    printf("sum2:%d timespent:%lf\n",sum2,timespent2);

    return 0;
}
