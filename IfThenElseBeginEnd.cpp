#include <iostream>
#include <string>
 
using namespace std;
const int BEGIN = 0;
const int END = 1;
const int IF = 2;
const int THEN = 3;
const int ELSE = 4;
int main()
{
	int N;
	cin >> N;
	int stack[100];
	int p = 0;
	bool YES = true;
	bool prevIf = false;
	for(int i = 0; i < N; i++)
	{
		string s;
		cin >> s;
		if(s=="begin")
		{
			stack[p++] = BEGIN;
			prevIf = false;
		}
		else if(s=="end")
		{
			while(p>=1 && stack[p-1]==THEN) p--;
			if(p >= 1 && stack[p-1]==BEGIN) p--;
			else YES = false;
			prevIf = false;
		}
		else if(s=="if")
		{
			prevIf = true;
			stack[p++] = IF;
		}
		else if(s=="then")
		{
			if(p >= 1 && stack[p-1]==IF && prevIf) stack[p-1]=THEN;
			else YES = false;
			prevIf = false;
		}
		else if(s=="else")
		{
			if(p>=1 && stack[p-1]==THEN) p--;
			else YES = false;
			prevIf = false;
		}
	}
	while(p>=1 && stack[p-1]==THEN) p--;
	if(p>0) YES = false;
	if(YES) cout << "YES" << endl;
	else cout << "NO" << endl;
	
	return 0;
}
