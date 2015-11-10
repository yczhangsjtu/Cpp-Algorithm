#include <cstdio>

using namespace std;

void fill(char m[251][251], int X, int Y, char C)
{
	if(m[Y][X] == C) return;
	char o = m[Y][X];
	m[Y][X] = C;
	if(Y > 0 && m[Y-1][X] == o) fill(m,X,Y-1,C);
	if(X > 0 && m[Y][X-1] == o) fill(m,X-1,Y,C);
	if(m[Y+1][X] == o) fill(m,X,Y+1,C);
	if(m[Y][X+1] == o) fill(m,X+1,Y,C);
}

int main()
{
	char m[251][251];
	int M,N;
	char L[2],C[2];
	char name[1000];
	int X1,Y1,X2,Y2;
	while(true)
	{
		scanf("%s",L);
		if(L[0]=='X') break;
		if(L[0]=='I')
		{
			scanf("%d%d",&M,&N);
			for(int i = 0; i < N; i++)
			{
				for(int j = 0; j < M; j++)
					m[i][j] = 'O';
				m[i][M] = '\0';
			}
			for(int i = 0; i < M+1; i++)
				m[N][i] = '\0';
		}
		else if(L[0]=='C')
		{
			for(int i = 0; i < N; i++)
			{
				for(int j = 0; j < M; j++)
					m[i][j] = 'O';
				m[i][M] = '\0';
			}
			for(int i = 0; i < M+1; i++)
				m[N][i] = '\0';
		}
		else if(L[0]=='L')
		{
			scanf("%d%d%s",&X1,&Y1,C);
			m[Y1-1][X1-1] = C[0];
		}
		else if(L[0]=='V')
		{
			scanf("%d%d%d%s",&X1,&Y1,&Y2,C);
			for(int i = Y1; i <= Y2; i++)
				m[i-1][X1-1] = C[0];
		}
		else if(L[0]=='H')
		{
			scanf("%d%d%d%s",&X1,&X2,&Y1,C);
			for(int i = X1; i <= X2; i++)
				m[Y1-1][i-1] = C[0];
		}
		else if(L[0]=='K')
		{
			scanf("%d%d%d%d%s",&X1,&Y1,&X2,&Y2,C);
			for(int i = X1; i <= X2; i++)
				for(int j = Y1; j <= Y2; j++)
					m[j-1][i-1] = C[0];
		}
		else if(L[0]=='F')
		{
			scanf("%d%d%s",&X1,&Y1,C);
			fill(m,X1-1,Y1-1,C[0]);
		}
		else if(L[0]=='S')
		{
			scanf("%s",name);
			printf("%s\n",name);
			for(int i = 0; i < N; i++)
				printf("%s\n",m[i]);
		}
	}
	return 0;
}
