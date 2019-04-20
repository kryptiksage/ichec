#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//return array with random values within limit
int* randomarray(int n, int max)
{
    int *a = (int *)malloc(sizeof(int));
    srand(time(NULL));
    for(int i=0; i<n; i++)
        a[i] = rand()%max;
    return a;
}
//
void main()
{
    int *p = randomarray(5, 5);
    for(int i=0; i<5; i++)
        printf("%i\n", p[i]);
    return 0;
}