#include <stdio.h>

typedef long long Int;

const Int mod = 19999997;

int main()
{
    Int N;
    scanf("%lld",&N);
    Int a[2];
    a[0] = 1;
    a[1] = 1;
    int k = 0;
    int i;
    for(i=0;i<N-1;i++)
    {
        a[k]=(a[k]+a[1-k])%mod;
        k=1-k;
    }
    printf("%lld\n",a[1-k]);
    return 0;
}
