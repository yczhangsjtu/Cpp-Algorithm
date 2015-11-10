#include <iostream>
#include <cstring>

using namespace std;

typedef unsigned __int64 block;
typedef unsigned __int32 hblock;
typedef unsigned int uint;
typedef unsigned char uchar;

const uint nRounds = 16; // DES needs 16 rounds

void printCharInHex(char c);

///////////////////////Data tables//////////////////////////////////////////////

uint schShft[] = {
	1, 1, 2, 2, 2, 2, 2, 2,
	1, 2, 2, 2, 2, 2, 2, 1
};

uint PermutationP[][8] = {
	{16 ,7 ,20 ,21 ,29 ,12 ,28 ,17},
	{1 ,15 ,23 ,26 ,5 ,18 ,31 ,10 },
	{2 ,8 ,24 ,14 ,32 ,27 ,3 ,9   },
	{19 ,13 ,30 ,6 ,22 ,11 ,4 ,25 }
};

uint Sbox[][4][16] ={
{{14 ,4 ,13 ,1 ,2 ,15 ,11 ,8 ,3 ,10 ,6 ,12 ,5 ,9 ,0 ,7},
{0 ,15 ,7 ,4 ,14 ,2 ,13 ,1 ,10 ,6 ,12 ,11 ,9 ,5 ,3 ,8},
{4 ,1 ,14 ,8 ,13 ,6 ,2 ,11 ,15 ,12 ,9 ,7 ,3 ,10 ,5 ,0},
{15 ,12 ,8 ,2 ,4 ,9 ,1 ,7 ,5 ,11 ,3 ,14 ,10 ,0 ,6 ,13}},

{{15 ,1 ,8 ,14 ,6 ,11 ,3 ,4 ,9 ,7 ,2 ,13 ,12 ,0 ,5 ,10},
{3 ,13 ,4 ,7 ,15 ,2 ,8 ,14 ,12 ,0 ,1 ,10 ,6 ,9 ,11 ,5},
{0 ,14 ,7 ,11 ,10 ,4 ,13 ,1 ,5 ,8 ,12 ,6 ,9 ,3 ,2 ,15},
{13 ,8 ,10 ,1 ,3 ,15 ,4 ,2 ,11 ,6 ,7 ,12 ,0 ,5 ,14 ,9}},

{{10 ,0 ,9 ,14 ,6 ,3 ,15 ,5 ,1 ,13 ,12 ,7 ,11 ,4 ,2 ,8},
{13 ,7 ,0 ,9 ,3 ,4 ,6 ,10 ,2 ,8 ,5 ,14 ,12 ,11 ,15 ,1},
{13 ,6 ,4 ,9 ,8 ,15 ,3 ,0 ,11 ,1 ,2 ,12 ,5 ,10 ,14 ,7},
{1 ,10 ,13 ,0 ,6 ,9 ,8 ,7 ,4 ,15 ,14 ,3 ,11 ,5 ,2 ,12}},

{{7 ,13 ,14 ,3 ,0 ,6 ,9 ,10 ,1 ,2 ,8 ,5 ,11 ,12 ,4 ,15},
{13 ,8 ,11 ,5 ,6 ,15 ,0 ,3 ,4 ,7 ,2 ,12 ,1 ,10 ,14 ,9},
{10 ,6 ,9 ,0 ,12 ,11 ,7 ,13 ,15 ,1 ,3 ,14 ,5 ,2 ,8 ,4},
{3 ,15 ,0 ,6 ,10 ,1 ,13 ,8 ,9 ,4 ,5 ,11 ,12 ,7 ,2 ,14}},

{{2 ,12 ,4 ,1 ,7 ,10 ,11 ,6 ,8 ,5 ,3 ,15 ,13 ,0 ,14 ,9},
{14 ,11 ,2 ,12 ,4 ,7 ,13 ,1 ,5 ,0 ,15 ,10 ,3 ,9 ,8 ,6},
{4 ,2 ,1 ,11 ,10 ,13 ,7 ,8 ,15 ,9 ,12 ,5 ,6 ,3 ,0 ,14},
{11 ,8 ,12 ,7 ,1 ,14 ,2 ,13 ,6 ,15 ,0 ,9 ,10 ,4 ,5 ,3}},

{{12 ,1 ,10 ,15 ,9 ,2 ,6 ,8 ,0 ,13 ,3 ,4 ,14 ,7 ,5 ,11},
{10 ,15 ,4 ,2 ,7 ,12 ,9 ,5 ,6 ,1 ,13 ,14 ,0 ,11 ,3 ,8},
{9 ,14 ,15 ,5 ,2 ,8 ,12 ,3 ,7 ,0 ,4 ,10 ,1 ,13 ,11 ,6},
{4 ,3 ,2 ,12 ,9 ,5 ,15 ,10 ,11 ,14 ,1 ,7 ,6 ,0 ,8 ,13}},

{{4 ,11 ,2 ,14 ,15 ,0 ,8 ,13 ,3 ,12 ,9 ,7 ,5 ,10 ,6 ,1},
{13 ,0 ,11 ,7 ,4 ,9 ,1 ,10 ,14 ,3 ,5 ,12 ,2 ,15 ,8 ,6},
{1 ,4 ,11 ,13 ,12 ,3 ,7 ,14 ,10 ,15 ,6 ,8 ,0 ,5 ,9 ,2},
{6 ,11 ,13 ,8 ,1 ,4 ,10 ,7 ,9 ,5 ,0 ,15 ,14 ,2 ,3 ,12}},

{{13 ,2 ,8 ,4 ,6 ,15 ,11 ,1 ,10 ,9 ,3 ,14 ,5 ,0 ,12 ,7},
{1 ,15 ,13 ,8 ,10 ,3 ,7 ,4 ,12 ,5 ,6 ,11 ,0 ,14 ,9 ,2},
{7 ,11 ,4 ,1 ,9 ,12 ,14 ,2 ,0 ,6 ,10 ,13 ,15 ,3 ,5 ,8},
{2 ,1 ,14 ,7 ,4 ,10 ,8 ,13 ,15 ,12 ,9 ,0 ,3 ,5 ,6 ,11}}
};

