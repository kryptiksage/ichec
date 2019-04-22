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
//search()
int search(int i, int n, int *a)
{
    int p = -1;
    for(int j=0; j<n; j++)
    {
        if(a[j] == i)
            return j;
        else if(a[j] > i)
            return p;
    }
    return p;
}
int main()
{
    int *p = randomarray(5, 5);
    for(int i=0; i<5; i++)
        printf("%i\n", p[i]);
    int a[10] = {1, 2, 3, 4, 5};
    printf("Index: %i\n", search(7, 5, a));
    return 0;
}