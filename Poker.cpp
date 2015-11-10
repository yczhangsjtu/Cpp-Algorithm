#include <cstdio>
#include <vector>

using namespace std;

typedef unsigned long long Int;

Int sum(int v[],int b)
{
}

void solvecase(int index)
{
	printf("Case #%d: ",index);
	int N;
	scanf("%d",&N);
	char buf[3];
	int v[14];
	for(int i = 0; i < 14; i++)
		v[i] = 0;
	for(int i = 0; i < N; i++)
	{
		scanf("%s",buf);
		int j = 0;
		if(buf[0] == 'T') j=10;
		else if(buf[0]=='J') j==11;
		else if(buf[0]=='Q') j==12;
		else if(buf[0]=='K') j==13;
		else if(buf[0]=='A') j==1;
		else j = buf[0]-'0';
		v[j]++;
	}
	printf("%llu\n",sum(v));
}

int main()
{
	int T;
	scanf("%d",&T);
	for(int i = 0; i < T; i++)
		solvecase(i+1);
	return 0;
}