uint InitialPermute[][8] =
{{58,50,42,34,26,18,10,2},
{60,52,44,36,28,20,12,4},
{62,54,46,38,30,22,14,6},
{64,56,48,40,32,24,16,8},
{57,49,41,33,25,17,9,1 },
{59,51,43,35,27,19,11,3},
{61,53,45,37,29,21,13,5},
{63,55,47,39,31,23,15,7}};

uint InverseInitialPermute[][8] =
{{40,8,48,16,56,24,64,32},
{39,7,47,15,55,23,63,31},
{38,6,46,14,54,22,62,30},
{37,5,45,13,53,21,61,29},
{36,4,44,12,52,20,60,28},
{35,3,43,11,51,19,59,27},
{34,2,42,10,50,18,58,26},
{33,1,41,9,49,17,57,25 }};

uint Permutation1[][8] =
{{57,49,41,33,25,17,9},
{1,58,50,42,34,26,18},
{10,2,59,51,43,35,27},
{19,11,3,60,52,44,36},
{63,55,47,39,31,23,15},
{7,62,54,46,38,30,22},
{14,6,61,53,45,37,29},
{21,13,5,28,20,12,4}};

uint Permutation2[][8] = 
{{14,17,11,24,1,5,3,28},
{15,6,21,10,23,19,12,4},
{26,8,16,7,27,20,13,2},
{41,52,31,37,47,55,30,40},
{51,45,33,48,44,49,39,56},
{34,53,46,42,50,36,29,32}};

////////////////////////////////////////////////////////////////////////////////

///////////////Bit operations////////////////////////

