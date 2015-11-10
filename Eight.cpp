#include <cstdio>
#include <map>

using namespace std;

typedef struct U
{
	int g;
	map<int,int> nbs;
} U;

void solvecase(int index)
{
	printf("Case #%d:\n",index);
	int N,M,Q;
	U u[100001];
	scanf("%d%d%d",&N,&M,&Q);
	for(int i = 1; i <= N; i++)
		scanf("%d",&u[i].g);
	int ba = 0;
	for(int i = 0; i < M; i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		u[x].nbs[y] = z;
		u[y].nbs[x] = z;
		if(u[x].g != u[y].g) ba+=z;
	}
	for(int i = 0; i < Q; i++)
	{
		int c;
		scanf("%d",&c);
		if(c == 1)
		{
			int x;
			scanf("%d",&x);
			u[x].g ^= 1;
			for(map<int,int>::iterator iter = u[x].nbs.begin();
			iter!=u[x].nbs.end(); iter++)
			{
				int idx = iter->first;
				int im = iter->second;
				if(u[idx].g==u[x].g) ba -= im;
				else ba += im;
			}
		}
		else if(c == 2)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			if(u[x].nbs.find(y)==u[x].nbs.end())
			{
				u[x].nbs[y]=0;
				u[y].nbs[x]=0;
			}
			int im = u[x].nbs[y];
			if(u[x].g != u[y].g) ba += (z-im);
			u[x].nbs[y] = u[y].nbs[x] = z;
		}
		else
		{
			printf("%d\n",ba);
		}
	}
}

int main()
{
	int T;
	scanf("%d",&T);
	for(int i = 0; i < T; i++)
		solvecase(i+1);
	return 0;
}
