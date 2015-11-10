#include <cstdio>

using namespace std;

int main()
{
	int n;
	while(true)
	{
		scanf("%d",&n);
		if(n == 0) break;
		int s[1000];
		int sum = 0;
		for(int i = 0; i < n; i++)
		{
			int a,b;
			scanf("%d.%d",&a,&b);
			s[i] = a*100+b;
			sum += s[i];
		}
		int avg = sum/n;
		int m = sum-avg*n;
		int r = 0, c = 0;
		for(int i = 0; i < n; i++)
		{
			if(s[i]>avg)
			{
				r += s[i]-avg;
				c++;
			}
		}
		if(m < c) r -= m;
		else r -= c;
		printf("$%d.%d%d\n",r/100,(r%100)/10,r%10);
	}
	return 0;
}
