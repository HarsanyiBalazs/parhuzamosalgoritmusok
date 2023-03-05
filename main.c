#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc > 3)
    {
        printf("too many args");
        return 1;
    }

    int minval = atoi(argv[1]);
    int maxval = atoi(argv[2]);
    int value;

    srand(time(0));

    value = rand()%(maxval-minval+1) + minval ;

    printf("value = %d \n",value);
    return 0;
}
