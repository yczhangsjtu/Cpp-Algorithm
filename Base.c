#include <stdio.h>
#include <math.h>

typedef long long Int;

int main()
{
	int T,t;
	scanf("%d",&T);
	for(t=0; t<T; t++)
	{
		Int N,M,A,B,u,v;
		Int sx=0, sy=0, sxx=0, syy=0;
		scanf("%lld%lld%lld%lld",&N,&M,&A,&B);
		for(u=0;u<A;u++)
		{
			Int x,y;
			scanf("%lld%lld",&x,&y);
			sx+=x;sy+=y;
			sxx+=x*x;syy+=y*y;
		}
		Int ax=sx/A, ay=sy/A;
		Int x0[4]={ax-1,ax,ax+1,ax+2};
		Int y0[4]={ay-1,ay,ay+1,ay+2};
		Int xs[4],ys[4];
		int k,k1,k2;
		for(k=0;k<4;k++)
		{
			xs[k] = A*x0[k]*x0[k]-2*sx*x0[k]+sxx;
			ys[k] = A*y0[k]*y0[k]-2*sy*y0[k]+syy;
		}
		Int b[4][4];
		for(k1=0;k1<4;k1++)
			for(k2=0;k2<4;k2++)
				b[k1][k2] = 200000000;
		for(v=0;v<B;v++)
		{
			Int x,y;
			scanf("%lld%lld",&x,&y);
			for(k1=0;k1<4;k1++)
				for(k2=0;k2<4;k2++)
				{
					int nn = abs(x-x0[k1])+abs(y-y0[k2]);
					if(nn<b[k1][k2])
						b[k1][k2]=nn;
				}
		}
		Int min = xs[0]+ys[0]+b[0][0];
		for(k1=0;k1<4;k1++)
			for(k2=0;k2<4;k2++)
			{
				if(xs[k1]+ys[k2]+b[k1][k2] < min)
					min = xs[k1]+ys[k2]+b[k1][k2];
			}
		printf("Case #%d: %lld\n",t+1,min);
	}
	return 0;
}
