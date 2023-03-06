#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int number = atoi(argv[2]);
    int minval = atoi(argv[3]);
    int maxval = atoi(argv[4]);
    FILE *fptr;
    int numbers[number];

    srand(time(0));

    for (int i = 0; i < number; i++)
    {
        
        numbers[i] = rand()%(maxval-minval+1) + minval ;

    }
    

    fptr = fopen(argv[1],"w");

    if(fptr == NULL)
    {
      printf("Error!");   
      return 1;             
    }

   for (int i = 0; i < number; i++)
   {
    
        fprintf(fptr," %d ",numbers[i]);

   }
   fclose(fptr); 
   return 0;
}
