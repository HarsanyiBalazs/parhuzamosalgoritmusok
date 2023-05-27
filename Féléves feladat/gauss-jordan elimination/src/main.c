#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>

const int n = 5;

/**
 * Generate the data for 1 dimensional array.
 */
void generate_data(double b[],int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        b[i]=rand();
    }
}

/**
 * Generate the data for 2 dimensional array.
 */l

void generate_data_2d(double a[][n],int size)
{
    int i,j;

    for(j=0;j<size;j++)
    {
        for(i=0;i<size;i++)
        {
            a[j][i] = rand();
        }
    }
}

/**
 * Solve the equation using Gauss-Jordan elimination.
 */
void gauss_jordan(double a[][n],double b[],double x[],int size)
{
    int k,i,j;
    double temp;
    for( k=0;k<size;k++)
    {
        #pragma omp parallel for private (temp,j)
        for(i=0;i<size;i++)
        {   
            if(i!=k)
            {
                if(a[k][k]!=0)
                {
                    temp=a[i][k]/a[k][k];
                }
                b[i]=b[i]-temp*b[k];
                for(j=k;j<size;j++)
                {
                    a[i][j]=a[i][j]-temp*a[k][j];
                }
            }
        }
    }
    for ( k = 0; k < size; k++)
    {
        if (a[k][k]==0)
        {
            printf("Gauss-Jordan elimination cant be performed on the matrix");
            return ;
        }
    }
    
    #pragma omp parallel for
    for ( k = 0; k < size; k++)
    {
        x[k]= b[k]/a[k][k];
    }
}

/**
 * Main
 */
int main()
{
    int size=n;
    double a[size][size];
    double b[size];
    double x[size];
    int j,i;
    
    clock_t passed_time;
    double time_taken;

    srand(123);

    generate_data(b,size);
    generate_data_2d(a,size);
    
    
    for( i=0;i<size;i++)
    {
        printf("\n");
        for(int j=0;j<n;j++)
        {
            printf("%lf ",a[i][j]);
        }
    }
    printf("\n");
    for( i=0;i<size;i++)
    {
        printf("%lf\n",b[i]);
    } 
    
    omp_set_num_threads(2) ;

    passed_time=clock();
    gauss_jordan(a,b,x,size);
    passed_time = clock() - passed_time;
    time_taken = ((double)passed_time)/CLOCKS_PER_SEC;


    
    printf("\n\n finished arrays:\n\n");
    for(i=0;i<size;i++)
    {
        printf("\n");
        for(int j=0;j<n;j++)
        {
            printf("%lf ",a[i][j]);
        }
    }

    printf("\n");
    for(i=0;i<size;i++)
    {
        printf("%lf\n",b[i]);
    }
    

    
    printf("\n");
    for(i=0;i<size;i++)
    {
        printf("%lf\n",x[i]);
    }
    
    printf("The program took %f seconds to execute", time_taken);

    return 0;
}
