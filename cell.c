#include<stdio.h>
#include<stdlib.h>
struct cell
{
    int content;
    struct cell *next;
}*c;
//to create new cell
void newcell(int n)
{
    struct cell *t = (struct cell*)malloc(sizeof(struct cell));
    t->content = n;
    t->next = NULL;   
    c = t;
}
//to push to front
struct cell *push(struct cell **t, int n)
{
    struct cell *tmp = (struct cell*)malloc(sizeof(struct cell));
    tmp->content = n;
    tmp->next = *t;
    *t=tmp;
    return tmp;    
}
//to deallocate list
int deallocate(struct cell **t)
{
    int n=0;
    struct cell *tmp;
    while(*t)
    {
        n++;
        tmp=*t;
        *t = (*t)->next;
        free(tmp);
    } 
    return n;   
}
//to find length of list
int countcells(struct cell *t)
{
    struct cell *tmp = t;
    int n = 0;
    while(tmp)
    {
        n++;
        tmp = tmp->next;
    }
    return n;
}
//to pop from rear
int pop(struct cell *t)
{
    struct cell *tmp = t;
    struct cell *s;
     while(tmp->next)
    {
        s = tmp;
        tmp = tmp->next;
    }
    int n = tmp -> content;
    s->next=NULL;
    free(tmp);
    return n;
}
//print list in order
void printlist(struct cell *t)
{
    struct cell *tmp = t;
    printf("The list: ");
    while(tmp)
    {
        printf("%i\n", tmp->content);
        tmp = tmp->next;
    }
}
//print list in reverse order
void printlistreverse(struct cell *t)
{
    struct cell *tmp = t;
    int l = countcells(tmp), a[50];
    for(int i=l-1; i>=0; i--)
    {
        a[i] = tmp->content;
        tmp = tmp->next;        
    }
    printf("The list: ");
    for(int i=0; i<l; i++)
        printf("%i\n", a[i]);
}
//sum of elements
int sumit(struct cell *t)
{
    struct cell *tmp = t;
    int sum = 0;
    while(tmp)
    {
        sum += tmp->content;
        tmp = tmp->next;
    }
    return sum;
}
int main()
{
    c=NULL;
    struct cell *t;
    //1
    newcell(36);
    t = push(&c, 1);
    t = push(&c, 6);
    t = push(&c, 12);
    t = push(&c, 4);
    printf("Pop: %i\n", pop(c));
    printf("Sum: %i\n", sumit(c));
    printf("Length: %i\n", countcells(c));
    printlist(c);
    printlistreverse(c);
    deallocate(&c);
    return 0;
}