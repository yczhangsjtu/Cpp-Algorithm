#include <iostream>

using namespace std;

typedef struct Date
{
	int m;
	int d;
	int y;
} Date;

int dateToInt(int m, int d, int y)
{
	return 1461 * (y + 4800 + (m - 14) / 12) / 4 +
		   367 * (m - 2 - (m - 14) / 12 * 12) / 12 -
		   3 * ((y + 4900 + (m - 14) / 12) / 100) / 4 +
		   d - 32075;
}

Date intToDate(int jd)
{
	int x, n, i, j, d, m, y;

	x = jd + 68569;
	n = 4 * x / 146097;
	x -= (146097 * n + 3) / 4;
	i = (4000 * (x + 1)) / 1461001;
	x -= 1461 * i / 4 - 31;
	j = 80 * x / 2447;
	d = x - 2447 * j / 80;
	x = j / 11;
	m = j + 2 - 12 * x;
	y = 100 * (n - 49) + i + x;
	Date date = {m, d, y};
	return date;
}

void solvecase()
{
	int y1,m1,d1,y2,m2,d2;
	cin >> y1;
	cin.get();
	cin >> m1;
	cin.get();
	cin >> d1;
	cin >> y2;
	cin.get();
	cin >> m2;
	cin.get();
	cin >> d2;
	int k1 = dateToInt(m1,d1,y1);
	int k2 = dateToInt(m2,d2,y2);
	int l16 = k1+(5-(k1+0)%7);
	int l15 = k1+(5-(k1+1)%7);
	int l26 = k2+(6-(k2+1)%7);
	int l25 = k2+(6-(k2+2)%7);
	int w5 = (l25-l15)/7;
	int w6 = (l26-l16)/7;

	int s = 0;
	for(int y = y1; y <= y2; y++)
	{
		int yd = dateToInt(1,1,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
		yd = dateToInt(5,1,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
		yd = dateToInt(5,2,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
		yd = dateToInt(5,3,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
		yd = dateToInt(10,1,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
		yd = dateToInt(10,2,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
		yd = dateToInt(10,3,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
		yd = dateToInt(10,4,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
		yd = dateToInt(10,5,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
		yd = dateToInt(10,6,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
		yd = dateToInt(10,7,y);
		if(yd >= k1 && yd <= k2 && yd%7!=5 && yd%7!=6) s++;
	}
	cout << (k2+1-k1)-w5-w6-s << endl;
}

int main()
{
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
		solvecase();
	return 0;
}
