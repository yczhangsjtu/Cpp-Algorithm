#include <cstdio>

using namespace std;

void solvecase(int n, int m, int testcase)
{
	if(testcase > 1) printf("\n");
	printf("Field #%d:\n",testcase);
	char buf[100][101];
	char res[100][101];
	for(int i = 0; i < n; i++)
		scanf("%s",buf[i]);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(buf[i][j]=='*') res[i][j]='*';
			else
			{
				int s = 0;
				if(i > 0 && buf[i-1][j]=='*') s++;
				if(i < n-1 && buf[i+1][j]=='*') s++;
				if(j > 0 && buf[i][j-1]=='*') s++;
				if(j < m-1 && buf[i][j+1]=='*') s++;
				if(i > 0 && j > 0 && buf[i-1][j-1]=='*') s++;
				if(i < n-1 && j > 0 && buf[i+1][j-1]=='*') s++;
				if(i > 0 && j < m-1 && buf[i-1][j+1]=='*') s++;
				if(i < n-1 && j < m-1 && buf[i+1][j+1]=='*') s++;
				res[i][j] = s+'0';
			}
		}
		res[i][m] = '\0';
		printf("%s\n",res[i]);
	}
}

int main()
{
	int n,m,i=1;
	while(true)
	{
		scanf("%d%d",&n,&m);
		if(n == 0 || m == 0) break;
		solvecase(n,m,i);
		i++;
	}
}
