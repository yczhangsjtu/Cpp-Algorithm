#include <cstdio>
#include <algorithm>
#include <set>
#include <list>

using namespace std;

set<int> Primes;

void solvecase(int casenum)
{
	printf("Case #%d: ",casenum);
	int N;
	scanf("%d",&N);
	set<int> nums;
	for(int i = 0; i < N; i++)
	{
		int n;
		scanf("%d",&n);
		nums.insert(n);
	}
	int s = 0;
	while(!nums.empty())
	{
		int t = *nums.begin();
		nums.erase(t);
		list<int> visited;
		list<bool> red;
		visited.push_back(t);
		red.push_back(true);
		int nred = 1, nblack = 0;
		while(!visited.empty())
		{
			int tt = visited.front(); visited.pop_front();
			bool rr = red.front(); red.pop_front();
			for(set<int>::iterator iter=Primes.begin();iter!=Primes.end();iter++)
			{
				int p = *iter;
				int tp = t*p;
				if(nums.find(tp)!=nums.end())
				{
					nums.erase(tp);
					visited.push_back(tp);
					red.push_back(!rr);
					if(rr) nred++;
					else nblack++;
				}
			}
		}
		int max = nred>nblack?nred:nblack;
		s += max;
	}
	printf("%d\n",s);
}

int main()
{
	int T;
	scanf("%d",&T);
	bool primes[500001];
	for(int i = 0; i < 500001; i++)
		primes[i] = true;
	primes[1]=false;
	for(int i = 2; i < 750; i++)
	{
		if(!primes[i]) continue;
		for(int j = 2*i; j<500001; j+=i)
			primes[j] = false;
	}
	for(int i = 2; i < 500001; i++)
		if(primes[i]) Primes.insert(i);
	for(int i = 0; i < T; i++)
		solvecase(i+1);
	return 0;
}
