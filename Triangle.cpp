#include <iostream>

using namespace std;

void solvecase(int index)
{
	int x1, y1, x2, y2, x3, y3;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	int t = (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
	cout << "Case #" << index << ": ";
	if(t == 0)
	{
		 cout << "not a triangle" << endl;
		return;
	}
	int s1 = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	int s2 = (x1-x3)*(x1-x3)+(y1-y3)*(y1-y3);
	int s3 = (x3-x2)*(x3-x2)+(y3-y2)*(y3-y2);
	if(s1 == s2 || s2 == s3 || s1 == s3)
		cout << "isosceles ";
	else
		cout << "scalene ";
	if(s1 + s2 == s3 || s1+s3==s2 || s2+s3==s1)
		cout << "right ";
	else if(s1 + s2 < s3 || s1+s3<s2 || s2+s3<s1)
		cout << "obtuse ";
	else
		cout << "acute ";
	cout << "triangle" << endl;
}

int main()
{
	int N;
	cin >> N;
	for(int i = 0; i < N; i++)
		solvecase(i+1);
	return 0;
}
