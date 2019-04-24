#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//return array with random values within limit
int* randomarray(int n, int max)
{
    int *a = (int *)malloc(sizeof(int));
    srand(time(NULL));//set random seed value according to time
    for(int i=0; i<n; )
    {
        int num = rand()%max, f=0; //num = random value 
        for(int j=0; j<i; j++)
            if(a[j] == num)
                f = 1; //checks if random value exists inside a[]
        if(f == 0)
        {
            a[i] = num; //if not in a[] then a[i] = num
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
            return p; //if arr[j] > i then no need to check further for i in arr[]
    }
    return p;
}
//chopsearch()
int chopsearch(int i, int n, int *arr, int amin, int amax)
{
    srand(time(NULL));
    int x = amin + rand()%(amax-amin+1); //x = random chop value used to divide arr[]
    if((amax-amin) < 0)
        return -1;
    else //similar to binary search 
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
                    return j; //check if i is present before a[x] and returns index of i i.e. j
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
            return arr[i]; //returns a[i] if a[i] has n/2 values less than it in the array

    }
}
//mediansort()
void mediansort(int n, int *cycle, int *arr, int *sorted)
{
    if(n<1)
        return;
    int m = median(n, arr); //median value of arr[]
    int pos;
    for(int i=0; i<n; i++)
        if(arr[i] == m)
        {
            pos = i; //finds position of median in arr[]
            break;
        }
    for(int i=pos; i<n-1; i++)
        arr[i] = arr[i+1]; //shifts values of arr[] 1 step backward
    if(*cycle == 0)
        sorted[*cycle] = m; //stores the first value of sorted
    else if(m >= sorted[*cycle-1])
        sorted[*cycle] = m; //stores value of median value greater than sorted[*cycle] to end of sorted[]
    else if(m < sorted[*cycle-1])
    {
        for(int i = *cycle ; i > 0; i--)
            sorted[i] = sorted[i-1];
        sorted[0] = m;
    }  // inserts median value less than sorted[*cycle] to beginning of sorted[]
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