#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> Nb;

void solvecase(int casenum)
{
	printf("Case #%d:\n",casenum);
	int n;
	Nb nodes[100001];
	int color[100001];
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
		color[i] = 0;
	for(int i = 0; i < n-1; i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		nodes[a].push_back(b);
		nodes[b].push_back(a);
	}
	int m = 1;
	int q;
	scanf("%d",&q);
	for(int i = 0; i < q; i++)
	{
		int c,x,y;
		scanf("%d",&c);
		if(c == 1)
		{
			printf("%d\n",m);
		}
		else
		{
			scanf("%d%d",&x,&y);
			int smx = 0;
			int cx = color[x];
			for(int k = 0; k < nodes[x].size(); k++)
			{
				int b = nodes[x][k];
				int cc = color[b];
				if(cc==cx) smx++;
				if(cc==y) smx--;
			}
			color[x] = y;
			m += smx;
		}
	}
}

int main()
{
	int T;
	scanf("%d",&T);
	for(int t = 0; t < T; t++)
		solvecase(t+1);
	return 0;
}
