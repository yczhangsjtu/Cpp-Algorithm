#include <iostream>
#include <string>
 
using namespace std;
 
int main()
{
	int N;
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		string s;
		cin >> s;
		int a = 0;
		for(int j = 0; j < s.length(); j++)
		{
			if(s[j] == '(') a++;
			if(s[j] == ')') a--;
			if(a < 0) break;
		}
		if(a != 0) cout << "NO" << endl;
		else cout << "YES" << endl;
	}
	return 0;
}
