#include <iostream>
#include <string>

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

int main(int argc, char *argv[])
{
	int now = dateToInt(3,14,2014);
	for(int i = 0; i < 365; i++)
	{
		int then = now + i;
		Date date = intToDate(then);
		cout << date.y << '-' << date.m << '-' << date.d << endl;
	}
	return 0;
}
