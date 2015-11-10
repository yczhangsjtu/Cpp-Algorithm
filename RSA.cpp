#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

typedef unsigned __int32 UINT;

typedef struct BigNum
{
	/*The integer of 1024 bits looks like:
	[b[31]][b[30]]...[b[2]][b[1]][b[0]]*/
	UINT b[32];
} BigNum;

BigNum Zero = {{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
}};

/**
 *  \brief Print an integer n
 *  
 *  \param [in] n integer to be printed
 *  \return Nothing
 *  
 */
void printNum(const BigNum & n, ios_base& (*b)(ios_base&))
{
	int i = 31;
	while(i > 0 && n.b[i] == 0) i--;
	for(;i >= 0;i--) cout << b << setw(9) << n.b[i];
}

/**
 *  \brief over load the operator + on BigNum
 *  
 */
BigNum operator+(const BigNum & n, UINT m)
{
	BigNum r = n;
	for(int i = 0; i < 32; i++)
	{
		if(r.b[i] <= (UINT)(-1) - m)
		{
			r.b[i] += m;
			return r;
		}
		else
		{
			r.b[i] += m;
			m = 1;
		}
	}
	return r;
}

/**
 *  \brief over load the operator - on BigNum
 *  
 */
BigNum operator-(const BigNum & n, UINT m)
{
	BigNum r = n;
	for(int i = 0; i < 32; i++)
	{
		if(r.b[i] >= m)
		{
			r.b[i] -= m;
			return r;
		}
		else
		{
			r.b[i] -= m;
			m = 1;
		}
	}
	return r;
}

/**
 *  \brief over load the operator -= on BigNum
 *  
 */
BigNum& operator-=(BigNum & n, UINT m)
{
	for(int i = 0; i < 32; i++)
	{
		if(n.b[i] >= m)
		{
			n.b[i] -= m;
			return n;
		}
		else
		{
			n.b[i] -= m;
			m = 1;
		}
	}
	return n;
}

/**
 *  \brief Shift an integer n right by 1 bit
 *  
 *  \param [in] n the integer to be shifted
 *  \return Nothing
 *  
 *  \details
 *  for i = 0 to 30 do
 *  	right shift the i'th integer;
 *  	copy the rightmost bit of the i+1'th integer to the left most bit of
 *  		the i'th integer;
 *  endfor
 *  right shift the 31'th integer
 */
void rightShift(BigNum & n)
{
	for(int i = 0; i < 30; i++)
	{
		n.b[i] >>= 1;
		n.b[i] |= (n.b[i+1] % 2) << 31;
	}
	n.b[31] >>= 1;
}

/**
 *  \brief For an integer n, find k>=0 and q odd so that n = 2^k q (q<<k)
 *  
 *  \param [in]  n The integer to be decomposited
 *  \param [out] k The power
 *  \param [out] q The odd number
 *  \return Nothing
 *  
 *  \details Copy n to q, shift q right until q is odd, count the shifts
 */
void twoPowerDecomposite(const BigNum & n, UINT & k, BigNum & q)
{
	q = n; // Copy n to q
	
	for(k = 0; k < 1024; k++)
	{
		if((q.b[0] % 2) == 1) return;
		rightShift(q);
	}
}

/**
 *  \brief Generate a random integer n that is less than m
 *  
 *  \param [in]  m upper bound
 *  \param [out] n the random integer
 *  \return Nothing
 *  
 */
void randNum(const BigNum & m, BigNum & n)
{
	int l;
	for(l = 31;l >= 0 && m.b[l] == 0;l--)
		n.b[l] = 0;
	if(l<0)
	{
		n = Zero;
		return;
	}
	while(true)
	{
		if(m.b[l]==(UINT)(-1)) n.b[l] = ((rand()<<16)+rand());
		else n.b[l] = (UINT)((rand()<<16)+rand()) % (m.b[l]+1);
		if(n.b[l] < m.b[l])
		{
			for(int i = 0; i < l; i++)
				n.b[i] = (rand()<<16)+rand();
			return;
		}
		else if(n.b[l] == m.b[l])
		{
			for(int i = l-1; i >= 0; i--)
			{
				n.b[i] = (rand()<<16)+rand();
				if(n.b[i] < m.b[i])
				{
					for(int j = 0; j < i; j++)
						n.b[j] = (rand()<<16)+rand();
					return;
				}
				else if(n.b[i] > m.b[i])
					break;
			}
		}
	}
}

/**
 *  \brief Test whether a number is an odd prime number
 *  
 *  \param [in] n The number to be tested
 *  \return If return false, n is not prime. Else, the result is inconclusive,
 *  but most probably n is a prime (by a really large probability)
 *  
 *  \details
 *  	1. Find intergers k, q, with k > 0, q odd, so that (n-1)=2^k q;
 *  	2. Select a random integer a, 1 < a < n-1;
 *  	3. if a^q mod n = 1 then return true ("inconclusive");
 *  	4. for j = 0 to k - 1 do
 *  			if a^(2^j q) mod n = n - 1 then return true ("inconclusive");
 *  	5. return false ("n is composite");
 */
bool Test(const BigNum & n)
{
	UINT   k;
	BigNum q, a;
	BigNum m = n-1;
	twoPowerDecomposite(m,k,q);
	if(k==0) return false; // k=1 means n is even, not possible to be odd prime
	m-=2;
	randNum(m,a);
	
}

int main()
{
	srand((UINT)time(0));
	BigNum a = {{0x000babab,0x00000001}};
	BigNum b;
	randNum(a,b);
	printNum(b,hex);
	cout << endl;
	randNum(a,b);
	printNum(b,hex);
	cout << endl;
	randNum(a,b);
	printNum(b,hex);
	cout << endl;
	randNum(a,b);
	printNum(b,hex);
	cout << endl;
	randNum(a,b);
	printNum(b,hex);
	cout << endl;
	randNum(a,b);
	printNum(b,hex);
	cout << endl;
	randNum(a,b);
	printNum(b,hex);
	cout << endl;
	
	return 0;
}
