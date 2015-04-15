#include <iostream>
#include <map>

using namespace std;

int main()
{
	int V,N;
	map<int,int> w;
	cin >> V >> N;
	for(int i = 0; i < N; i++)
	{
		int ww,vv;
		cin >> ww >> vv;
		if(w.find(ww) == w.end() || w[ww]<vv)
			w[ww] = vv;
	}
	int X[10001];
	X[0] = 0;
	for(int i = 1; i <= V; i++)
	{
		map<int,int>::iterator iter;
		int max = 0;
		for(iter = w.begin(); iter!=w.end(); iter++)
		{
			int ww = iter->first;
			int vv = iter->second;
			if(i < ww) continue;
			if(X[i-ww]+vv > max) max = X[i-ww]+vv;
		}
		X[i] = max;
	}
	cout << X[V] << endl;
	return 0;
}
