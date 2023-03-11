#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int number = atoi(argv[2]);
    int numberhelp=number;
    int minval = atoi(argv[3]);
    int maxval = atoi(argv[4]);
    FILE *fptr;
    FILE *fptrtime;
    int numbers[number*20];


    clock_t startrand,endrand,startwrite,endwrite;
    double timespent1,timespent2;

    srand(time(0));
    fptr = fopen(argv[1],"w");

    if(fptr == NULL)
    {
      printf("Error!");
      return 1;
    }

    fptrtime = fopen("data.txt","a");

    if(fptrtime == NULL)
    {
      printf("Error!");
      return 1;
    }

    for(int j=number;j<=(numberhelp*20);j=j+numberhelp)
    {

        startrand=clock();

        for (int i = 0; i < number; i++)
        {

            numbers[i] = rand()%(maxval-minval+1) + minval ;

        }


        endrand=clock();
        timespent1 = ((double)(endrand-startrand))/ CLOCKS_PER_SEC;

        startwrite=clock();

        for (int i = 0; i < number; i++)
        {

            fprintf(fptr," %d ",numbers[i]);

        }


        endwrite=clock();
        timespent2 = ((double)(endwrite-startwrite))/CLOCKS_PER_SEC;

        fprintf(fptrtime,"%d %lf %lf\n",number,timespent1,timespent2);

        number=number+numberhelp;



    }

   fclose(fptrtime);
   fclose(fptr);
   return 0;
}
