#include <iostream>

using namespace std;

void postOrder(int r,int* L, int* R)
{
	if(r == -1) return;
	postOrder(L[r],L,R);
	postOrder(R[r],L,R);
	cout << r << ' ';
}

int main()
{
	int n;
	cin >> n;
	int L[30001];
	int R[30001];
	int P[30001];
	P[1] = 1;
	for(int i = 0; i < n; i++)
	{
		int x,y,z;
		cin >> x >> y >> z;
		L[x] = y;
		R[x] = z;
		P[y] = P[x]*2;
		P[z] = P[y]+1;
	}
	for(int i = 1; i <= n; i++)
		cout << P[i] << ' ';
	cout << endl;
	postOrder(1,L,R);
	cout << endl;
	return 0;
}
