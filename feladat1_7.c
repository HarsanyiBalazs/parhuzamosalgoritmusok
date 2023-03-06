#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 30;
    int db = 0;
    int prime=1;

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
    
    printf("%d",db);
    return 0;
}