#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


/**
 * Generate the data for y axis array.
 */
double* generate_data(int size)
{
    double* data;
    int i;
    double random;
    data = (double*)malloc(size * sizeof(double));
    for (i = 0; i < size; ++i) 
    {
        random=(double)(rand()%(100) -50);
        data[i] =random;
    }

  return data;
}


/**
 * Generate the data for x axis array.
 */
double* generate_data_x(int size)
{
    double* data;
    int i;
    double random;
    data = (double*)malloc(size * sizeof(double));
    for (i = 0; i < size; ++i) 
    {
        data[i] = i;
    }

  return data;
}


/**
 * Interpolate the y value at given x value (sequentially).
 */
double lagrange_interpolation_seq(int size,double* x,double* y,double target_x)
{
    double sum=0;
    double li[size];
    double l;
    int i,j;
    for ( i = 0; i < size; i++)
    {
        l=1;
        for(j=0;j<size;j++)
        {
            if(j!=i)
            {
                l=l*(target_x-x[j])/(x[i]-x[j]);
            }
        }
        l*=y[i];
        li[i]=l;
    }

    for(i=0;i<size;i++)
    {
        sum+= li[i];
    }
    return sum;
}


/**
 * Interpolate the y value at given x value (parallelly).
 */
double lagrange_interpolation_par(int size,double* x,double* y,double target_x)
{
    double sum=0;
    double li[size];
    double l;
    int i,j;
    #pragma omp parallel for private (j,l)
    for ( i = 0; i < size; i++)
    {
        l=1;
        for(j=0;j<size;j++)
        {
            if(j!=i)
            {
                l=l*(target_x-x[j])/(x[i]-x[j]);
            }
        }

        l*=y[i];
        li[i]=l;
    }

    #pragma omp parallel for reduction (+:sum)
    for(i=0;i<size;i++)
    {
        sum+= li[i];
    }
    return sum;
}

/**
 * Main
 */
int main(){
    int i,size;
    double interpolation_result;
    double target_x;  //Value of x for which interpolated value is required.
    //Arrays to store the x and y data-points.
    double* x;
    double* y;

    double time_taken;
    clock_t passed_time;
    srand(1234);

    size=4000;
    x=generate_data_x(size);
    y=generate_data(size);
    target_x=500;


    /*
    for(i=0;i<size;i++)
    {
        printf("x: %lf y: %lf\n",x[i],y[i]);
    }
    */
    printf("x: %lf y: %lf\n",x[500],y[500]);
    //printf("x: %lf y: %lf\n",x[1002],y[1002]);

    omp_set_num_threads(4) ;

    passed_time = clock();
    interpolation_result=lagrange_interpolation_seq(size,x,y,target_x);
    printf("The interpolated value is %lf\n",interpolation_result);
    passed_time = clock() - passed_time;
    time_taken = ((double)passed_time)/CLOCKS_PER_SEC;
    printf("The program took %f seconds to execute (sequential)\n", time_taken);

    passed_time = clock();
    interpolation_result=lagrange_interpolation_par(size,x,y,target_x);
    printf("The interpolated value is %lf\n",interpolation_result);
    passed_time = clock() - passed_time;
    time_taken = ((double)passed_time)/CLOCKS_PER_SEC;
    printf("The program took %f seconds to execute (parallel)\n", time_taken);

    return 0;
}