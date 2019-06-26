#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
omp_lock_t lock;
int main(int argc, char **argv){
    int niter, i, j;
    long seed;
    double count;
    double x,y,z,pi;
    extern float ran2();
    niter=10000;
    count=0;
    #pragma omp critical
    for(i=1;i<=niter;i++){
        #pragma ordered
        seed=i;
        x=ran2(&seed);  
        y=ran2(&seed);
        z=x*x+y*y;
        if(z<1){
            count+=1;
        }
    }   
    pi=count*4.0/niter;
    printf("The value of pi is %8.14f\n",pi);
    return 0;
}
#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

float ran2(long *idum)
{
    omp_init_lock(&lock);
    int j;
    long k;
    static long idum2=123456789;
    static long iy=0;
    static long iv[NTAB];
    float temp;
    if (*idum <= 0) {
        if (-(*idum) < 1) *idum=1;
        else *idum = -(*idum);
            idum2=(*idum);
        for (j=NTAB+7;j>=0;j--) {
            omp_set_lock(&lock);
            k=(*idum)/IQ1;
            *idum=IA1*(*idum-k*IQ1)-k*IR1;
            if (*idum < 0) *idum += IM1;
            if (j < NTAB) iv[j] = *idum;
            omp_unset_lock(&lock);
        }
        iy=iv[0];
    }
    k=(*idum)/IQ1;
    *idum=IA1*(*idum-k*IQ1)-k*IR1;
    if (*idum < 0) *idum += IM1;
    k=idum2/IQ2;
    idum2=IA2*(idum2-k*IQ2)-k*IR2;
    if (idum2 < 0) idum2 += IM2;
    j=iy/NDIV;
    iy=iv[j]-idum2;
    iv[j] = *idum;
    if (iy < 1) iy += IMM1;
    omp_destroy_lock(&lock);
    if ((temp=AM*iy) > RNMX) return RNMX;
    else return temp;
}
/* (C) Copr. 1986-92 Numerical Recipes Software "!15L1. */
