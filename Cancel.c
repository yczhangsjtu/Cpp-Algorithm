#include <stdio.h>
#include <string.h>

int main()
{
	int N,i,j;
	scanf("%d",&N);
	char buf[101];
	int f[101];
	for(i = 0; i < N; i++)
	{
		scanf("%s",buf);
		int ol = strlen(buf);
		int p=0,q=0;
		while(buf[q]!='\0')
		{
			if(p-1<0 || buf[p-1]!=buf[q])
				buf[p++]=buf[q++];
			else if(p-1>=0)
			{
				p--;
				while(buf[q+1]==buf[q]) q++;
				q++;
			}
		}
		buf[p++]='\0';

		int l = strlen(buf);
		int max = 1;
		f[0] = 1;
		int r = 0, rr = 0;
		if(l==0) max = 0;
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
				if(buf[j+k]==buf[j-k])
					f[j]+=2;
				else
					break;
			}
			rr = j+f[j]/2;
			if(f[j]>max) max=f[j];
		}
		printf("%d\n",ol-l+max+1);
	}
	return 0;
}
