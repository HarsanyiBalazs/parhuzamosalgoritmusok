#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    int n = 20000;
    int db = 0;
    int prime=1;

    clock_t start,end;
    double timespent;

    FILE *fptr;
    fptr = fopen("timespentprimes.txt","a");

    if(fptr == NULL)
    {
      printf("Error!");
      return 1;
    }



    for(int k=1000 ;k<=n;k=k+1000){
    start=clock();
    for (int i = 2; i <= n; i++)
    {


        for ( int j = 2; j <= (i/2) ; j++)
        {

            if ( (i % j) == 0 )
            {
                prime=0;
                break;
            }

        }

        if (prime == 1)
        {
            db++;
        }
        prime = 1 ;
    }
    end = clock();
    printf("%d\n",db);
    timespent = ((double)(end-start))/ CLOCKS_PER_SEC;
    fprintf(fptr,"%lf %d\n",timespent,k);
    }


    fclose(fptr);
    printf("%d",db);
    return 0;
}
