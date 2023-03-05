#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int random;
    double random2;
    int max = 1000;
    int min =500;
    double range = max - min;
    double div = RAND_MAX /range;

    srand(time(0));

    random = rand()%1000 + 500;


    random2 = min + (rand()/div);


    printf("A random szám: %d\n",random);
    printf("A random2 szám: %lf\n",random2);
    return 0;
}
