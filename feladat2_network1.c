#include <stdio.h>
#include <stdlib.h>


int main()
{
    int vertices;
    int edges;
    int number=50;
    double ratio_edges;
    double ratio_vertices;
    int sum;
    FILE *fptr;

    fptr = fopen("ratios.txt","w");

    if(fptr == NULL)
    {
      printf("Error!");   
      return 1;             
    }

    fprintf(fptr,"vertices edges\n");


    for (int n = 1; n <= number; n++)
    {
        edges=n*(n-1)+n*(n-1);
        vertices=n*n;
        sum=edges+vertices;
        ratio_edges=(double)edges/sum;
        ratio_vertices=(double)vertices/sum;

        printf("n=%d vertices=%d edges=%d ratio vertices:edges %lf:%lf\n",n,vertices,edges,ratio_vertices,ratio_edges);
        fprintf(fptr,"%lf %lf\n",ratio_vertices,ratio_edges);

    }

    fclose(fptr);

    return 0;
}