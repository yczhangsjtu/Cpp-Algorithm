#include <iostream>
#include <vector>

void swap(int* array, int a, int b)
{
	int tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}
 
 void sort(int* array, int left, int right)
 {
	 if(left >= right-1) return;
	 int mid = (left+right)/2;
	 swap(array,mid,left);
	 int p = left, q = right;
	 while(p < q-1)
	 {
		 if(array[p] > array[p+1]) swap(array,p++,p+1);
		 else swap(array,p+1,--q);
	 }
	 sort(array,left,p);
	 sort(array,p+1,right);
 }

using namespace std;

int findlastless(int* array, int t, int left, int right)
{
	while(left < right)
	{
		if(array[left] < t && array[left+1] >= t) return left;
		if(array[right-1] < t) return right - 1;
		if(array[left] >= t) return -1;
		int mid = (left+right)/2;
		if(array[mid]<t){left = mid;right--;}
		else right = mid;
	}
	return -1;
}

int main()
{
	int N, M;
	cin >> N >> M;
	int h[10000], l[10000];
	for(int i = 0; i < N; i++)
		cin >> h[i];
	for(int i = 0; i < M; i++)
		cin >> l[i];
	sort(h,0,N);
	sort(l,0,M);
	int q = M;
	int sum = 0;
	for(int p = N-1; p >= 0; p--)
	{
		q = findlastless(l,h[p],0,q);
		if(q >= 0) sum++;
	}
	cout << sum + N << endl;
	return 0;
}
