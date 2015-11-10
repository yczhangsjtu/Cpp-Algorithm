#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;


typedef unsigned int UINT;

/**
 *  \brief For an integer n, find k>=0 and q odd so that n = 2^k q (q<<k)
 *  
 *  \param [in]  n The integer to be decomposited
 *  \param [out] k (pointer to)The power
 *  \param [out] q (pointer to)The odd number
 *  \return Nothing
 *  
 *  \details Copy n to q, shift q right until q is odd, count the shifts
 */
void twoPowerDecomposite(UINT n, UINT * k, UINT * q)
{
	*q = n; // Copy n to q
	
	for(*k = 0; *k < 32; (*k)++)
	{
		if((*q % 2) == 1) return;
		*q >>= 1;
	}
}

// Return an unsigned integer of 32 bit
UINT randInt()
{
	return ((UINT)rand() << 24) ^ ((UINT)rand()<<12) ^ (UINT)rand();
}



/**
 *  \brief Return a*b mod n
 *  
 *  \param [in] a
 *  \param [in] b
 *  \param [in] n
 *  \return a*b mod n
 *  
 *  \details Omitted
 */
UINT timeMode(UINT a, UINT b, UINT n)
{
	UINT f = 0;
	if(n == 0) return 0;
	
	for(UINT i = 32; i>0; i--)
	{
		if(2*f<f)
			f = f-(n-f);
		else
			f = (2*f)%n;
			
		if((b >> (i-1))%2)
		{
			if((f+a)<f)
				f = f-(n-a);
			else
				f = (f+a) % n;
		}
	}
	return f;
}

/**
 *  \brief Return a^b mod n
 *  
 *  \param [in] a
 *  \param [in] b
 *  \param [in] n
 *  \return a^b mod n
 *  
 *  \details Omitted
 */
UINT expMode(UINT a, UINT b, UINT n)
{
	UINT f = 1;
	if(n == 0) return 0;
	
	for(UINT i = 32; i>0; i--)
	{
		f = timeMode(f,f,n);
		if((b >> (i-1))%2) f = timeMode(f,a,n);
	}
	return f;
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
bool Test(UINT n)
{
	UINT k;
	UINT q, a;
	UINT m = n-1;
	if(n < 3) return false;
	if(n == 3) return true;
	twoPowerDecomposite(m,&k,&q);
	if(k==0) return false; // k=0 means n is even, not possible to be odd prime
	for(UINT i=0; i<10; i++)
	{
		bool isPrime = false;
		int  qq = q;
		a = (randInt() % (n-3)) + 2;
		if(expMode(a,qq,n)==1) continue;
		for(UINT j = 0; j < k; j++, qq<<=1)
		{
			if(expMode(a,qq,n)==n-1)
			{
				isPrime = true;
				break;
			}
		}
			
		if(!isPrime) return false;
	}
	return true;
}

/**
 *  \brief Generate a prime less than or equal to max, greater than or equal to
 *         min
 *  
 *  \return return a prime number between 0 and 2^32-1
 *  
 *  \details Details
 */
UINT genPrime(UINT min, UINT max)
{
	if(max == 0) return 0;
	if(min>=max) return Test(max) ? max: 0;
	
	UINT p;
	for(int i = 0; i < 1000; i++)
	{
		p = ((randInt()%(max-min))+min) | 1; // make it an odd number
		if(Test(p)) return p;
	}
	return 0;
}

//Greatest common dividor
UINT gcd(UINT a,UINT b)
{
	if(a==b || b==0) return a;
	if(a==0) return b;
	if(a>b) return gcd(a%b,b);
	else	return gcd(b%a,a);
}

// Get an integer prime to n
UINT getPrimeTo(UINT n, UINT min, UINT max)
{
	if(n < 3) return 1;
	if(max == 0) return 0;
	if(min>=max) return gcd(max,n)<=1 ? max: 0;
	
	UINT p;
	for(int i = 0; i < 1000; i++)
	{
		p = ((randInt()%(max-min))+min) | 1; // make it an odd number
		if(gcd(p,n)==1) return p;
	}
	return 0;
}

// Find b such that ab mod n = 1
UINT modeInverse(UINT a, UINT n)
{
	if(a == 0 || n == 0) return 0;
	int t = 0, newt = 1, r = n, newr = a;
	while(newr != 0)
	{
		int q = r / newr;
		int tmp = t;
		t = newt;
		newt = tmp - q * newt;
		tmp = r;
		r = newr;
		newr = tmp - q * newr;
	}
	if( r > 1 ) return 0;
	if(t < 0) t += n;
	return t;
}

int main()
{
	// Initiate pseudo random generator
	srand((unsigned)time(0));
	
	int p, q, n, phi, e, d;
	// 1. Generate two prime numbers
	p = genPrime(100,65500);
	do
		q = genPrime(100,65500);
	while (q==p);
	cout << "Get two prime numbers: " << p << " and " << q << endl;
	// 2. Calculate their product
	n = p*q;
	cout << "n = " << n << endl;
	// 3. Calculate phi(n)=(p-1)(q-1)
	phi = (p-1)*(q-1);
	cout << "phi(n) = " << phi << endl;
	// 4. Generate a number relatively prime to phi(n)
	e = getPrimeTo(phi,3,phi);
	cout << "Get e relatively prime to phi(n): e = " << e << endl;
	// 5. Get d such that de mod phi(n) = 1
	d = modeInverse(e,phi);
	cout << "Get d such that ed mod phi(n) = 1: d = " << d << endl;
	
	while(true)
	{
		char m;
		int c;
		cout << "Input a char: " << endl;
		cin >> m;
		cout << "After encryption: " << endl;
		c = expMode((UINT)m,e,n);
		cout << c << endl;
		cout << "After decryption: " << endl;
		m = expMode(c,d,n);
		cout << m << endl;
	}
	
	return 0;
}
