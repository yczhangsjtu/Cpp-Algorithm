#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int N,i;
	scanf("%d",&N);
	char buf[1000001];
	for(i = 0; i < N; i++)
	{
		scanf("%s",buf);
		int l = strlen(buf);
		int *f = (int*)malloc(sizeof(int)*(2*l+1));
		l = 2*l+1;
		int max = 1;

		f[0] = 1;
		int r = 0, rr = 0, j;
		for(j = 0; j<l; j++)
		{
			f[j] = 1;
			if(r > j)
			{
				int rf = 2*rr-j;
				if(rf-f[rf]/2 > rr-f[rr]/2)
				{
					f[j] = f[rf];
					continue;
				}
				f[j] = (r-j)*2+1;
			}
			int k = r-j+1;
			if(k<=0) k=1;
			for(;k<=j;k++)
			{
				char a=(j+k)%2==0?'0':buf[(j+k)/2];
				char b=(j-k)%2==0?'0':buf[(j-k)/2];
				if(a==b)
					f[j]+=2;
				else
					break;
			}
			rr = j+f[j]/2;
			if(f[j]>max) max=f[j];
		}
		printf("%d\n",(max-1)/2);
		free(f);
	}
	return 0;
}
