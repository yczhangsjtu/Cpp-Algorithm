#include <cstdio>
#include <set>

using namespace std;

int main()
{
	int n,Q;
	scanf("%d%d",&n,&Q);
	int as[100000],bs[10000];
	for(int i = 0; i < n-1; i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		as[i] = a; bs[i] = b;
	}
	for(int i = 0; i < Q; i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		int S = r-l+1;
		for(int j=0; j < n-1; j++)
		{
			if(as[j]>=l && as[j]<=r && bs[j]>=l && bs[j] <= r) S--;
		}
		printf("%d\n",S);
	}
	return 0;
}
