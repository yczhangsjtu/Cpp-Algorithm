#include <stdio.h>
#include <string.h>

const int mod = 100007;

int main()
{
	int T,t;
	scanf("%d",&T);
	for(t=0;t<T;t++)
	{
		char buf[1001];
		int r[1000][1000];
		scanf("%s",buf);
		int l=strlen(buf);
		int k,d;
		for(k=0;k<l;k++)
			r[k][k] = 1;
		for(k=0;k<l-1;k++)
			r[k][k+1] = buf[k]==buf[k+1]?3:2;
		for(d=2; d<=l-1; d++)
		{
			for(k=0;k+d<l;k++)
			{
				r[k][k+d] = r[k][k+d-1]+r[k+1][k+d]-r[k+1][k+d-1];
				if(buf[k]==buf[k+d]) r[k][k+d]+=r[k+1][k+d-1]+1;
				r[k][k+d]%=mod;
			}
		}
		printf("Case #%d: %d\n",t+1,r[0][l-1]);
	}
	return 0;
}
