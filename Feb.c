#include <stdio.h>
#include <string.h>

int run(int year)
{
	return year%4==0 && !(year%100==0 && year%400!=0);
}

int countmp(int a, int b, int k)
{
	a-=(a-1)%k;
	b-=(b%k-1);
	return (b-a)/k;
}

int countrun(int y1, int y2)
{
	return countmp(y1,y2,4)-countmp(y1,y2,100)+countmp(y1,y2,400);
}

int getmonth(char *month)
{
	if(month[0]=='J')
	{
		if(month[1]=='a') return 1;
		if(month[1]=='u')
		{
			if(month[2]=='n') return 6;
			if(month[2]=='l') return 7;
			return 0;
		}
		return 0;
	}
	if(month[0]=='F') return 2;
	if(month[0]=='M')
	{
		if(month[2]=='r') return 3;
		if(month[2]=='y') return 5;
		return 0;
	}
	if(month[0]=='A')
	{
		if(month[1]=='p') return 4;
		if(month[1]=='u') return 8;
		return 0;
	}
	if(month[0]=='S') return 9;
	if(month[0]=='O') return 10;
	if(month[0]=='N') return 11;
	if(month[0]=='D') return 12;
	return 0;
}

int main()
{
	int T,t;
	scanf("%d",&T);
	for(t=0; t<T; t++)
	{
		char month[20];
		int d1,d2,y1,y2,m1,m2;
		scanf("%s%d,%d",month,&d1,&y1);
		m1 = getmonth(month);
		scanf("%s%d,%d",month,&d2,&y2);
		m2 = getmonth(month);
		if(run(y1) && m1>2) y1++;
		if(run(y2) && !(m2>2 || (m2==2 && d2==29))) y2--;
		printf("Case #%d: %d\n",t+1,countrun(y1,y2));
	}
	return 0;
}
