/*
 * The classical KMP algorithm for string match
 */
#include <cstdio>

using namespace std;

void calcnext(char* par, int *NEXT)
{
	NEXT[0] = -1;
	NEXT[1] = 0;
	for(int i = 2; par[i]!='\0'; i++)
	{
		int q = NEXT[i-1];
		while(q>=0 && par[q+1]!=par[i]) q=NEXT[q];
		if(q==-1) NEXT[i] = 0;
		else NEXT[i] = q+1;
	}
}

int main()
{
	int N;
	scanf("%d",&N);
	for(int i = 0; i < N; i++)
	{
		char par[10002];
		int NEXT[10001];
		scanf("%s",par+1);
		calcnext(par,NEXT);
		int q=0, s=0;
		char c;
		while((c=getchar())<'A' || c>'Z')
			;
		ungetc(c,stdin);
		while(true)
		{
			c = getchar();
			if(par[q+1] == '\0') s++;
			if(c<'A' || c>'Z') break;
			while(q >= 0 && c != par[q+1]) q = NEXT[q];
			q++;
		}
		printf("%d\n",s);
	}
	return 0;
}
