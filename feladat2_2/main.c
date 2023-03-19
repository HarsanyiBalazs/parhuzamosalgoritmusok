#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(0));

    int n=10;
    int rndArray[n];
    int tombElem;
    int voltmar=0;
    int duplicateChance;
    int duplicateNumber;
    int uniquearr;


    /*
    for(int i=0;i<n;)
    {
        tombElem = rand();
        for(int j=0;j<i;j++)
        {
            if(rndArray[j] == tombElem)
            {
                voltmar=1;
                break;
            }
        }
        if(voltmar == 0)
        {
            rndArray[i]=tombElem;
            i++;
        }
        voltmar=0;
    }
    alapfeladat
    */


    for(int i=0;i<n;)
    {
        duplicateChance = rand()%(1+1);
        if((duplicateChance == 1) && (i != 0))
        {
            duplicateNumber = rand()%(i);
            rndArray[i] = rndArray[duplicateNumber];
            i++;
        }
        else
        {

            tombElem = rand();
            for(int j=0;j<i;j++)
            {
                if(rndArray[j] == tombElem)
                {
                    voltmar=1;
                    break;
                }
            }
            if(voltmar == 0)
            {
                rndArray[i]=tombElem;
                i++;
            }
            voltmar=0;
        }
    }

    uniquearr = uniquearray(rndArray,n);
    if(uniquearr==1){printf("all values are unique\n");}
    else{printf("not all values are unique\n");}

    printarray(rndArray,n);

    return 0;

}

void printarray(int tomb[],int size)
{
    for(int i=0;i < size;i++)
    {
        printf("%d\n",tomb[i]);
    }
    return;
}

int uniquearray(int tomb[],int size)
{
    // O(n^2) a bonyolultság
    for(int i=0; i<size-1;i++)
    {
        for(int j= i+1;j<size;j++)
        {
            if(tomb[i]==tomb[j])
            {
                return 0;
            }
        }
    }
    return 1;
}
