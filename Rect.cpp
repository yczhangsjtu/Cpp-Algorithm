#include <cstdio>
#include <map>

typedef struct Point
{
	int x,y;
} Point;

typedef struct Points
{
	int x1,y1,x2,y2;
} Points;

bool operator<(Point p1, Point p2)
{
	if(p1.x < p2.x) return true;
	if(p1.x > p2.x) return false;
	return p1.y < p2.y;
}

typedef map<Point,Points> M;

int main()
{
	int T,i,j,k;
	scanf("%d",&T);
	for(i=0;i<T;i++)
	{
		M m;
		int x1,y1,x2,y2;
		for(j=0;j<4;j++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		}
	}
	return 0;
}
