#include <iostream>

#define max(a,b,c) ((a)>(b)?((a)>(c)?(a):(c)):((b)>(c)?(b):(c)))
#define argmin(a,b,c) ((a)<=(b)?((a)<=(c)?(0):(2)):((b)<=(c)?(1):(2)))

typedef long int Int;

using namespace std;

int main()
{
	int N;
	cin >> N;
	Int a[100000];
	for(int i = 0; i < N; i++)
		cin >> a[i];

	Int b[3][100000];
	Int s[3] = {0,0,0};
	Int m[3];
	for(int i = 0; i < N; i++)
	{
		b[i%3][i/3] = a[i];
		if(i/3 > 0) b[i%3][i/3] += b[i%3][i/3-1];
		if(i+3 < N) s[i%3] += b[i%3][i/3];
	}
	m[(N-3)%3] = (N-3)/3;
	m[(N-2)%3] = (N-2)/3;
	m[(N-1)%3] = (N-1)/3;
	cout << s[0]+s[1]+s[2] << ' ' << max(b[0][m[0]],b[1][m[1]],b[2][m[2]]) << endl;

	m[0] = m[1] = m[2] = 0;
	b[0][0] = b[1][0] = b[2][0] = 0;
	s[0] = s[1] = s[2] = 0;
	for(int i = 0; i < N; i++)
	{
		int k = argmin(b[0][m[0]],b[1][m[1]],b[2][m[2]]);
		m[k]++;
		b[k][m[k]] = a[i] + b[k][m[k]-1];
		s[k] += b[k][m[k]];
	}
	s[0] -= b[0][m[0]];
	s[1] -= b[1][m[1]];
	s[2] -= b[2][m[2]];
	cout << s[0]+s[1]+s[2] << ' ' << max(b[0][m[0]],b[1][m[1]],b[2][m[2]]) << endl;

	return 0;
}
