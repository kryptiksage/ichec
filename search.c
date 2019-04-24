#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//return array with random values within limit
int* randomarray(int n, int max)
{
    int *a = (int *)malloc(sizeof(int));
    srand(time(NULL));
    for(int i=0; i<n; )
    {
        int num = rand()%max, f=0;
        for(int j=0; j<i; j++)
            if(a[j] == num)
                f = 1;
        if(f == 0)
        {
            a[i] = num;
            i++;
        }
    }
    return a;
}
//search()
int search(int i, int n, int *arr)
{
    int p = -1;
    for(int j=0; j<n; j++)
    {
        if(arr[j] == i)
            return j;
        else if(arr[j] > i)
            return p;
    }
    return p;
}
//chopsearch()
int chopsearch(int i, int n, int *arr, int amin, int amax)
{
    srand(time(NULL));
    int x = amin + rand()%(amax-amin+1);
    if((amax-amin) < 0)
        return -1;
    else
    {
        if(i<arr[x])
            return chopsearch(i, n, arr, amin, x-1);
        else if(i>arr[x])
            return chopsearch(i, n, arr, x+1, amax);
        else
        {
            for(int j=amin; j<=x; j++)
            {
                if(arr[j] == i)
                    return j;
            }
        }
    }
    
}
//median()
int median(int n, int *arr)
{
    for(int i=0; i<n; i++)
    {
        int  c = 0;
        for(int j=0; j<n; j++)
            if(arr[j]<arr[i])
                c++;
        if(c == n/2)
            return arr[i];

    }
}
//mediansort()
void mediansort(int n, int *cycle, int *arr, int *sorted)
{
    if(n<1)
        return;
    int m = median(n, arr);
    int pos;
    for(int i=0; i<n; i++)
        if(arr[i] == m)
        {
            pos = i;
            break;
        }
    for(int i=pos; i<n-1; i++)
        arr[i] = arr[i+1];
    if(*cycle == 0)
        sorted[*cycle] = m;
    else if(m >= sorted[*cycle-1])
        sorted[*cycle] = m;
    else if(m < sorted[*cycle-1])
    {
        for(int i = *cycle ; i > 0; i--)
            sorted[i] = sorted[i-1];
        sorted[0] = m;
    }  
    *cycle = *cycle + 1;
    mediansort(n-1, cycle, arr, sorted);

}
//benchmark_naive()
int benchmark_naive(int n, int max, int s, int mult)
{
    clock_t t;
    t = clock();
    for(int i=1; i<=mult; i++)
    {
        if(i%1000==0)
        {
            int *arr = randomarray(n, max), *sorted = (int*)malloc(sizeof(int)), c=0;
            mediansort(n, &c, arr, sorted);  
            int item = search(s, n, sorted);       
        }
    }    
    t = clock() - t;
    double ti = (double)t;
    return ti;
}
//benchmark_chop()
int benchmark_chop(int n, int max, int s, int mult)
{
    clock_t t;
    t = clock();
    for(int i=1; i<=mult; i++)
    {
        if(i%1000==0)
        {
            int *arr = randomarray(n, max), *sorted = (int*)malloc(sizeof(int)), c=0;
            mediansort(n, &c, arr, sorted);  
            int item = chopsearch(s, n, sorted, 0, n-1);
        }
    }    
    t = clock() - t;
    double ti = (double)t;
    return ti;
}
int main()
{
    int n, max, c=0;
    printf("Enter size of array: ");
    scanf("%i", &n);
    printf("Enter maximum value: ");
    scanf("%i", &max);
    int *arr = randomarray(n, max), *sorted = (int*)malloc(sizeof(int));
    printf("\nUnsorted array: \n");
    for(int i=0; i<n; i++)
        printf("%i,\n", arr[i]);
    mediansort(n, &c, arr, sorted);
    printf("Sorted array: \n");
    for(int i=0; i<n; i++)
        printf("%i,\n", sorted[i]);    

    //question 6 - i
    printf("1.a: %d\n",benchmark_naive(2000, 10000, 10, 1000000));
    printf("1.b: %d\n",benchmark_chop(2000, 10000, 10, 1000000));
    printf("2.a: %d\n",benchmark_naive(2000, 10000, 5000, 1000000));
    printf("2.b: %d\n",benchmark_chop(2000, 10000, 5000, 1000000));
    printf("3.a: %d\n",benchmark_naive(2000, 10000, 9000, 1000000));
    printf("3.b: %d\n",benchmark_chop(2000, 10000, 9000, 1000000));
    return 0;
}