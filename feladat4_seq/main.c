#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int max_depth=5;
int current_depth=0;


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

int sum_rec(int numbers[],int low,int upp)
{
    current_depth++;

    int sum=0;
    int i;
    int low1=low;
    int upp1=(int)((round(((double)low+upp)/2))-1);
    int low2=(int)(round(((double)low+upp)/2));
    int upp2=upp;
    int result;

    if(low==upp)
    {
        return numbers[low];
    }

    if(current_depth>=max_depth)
    {
        for(i=low;i<=upp;i++)
        {
            sum += numbers[i];
        }
        return sum;
    }
    result = sum_rec(numbers,low1,upp1);
    sum += result;
    result = sum_rec(numbers,low2,upp2);
    sum += result;
    return sum;
}



int main()
{
    int n = 30000;
    int numbers[n];
    int i;
    int sum1=0;
    int sum2=0;

    clock_t start,end;
    double timespent;

    srand(time(0));

    for(i = 0; i<n;i++)
    {
        numbers[i]=rand();
    }

    start=clock();
    sum1= sum_seq(numbers,n);
    end = clock();
    timespent = ((double)(end-start))/ CLOCKS_PER_SEC;
    printf("su1: %d timespent: %lf\n",sum1,timespent);

    start=clock();
    sum2= sum_rec(numbers,0,n-1);
    end = clock();
    timespent = ((double)(end-start))/ CLOCKS_PER_SEC;
    printf("sum2: %d timespent: %lf\n",sum2,timespent);

    return 0;
}
