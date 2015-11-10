#include <stdio.h>
#include <string.h>
#define MAX_FILENAME 100
#define KEY_LENGTH 256

typedef unsigned char BYTE;

/*
	Initialization part of RC4
	
	Initialize the permutation of S: A permutation from 0 to 255
	The permutation is based on the key
*/
void initRC4(BYTE S[KEY_LENGTH], BYTE T[KEY_LENGTH], BYTE K[KEY_LENGTH]);
BYTE RC4(BYTE S[KEY_LENGTH], int *i, int *j);
void Swap(BYTE *a, BYTE *b);

int main(int argc,char *argv[])
{
	/*
	**Define the file stream
	*/ 
	FILE *input,*output;
	/*
	**Define the variables
	*/
	char inFileName[MAX_FILENAME+1],
		 outFileName[MAX_FILENAME+1],
		 key[KEY_LENGTH+1];
    int ch;
	int i, j;
	BYTE S[KEY_LENGTH+1],T[KEY_LENGTH+1];
	/*
	**Input filenames
	*/
    if(argc<4)
    {
        printf("Usage:RC4 <Input Filename> <Key> <Output Filename>\n");
		return -1;
    }
    else
    {
        strncpy(inFileName,argv[1],MAX_FILENAME);
        strncpy(outFileName,argv[3],MAX_FILENAME);
        strncpy(key,argv[2],KEY_LENGTH);
    }
	/*
	**Check if the two strings are the same, if then, report error and end.
	*/
	if(!strcmp(inFileName, outFileName))
	{
		printf("Input filename and output filename cannot be the same!\n");
		return -1;
	}
	
	/*
	**Open files and check if the files are opened correctly.
	*/
	input=fopen(inFileName,"rb");
	
	/*
	**If the files were not opened correctly, exit the program.
	*/
	if(input==NULL )
	{
		perror(inFileName);
		return -1;
	}
	output=fopen(outFileName,"wb");
	
	if(output==NULL)
	{
		perror(outFileName);
		return -1;
	}
	
	initRC4(S,T,key);
	i = 0, j = 0;
	
	/*
	**The main work
	*/
	while((ch=fgetc(input))!=EOF)
	{
        /*
        **Encoding
        */
		BYTE k = RC4(S,&i,&j);
		
		ch ^= k;
		
        if(*outFileName!='\0')
            fputc(ch,output);
        else
            printf("%c",ch);
	}
	
    fflush(stdout);
	/*
	**Close the files
	*/
	fclose(input);
    if(outFileName!='\0')
        fclose(output);
	printf("Assignment finished successfully!");
    fflush(stdout);
    return 0;
}

void initRC4(BYTE S[KEY_LENGTH], BYTE T[KEY_LENGTH], BYTE K[KEY_LENGTH])
{
	int i,j;
	/*The length of the key may not be KEY_LENGTH
	  So, use strlen to get the real length*/
	int keylen = strlen(K);
	if(keylen > KEY_LENGTH) keylen = KEY_LENGTH;
	for(i = 0; i < KEY_LENGTH; i++)
	{
		S[i] = i;
		T[i] = K[i % keylen];
	}
	for(j = 0; j < KEY_LENGTH; j++)
		j = (j+S[i]+T[i]) % KEY_LENGTH;
	Swap(&S[i],&S[j]);
}

BYTE RC4(BYTE S[KEY_LENGTH], int *i, int *j)
{
	int t;
	*i = (*i+1) % KEY_LENGTH;
	*j = (*j+S[*i]) % 256;
	Swap(&S[*i],&S[*j]);
	t = (S[*i]+S[*j]) % 256;
	return S[t];
}

void Swap(BYTE *a, BYTE *b)
{
	BYTE t = *a;
	*a = *b;
	*b = t;
}