// Set the m'th bit of char a to be the n'th bit of char b
int getBit(char &a, uint m, char b, uint n)
{
	uchar model1 = (uchar)0x01, model2 = (uchar)0x01;
	model1 <<= n, model2 <<= m, model2 = ~model2;
	model1 &= b; // Get the n'th bit of b
	model1 >>= n;
	model1 <<= m;
	a &= model2; // Set the target bit to 0
	a |= model1; // Set the target bit to the desired bit
	
	if(model1==0) return 0;
	else return 1;
}

/////////////////////////////////////////////////////

// 32 bits swap
void swap(char str1[], char str2[], uint len)
{
	for(uint i = 0; i < 4; i++)
	{
		char tmp = str1[i];
		str1[i] = str2[i];
		str2[i] = tmp;
	}
}

void initialPermutate(char text[8])
{
	char buf[8];
	for(uint i = 0; i < 8; i++)
	{
		for(uint j = 0; j < 8; j++)
		{
			uint  m = InitialPermute[i][j] - 1;
			uint ix = m / 8;
			uint iy = m % 8;
			getBit(buf[i],j,text[ix],iy);
		}
	}
	memcpy(text,buf,8);
}

void inverseInitialPermutate(char text[8])
{
	char buf[8];
	for(uint i = 0; i < 8; i++)
	{
		for(uint j = 0; j < 8; j++)
		{
			uint  m = InverseInitialPermute[i][j] - 1;
			uint ix = m / 8;
			uint iy = m % 8;
			getBit(buf[i],j,text[ix],iy);
		}
	}
	memcpy(text,buf,8);
}

// Permute 1, choose from 64 bits key to 56 bits
void permuteChooseKey(const char key[8],char newKey[8])
{
	for(uint i = 0; i < 8; i++)
	{
		for(uint j = 0; j < 7; j++)
		{
			uint  m = Permutation1[i][j] - 1;
			uint ix = m / 8;
			uint iy = m % 8;
			getBit(newKey[i],j,key[ix],iy);
		}
	}
}

// Permute 2, choose from 56 bits key to 48 bits
void permute2(const char key[8], char K[8])
{
	for(uint i = 0; i < 8; i++)
	{
		for(uint j = 0; j < 6; j++)
		{
			uint  n = i * 6 + j;
			uint ix = n / 8;
			uint iy = n % 8;
			uint  m = Permutation2[ix][iy] - 1;
			uint jx = m / 7;
			uint jy = m % 7;
			getBit(K[i],j,key[jx],jy);
		}
	}
}

// Expand 32 bits to 48 bits, only the lower 6 bits are used
void expand(const char text[], char expansion[8])
{
	for(uint i = 0; i < 4; i++)
	{
		// Split the 8 bits char into two 4 bits 0-1-string
		// abcdefgh -> ***abcd* ***efgh*
		expansion[2*i] = text[i] << 1;
		expansion[2*i+1] = text[i] >> 3;
	}
	// Expansion
	// ***abcd* ***efgh* -> **iabcdj **kefghl
	for(uint i = 0; i < 7; i++)
	{
		getBit(expansion[i],5,expansion[i+1],1);
		getBit(expansion[i+1],0,expansion[i],4);
	}
	getBit(expansion[7],5,expansion[0],1);
	getBit(expansion[0],0,expansion[7],4);
}

// Only the lower 6 bits is used in the targets or the keys
void Xor48(char target[8], const char key[8])
{
	for(uint i = 0; i < 8; i++)
		target[i] ^= key[i];
}

void Xor32(char target[4], const char key[])
{
	for(uint i = 0; i < 4; i++)
		target[i] ^= key[i];
}

