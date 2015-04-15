#include <iostream>

using namespace std;

void solvecase()
{
	int N, M;
	cin >> N >> M;
	int S[1000];
	int s = 0;
	int k = 0;
	bool r = true;
	for(int i = 0; i < N; i++)
	{
		int t;
		cin >> t;
		if(!r) continue;
		if(t <= k)
		{
			if(t == k)
			{
				//cout << "Letting " << k << " pass" << endl;
				k++;
				continue;
			}
			if(s <= 0 || S[s-1] != t)
			{
				/*
				if(s <= 0)
					cout << "Trying to pop empty stack" << endl;
				else
				{
					cout << "Train " << t << " is not at the front" << endl;
					for(int j = 0; j < s; j++)
						cout << S[j] << ' ' << endl;
				}
				*/
				r = false;
			}
			else
			{
				//cout << "Poping " << S[s-1] << endl;
				--s;
			}
		}
		else
		{
			while(k < t)
			{
				if(s >= M)
				{
					//cout << "Stack full" << endl;
					r = false;
					break;
				}
				else
				{
					// cout << "Pushing " << k << endl;
					S[s++] = k++;
				}
			}
			//cout << "Letting " << k << " pass" << endl;
			k++;
		}
	}
	if(r) cout << "YES" << endl;
	else cout << "NO" << endl;
}

int main()
{
	int T;
	cin >> T;
	for(int i = 0; i < T; i++)
		solvecase();
	return 0;
}
