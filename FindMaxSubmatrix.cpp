#include <iostream>

using namespace std;

int sum(int* A, int s, int l)
{
	int S = 0;
	for(int i = 0; i < l; i++)
		S += A[s+i];
	return S;
}

int sum(int **A, int c, int s, int l)
{
	int S = 0;
	for(int i = 0; i < l; i++)
		S += A[s+i][c];
	return S;
}

int main()
{
	int** A = new int*[1000];
	for(int i = 0; i < 1000; i++)
		A[i] = new int[1000];
	int** S = new int*[1000];
	for(int i = 0; i < 1000; i++)
		S[i] = new int[1000];
	int** T = new int*[1000];
	for(int i = 0; i < 1000; i++)
		T[i] = new int[1000];

	int L,W;
	cin >> L >> W;
	for(int i = 0; i < L; i++)
		for(int j = 0; j < W; j++)
			cin >> A[i][j];
	int a,b;
	cin >> a >> b;
	for(int i = 0; i < L; i++)
		for(int j = 0; j < W-b+1; j++)
		{
			if(j == 0) S[i][j] = sum(A[i],0,b);
			else S[i][j] = S[i][j-1] - A[i][j-1] + A[i][j+b-1];
		}
	int max = 0;
	for(int j = 0; j < W-b+1; j++)
		for(int i = 0; i < L-a+1; i++)
		{
			if(i == 0) T[i][j] = sum(S,j,0,a);
			else T[i][j] = T[i-1][j] - S[i-1][j] + S[i+a-1][j];
			if(T[i][j] > max) max = T[i][j];
		}
	cout << max << endl;
	for(int i = 0; i < 1000; i++)
	{
		delete[] A[i];
		delete[] S[i];
		delete[] T[i];
	}
	delete[] A;
	delete[] S;
	delete[] T;
	return 0;
}
