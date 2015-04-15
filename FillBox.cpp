#include <iostream>
#include <set>
#include <list>

using namespace std;

typedef struct Pair
{
	int i;
	int j;
	Pair(int a,int b):i(a),j(b){}
} Pair;

bool operator<(Pair a, Pair b)
{
	if(a.i < b.i) return true;
	if(a.i > b.i) return false;
	return a.j < b.j;
}

bool surround(int i, int j, int L, int M[100][100])
{
	if(M[i][j] != 0) return false;
	if(i > 0 && M[i-1][j]==1) return true;
	if(j > 0 && M[i][j-1]==1) return true;
	if(i < L-1 && M[i+1][j]==1) return true;
	if(j < L-1 && M[i][j+1]==1) return true;
	return false;
}

int main()
{
	int L;
	cin >> L;
	int M[100][100];
	for(int i = 0; i < L; i++)
		for(int j = 0; j < L; j++)
			cin >> M[i][j];
	set<Pair> e;
	for(int i = 0; i < L; i++)
		for(int j = 0; j < L; j++)
		{
			if(M[i][j]==0) e.insert(Pair(i,j));
		}
	int count = 0;
	while(!e.empty())
	{
		list<Pair> l;
		set<Pair>::iterator iter;
		for(iter = e.begin(); iter!=e.end(); iter++)
		{
			int i = iter->i, j = iter->j;
			if(surround(i,j,L,M)) l.push_back(Pair(i,j));
		}
		while(!l.empty())
		{
			Pair p = l.back();
			l.pop_back();
			M[p.i][p.j] = 1;
			e.erase(p);
		}
		count++;
	}
	cout << count << endl;
	return 0;
}
