#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Int;

using namespace std;

Int mergesort(vector<Int> &v, Int left, Int right)
{
	if(right <= left+1) return 0;
	if(right == left+2)
	{
		if(v[left]>v[right-1])
		{
			Int tmp = v[left];
			v[left] = v[right-1];
			v[right-1] = tmp;
			return 1;
		}
		return 0;
	}
	Int mid = (left+right)/2;
	Int l = mergesort(v,left,mid);
	Int r = mergesort(v,mid,right);
	Int s = 0;
	Int p = left, q = mid;
	Int* w = new Int[right-left];
	Int c = 0;
	while(p < mid || q < right)
	{
		if(p < mid && q < right)
		{
			if(v[p] <= v[q])
			{
				w[c++] = v[p++];
			}
			else
			{
				while(v[p] > v[q] && q < right)
				{
					w[c++] = v[q++];
					s += (mid-p);
				}
			}
		}
		else if(p < mid)
		{
			while(p < mid) w[c++] = v[p++];
		}
		else if(q < right)
		{
			if(v[p] <= v[q])
			{
				while(q < right) w[c++] = v[q++];
				break;
			}
			else
			{
				while(q < right && v[p] > v[q])
				{
					w[c++] = v[q++];
					s++;
				}
			}
		}
	}
	Int t = s + l + r;
	for(Int i = left; i < right; i++)
		v[i] = w[i-left];
	delete[]w;
	return t;
}

int main()
{
	Int N;
	cin >> N;
	vector<Int> a(N);
	for(Int i = 0; i < N; i++)
		cin >> a[i];
	cout << mergesort(a,0,a.size()) << endl;
	return 0;
}
