#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
	int n;
	while(true)
	{
		if(scanf("%d",&n) < 1) break;
		int d[3000];
		bool b[3000];
		for(int i = 1; i < n; i++)
			b[i] = false;
		bool ans = true;
		for(int i = 0; i < n; i++)
		{
			scanf("%d",&d[i]);
			if(!ans) continue;
			if(i > 0)
			{
				int e = abs(d[i]-d[i-1]);
				if(e < 1 || e > n-1) ans = false;
				if(b[e]) ans = false;
				else b[e] = true;
			}
		}
		if(ans) printf("Jolly\n");
		else printf("Not jolly\n");
	}
	return 0;
}
