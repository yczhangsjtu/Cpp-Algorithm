#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

int main()
{
	char buff[256];
	cin.getline(buff,256);
	int N = atoi(buff);
	for(int i = 0; i < N; i++)
	{
		// Read line by line
		cin.getline(buff,256);
		// These following codes are to split the line into
		// three parts by spaces
		char *p = &buff[0];
		char *str[3];
		char **ps = &str[0];
		*ps++ = &buff[0];
		while(*p != '\0')
		{
			if(*p == ' ')
			{
				*p = '\0';
				*ps ++ = p+1;
			}
			p++;
		}
		////////////////////////////////////////////////////////////////////////
		
		// Now let's begin the algorithm part
		// First, transform the original digits into integers
		int num[100];
		int R = strlen(str[0]);
		int S = strlen(str[1]);
		int T = strlen(str[2]);
		for(int j = 0; j < R; j++)
		{
			for(int k = 0; k < S; k++)
			{
				if(str[1][k] == str[0][j])
				{
					num[j] = k;
					break;
				}
			}
		}
		// Now, the source language is useless (except the number of digits)
		// Then, we need to build a transform table that maps the powers of
		// the source language into an integer array of the other language
		vector<int> tt[R];
		tt[0].push_back(1); // The power 0 is definitely 1
		for(int j = 1; j < R; j++)
		{
			tt[j] = tt[j-1]; // First copy the last one
			for(int k = 0; k < tt[j].size(); k++) tt[j].at(k) *= S;// Multiply S
			// "Flatten" the number
			for(int k = 0; k < tt[j].size(); k++)
			{
				if(tt[j].at(k) >= T) // Any overflow
				{
					if(k == tt[j].size() - 1) tt[j].push_back(0);
					tt[j].at(k+1) += tt[j].at(k) / T; // Overflow to higher
					tt[j].at(k) %= T;
				}
				// cout << tt[j].at(k) << ' ';
			}
			// cout << endl;
		}
		
		// Now, done with the transform table
		// Linear combine the transform table entries by the digits
		vector<int> result(tt[R-1].size());
		for(int j = 0; j < R; j++)
		{
			for(int k = 0; k < tt[j].size(); k++)
				result.at(k) += tt[j].at(k) * num[R-1-j];
		}
		// "Flatten" the number
		for(int k = 0; k < result.size(); k++)
		{
			if(result.at(k) >= T) // Any overflow
			{
				if(k == result.size() - 1) result.push_back(0);
				result.at(k+1) += result.at(k) / T; // Overflow to higher
				result.at(k) %= T;
			}
		}
		cout << "Case #" << i+1 << ": ";
		for(int j = result.size() - 1; j >= 0; j--)
			cout << str[2][result.at(j)];
		cout << endl;
	}
	return 0;
}
