#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>

using namespace std;

// Divide and conquer algorithm: O(n log n)
int maxSubSeq(const vector<int> & input, int left, int right)
{
	assert(left >= 0);
	assert(right > left);
	assert(right <= input.size());
	if(right - left == 1) return input.at(left) > 0? input.at(left): 0;
	int mid = (right + left) / 2;
	int res1 = maxSubSeq(input, left, mid);
	int res2 = maxSubSeq(input, mid, right);
	int leftmax = 0, rightmax = 0;
	int sum = 0;
	for(int i = mid - 1; i >= left; i--)
	{
		sum += input.at(i);
		if(sum > leftmax) leftmax = sum;
	}
	sum = 0;
	for(int i = mid; i < right; i++)
	{
		sum += input.at(i);
		if(sum > rightmax) rightmax = sum;
	}
	int res3 = leftmax + rightmax;
	int res = res1;
	if(res2 > res) res = res2;
	if(res3 > res) res = res3;
	return res;
}

int maxSubSeq(const vector<int> & input)
{
	if(input.empty()) return 0;
	return maxSubSeq(input,0,input.size());
}

// Scan algorithm: O(n)
int maxSubSeq2(const vector<int> & input)
{
	int max = 0;
	int start = 0;
	int sum = 0;
	for(int i = 0; i < input.size(); i++)
	{
		sum += input.at(i);
		if(sum < 0)
		{
			start = i;
			sum = 0;
		}
		if(sum > max) max = sum;
	}
	return max;
}

int main(int argc, char *argv[])
{
	if(argc < 2) return -1;

	vector<int> seq;
	for(int i = 1; i < argc; i++)
		seq.push_back(atoi(argv[i]));
	cout << maxSubSeq(seq) << endl;
	cout << maxSubSeq2(seq) << endl;
	
	return 0;
}
