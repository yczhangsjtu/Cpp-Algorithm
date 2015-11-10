#include <iostream>
#include <fstream>
#include <set>

using namespace std;

typedef set<int> Cand;

Cand fullCand()
{
	Cand cand;
	for(int i = 1; i <= 9; i++)
		cand.insert(i);
	return cand;
}

Cand singleCand(int i)
{
	Cand cand;
	cand.insert(i);
	return cand;
}

bool integerToCand(int I[9][9], Cand M[9][9])
{
	bool valid = true;
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(I[i][j]!=0)
			{
				Cand::iterator iter;
				if((iter=M[i][j].find(I[i][j]))!=M[i][j].end())
					M[i][j] = singleCand(I[i][j]);
				else
					valid = false;
			}
		}
	}
	return valid;
}

bool analyseCand(Cand M[9][9])
{
	bool changed = false;
	do
	{
	changed = false;
	for(int i0 = 0; i0 < 3; i0++)
	{
	if(changed) break;
	for(int i1 = 0; i1 < 3; i1++)
	{
		if(changed) break;
		int i = i0 * 3 + i1;
		for(int j0 = 0; j0 < 3; j0++)
		{
		if(changed) break;
		for(int j1 = 0; j1 < 3; j1++)
		{
			if(changed) break;
			int j = j0*3 + j1;
			if(M[i][j].size()==1)
			{
				int n = *M[i][j].begin();
				for(int k = 0; k < 9; k++)
				{
					if(changed) break;
					if(k != i)
					{
						int e = M[k][j].erase(n);
						if(e>0)
						{
							if(M[k][j].empty())
							{
								cout << "Invalid case! Location " << k << "," << j
									 << " has no candidate." << endl;
								cout << "After erasing " << n << endl;
								return false;
							}
							if(M[k][j].size()==1)
							{
								cout << "Location " << k << "," << j << " is "
									 << *M[k][j].begin() << endl;
							}
							changed = true;
							continue;
						}
					}
					if(k != j)
					{
						int e = M[i][k].erase(n);
						if(e>0)
						{
							if(M[i][k].empty())
							{
								cout << "Invalid case! Location " << i << "," << k
									 << " has no candidate." << endl;
								cout << "After erasing " << n << endl;
								return false;
							}
							if(M[i][k].size()==1)
							{
								cout << "Location " << i << "," << k << " is "
									 << *M[i][k].begin() << endl;
							}
							changed = true;
							continue;
						}
					}
				}
				for(int x = 0; x < 3; x++)
				{
					for(int y = 0; y < 3; y++)
					{
						int ii = i0*3+x;
						int jj = j0*3+y;
						if(ii!=i || jj!=j)
						{
							int e = M[ii][jj].erase(n);
							if(e>0)
							{
								if(M[ii][jj].empty())
								{
									cout << "Invalid case! Location " << ii 
										 << "," << jj << " has no candidate."
										 << endl;
									cout << "After erasing " << n << endl;
									return false;
								}
								if(M[ii][jj].size()==1)
								{
									cout << "Location " << ii << "," << jj
										 << " is " << *M[ii][jj].begin() << endl;
								}
								changed = true;
								continue;
							}
						}
					}
				}
			}
		}
		}
	}
	}
	
	for(int n = 1; n <= 9; n++)
	{
		if(changed) break;
		for(int i0 = 0; i0 < 9; i0++)
		{
			if(changed) break;
			int sum = 0; int j0 = 0;
			for(int j = 0; j < 9; j++)
			{
				if(changed) break;
				if(M[i0][j].find(n)!=M[i0][j].end())
				{
					sum++;
					j0 = j;
				}
			}
			if(sum==0)
			{
				cout << "Invalid case! Row " << i0 << " has no " << n << endl;
				return false;
			}
			else if(sum==1)
			{
				if(M[i0][j0].size()>1)
				{
					cout << "Location " << i0 << "," << j0 << " is "
						 << n << endl;
					M[i0][j0] = singleCand(n);
				}
			}
		}
		for(int j0 = 0; j0 < 9; j0++)
		{
			if(changed) break;
			int sum = 0; int i0 = 0;
			for(int i = 0; i < 9; i++)
			{
				if(M[i][j0].find(n)!=M[i][j0].end())
				{
					sum++;
					i0 = i;
				}
			}
			if(sum==0)
			{
				cout << "Invalid case! Column " << j0 << " has no " << n << endl;
				return false;
			}
			else if(sum==1)
			{
				if(M[i0][j0].size()>1)
				{
					cout << "Location " << i0 << "," << j0 << " is "
						 << n << endl;
					M[i0][j0] = singleCand(n);
					changed = true;
				}
			}
		}
		
		for(int i0 = 0; i0 < 3; i0++)
		{
			if(changed) break;
			for(int j0 = 0; j0 < 3; j0++)
			{
				if(changed) break;
				int sum = 0; int ii = 0, jj = 0;
				for(int i1 = 0; i1 < 3; i1++)
				{
					if(changed) break;
					for(int j1 = 0; j1 < 3; j1++)
					{
						if(changed) break;
						int i = i0*3+i1;
						int j = j0*3+j1;
						if(M[i][j].find(n)!=M[i][j].end())
						{
							sum++;
							ii = i;
							jj = j;
						}
					}
				}
				if(sum==0)
				{
					cout << "Invalid case! Square " << i0 << "," << j0
						 << " has no " << n << endl;
					return false;
				}
				else if(sum==1)
				{
					if(M[ii][jj].size()>1)
					{
						cout << "Location " << i0 << "," << j0 << " is "
							 << n << endl;
						M[ii][jj] = singleCand(n);
						changed = true;
					}
				}
			}
		}
	}
	
	} while(changed);
	
	return true;
}

void candToInteger(Cand M[9][9], int I[9][9])
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(M[i][j].size()==1)
				I[i][j] = *M[i][j].begin();
		}
	}
}


int main()
{
	int  I[9][9];
	Cand M[9][9];
	
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			I[i][j] = 0;
			M[i][j] = fullCand();
		}
	}
	
	ifstream fin("input.txt");
	if(fin)
	{
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				fin >> I[i][j];
				if(fin.eof()) break;
			}
			if(fin.eof()) break;
		}
		fin.close();
		integerToCand(I,M);
		analyseCand(M);
		candToInteger(M,I);
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				cout << I[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
	
	return 0;
}