// For every char, only use lower 6 bits, abcdef from higher to lower
// the result is Sbox[index][af][bcde], which is four bits
// Two four-bit result form a new char
void SBox(const char orig[8], char newbits[4], uint index)
{
	for(uint i = 0; i < 8; i+=2)
	{
		char i1 = 0, i2 = 0;
		getBit(i1,1,orig[i],5);
		getBit(i1,0,orig[i],0);
		getBit(i2,3,orig[i],4);
		getBit(i2,2,orig[i],3);
		getBit(i2,1,orig[i],2);
		getBit(i2,0,orig[i],1);
		uchar lower = Sbox[index][i1][i2];
		getBit(i1,1,orig[i+1],5);
		getBit(i1,0,orig[i+1],0);
		getBit(i2,3,orig[i+1],4);
		getBit(i2,2,orig[i+1],3);
		getBit(i2,1,orig[i+1],2);
		getBit(i2,0,orig[i+1],1);
		uchar higher = Sbox[index][i1][i2];
		newbits[i/2] = (lower & 0x0f) + (higher<<4);
	}
}

// Permutation P
void P(char text[4])
{
	char ntext[4];
	for(uint i = 0; i < 4; i++)
		for(uint j = 0; j < 8; j++)
		{
			uint target = PermutationP[i][j] - 1;
			uint ic = target / 8;
			uint ib = target % 8;
			getBit(ntext[i],j,text[ic],ib);
		}
	for(uint i = 0; i < 4; i++)
		text[i] = ntext[i];
}

/*
   An extremely bizzare left shift, in fact, intended only for DES
   Shift the lower 7 bits of four chars as a whole, and is a circular shift
*/
void leftShift(char key[], uint nShft)
{
	// If the original is
	// abcdefgh abcdefgh abcdefgh abcdefgh abcdefgh abcdefgh abcdefgh abcdefgh
	// First, left shift each by one (since we do not care about the highest)
	// bcdefgh0 bcdefgh0 bcdefgh0 bcdefgh0 bcdefgh0 bcdefgh0 bcdefgh0 bcdefgh0
	// Second, copy all the b's to the previous zeros (higher one)
	for(uint n = 0; n < nShft; n++) // Do this for several times
	{
		for(uint i = 0; i < 8; i++) // Left shifts
			key[i] <<= 1;
		for(uint i = 0; i < 7; i++) // Copy the highest bits to the next lowest
			getBit(key[i+1],0,key[i],7);
		getBit(key[0],0,key[7],7);
	}
}

///////////////////////////////Main part of DES/////////////////////////////////
/* In each round:
1. Expand the text(lower 32 bits) to 48 bits
2. Use the key to Xor the text(48 bits)
3. Use the S-box to tackle the text(48 bits) back to 32 bits
4. Exert permutation P on the text(lower 32 bits)
5. Xor the lower 32 bits by higher 32 bits
6. Set the original lower 32 bits as the new higher 32 bits
7. Set the new lower 32 bits as new lower 32 btis
*/
/*
   In DES algorithm, the key is 56 bits, but for convenience (since there is
   no 7-bits variable type in C), 64 bits are passed as parameters, but only
   56 bits will be used. In fact only lower 7 bits will be used.
*/
void DESRound(
	char text[8],
	const char key[8],
	uint index
)
{
	char K[8], expansion[8]; // 48 bits permuted key, expanded text
	char newLower[4]; // New lower 32 bits
	
	// Permute2 of key
	permute2(key,K);
	
	// Expand lower 32 bits of text
	expand(text,expansion);
	
	// Do the Xor operation
	Xor48(expansion, K);
	// Use the S-box
	SBox(expansion, newLower, index);
	// Permutation P
	P(newLower);
	
	// Xor with the higher 32 bits
	Xor32(newLower, text+4);
	// Copy the original lower bits to higher
	memcpy(text+4, text, 4);
	// Copy the new lower 32 bits to the original place
	memcpy(text, newLower, 4);
}

