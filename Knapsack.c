#include <stdio.h>

int main()
{
	int N,M,i,j,k;
	int need[500],value[500];
	int m[100001];
	scanf("%d%d",&N,&M);
	for(i=0;i<N;i++) scanf("%d%d",&need[i],&value[i]);
	for(i=0;i<=M;i++) m[i]=0;
	for(i=0;i<N;i++)
	{
		for(j=M;j>=0;j--)
		{
			if(j-need[i] >= 0)
			{
				k = m[j-need[i]] + value[i];
				if(k > m[j]) m[j]=k;
			}
		}
	}
	printf("%d\n",m[M]);
	return 0;
}
