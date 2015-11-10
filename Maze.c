#include <stdio.h>

int main()
{
	int n,i,j;
	int d[100][100];
	int m[100][100];
	scanf("%d",&n);
	for(i=0;i<n;i++)
		for(j=0;j<=i;j++)
			scanf("%d",&d[i][j]);
	for(j=n-1;j>=0;j--)
		m[n-1][j]=d[n-1][j];
	for(i=n-2;i>=0;i--)
		for(j=0;j<=i;j++)
			m[i][j]=(m[i+1][j]>m[i+1][j+1]?m[i+1][j]:m[i+1][j+1])+d[i][j];
	printf("%d\n",m[0][0]);
	return 0;
}
