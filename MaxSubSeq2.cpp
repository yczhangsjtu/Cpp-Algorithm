#include <iostream>

using namespace std;

int main()
{
	int max = 0;
	int n;
	cin >> n;
	int a,b,c;
	cin >> a;
	b=c=a;
	for(int i = 1; i < n; i++)
	{
		cin >> a;
		b = c>b?a+c:a+b;
		if(b > max) max = b;
		c = a;
	}
	if(max > 0) cout << max << endl;
	else cout << "Game Over" << endl;
	return 0;
}