/*
1. Initial permutation
2. Permute choose key
3. Carry out the DESRound function 16 times
4. Swap higher and lower 32 bits
5. Inverse Initial permutation
*/
void DESBlock(
	const char plainText[8],
	char cipherText[8],
	const char key[8],
	bool encrypt
)
{
	char subKeys[16][8]; // All the subkeys
	
	// Copy the plain text to the position of cipher text
	memcpy(cipherText,plainText,8);
	// Initial permutation
	initialPermutate(cipherText);
	// Permute choose key
	permuteChooseKey(key,subKeys[0]);
	
	
	// Generate all the subkeys
	for(uint i = 0; i < nRounds; i++)
	{
		// Get the number of left shifts from the schedule shift table
		uint nShft = schShft[i];
		leftShift(subKeys[i],nShft);
		leftShift(subKeys[i]+4,nShft);
		if(i < nRounds - 1) // If this is not the last round
			memcpy(subKeys[i+1],subKeys[i],8); // Copy the key to the next
	}
		
	// Carry out the DESRound function
	if(encrypt) // Encryption
	{
		for(uint i = 0; i < nRounds; i++)
		{
			DESRound(cipherText,subKeys[i],i);
		}
	}
	
	else // Decryption
	{
		for(uint i = 0; i < nRounds; i++)
		{
			DESRound(cipherText,subKeys[nRounds-1-i],nRounds-1-i);
		}
	}
		
	// Swap higher and lower 32 bits
	swap(cipherText,cipherText+4,4);
	
	// Inverse Initial permutation
	inverseInitialPermutate(cipherText);
	
}

void DES(
	const char plainText[][8],
	char cipherText[][8],
	const char key[8],
	uint n,
	bool encrypt
)
{
	// Encrypt each block separatedly
	for(uint i = 0; i < n; i++)
		DESBlock(plainText[i],cipherText[i],key,encrypt);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

using namespace std;

char getCharFromHex()
{
	char h;
	char l;
	cin >> h >> l;
	int sum = 0;
	if(isdigit(h)) sum = h - '0';
	else if(h >= 'a' && h <= 'f') sum = h - 'a' + 10;
	else if(h >= 'A' && h <= 'F') sum = h - 'A' + 10;
	sum <<= 4;
	if(isdigit(l)) sum += l - '0';
	else if(l >= 'a' && l <= 'f') sum += l - 'a' + 10;
	else if(l >= 'A' && l <= 'F') sum += l - 'A' + 10;
	return (char) sum;
}

void printCharInHex(char c)
{
	unsigned char h = (unsigned char) c >> 4;
	unsigned char l = c & 0x0f;
	cout << hex << (int)h << (int)l;
}

int main()
{
	const int n = 128;
	char plainText[n][8];
	char cipherText[n][8];
	char key[8];
	int i;
	
	cout << "Input the text you want to encrypt:" << endl;
	for(i = 0; i < 128; i++)
	{
		bool b = false;
		memset(plainText[i],'\0',8);
		for(int j = 0; j < 8; j++)
		{
			plainText[i][j] = cin.get();
			if(plainText[i][j]=='\n')
			{
				b = true;
				break;
			}
		}
		if(b) break;
	}
	if(i < 128) i++;
	
	memset(key,'\0',8);
	cout << "Input the key:" << endl;
	cin.getline(key,8);
	
	cout << "Encrypting ..." << endl;
	DES(plainText,cipherText,key,i,true);
	cout << "Done!" << endl;
	
	for(int j = 0; j < i; j++)
	{
		for(int k = 0; k < 8; k++)
		{
			printCharInHex(cipherText[j][k]);
			cout << ' ';
		}
		cout << endl;
	}
	
	cout << "Decrypting ..." << endl;
	DES(cipherText,plainText,key,i,false);
	cout << "Done!" << endl;
	for(int j = 0; j < i; j++)
	{
		for(int k = 0; k < 8; k++)
		{
			cout << plainText[j][k];
		}
	}
	cout << endl;
	return 0;
}
