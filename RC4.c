#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_FILENAME 100
#define KEY_LENGTH 256
//#define DEBUG

typedef unsigned char BYTE;

/*
	Initialization part of RC4

	Initialize the permutation of S: A permutation from 0 to 255
	The permutation is based on the key
*/
void initRC4(BYTE S[KEY_LENGTH], BYTE T[KEY_LENGTH], BYTE K[KEY_LENGTH]);
BYTE RC4(BYTE S[KEY_LENGTH], int *i, int *j);
void Swap(BYTE *a, BYTE *b);
void usage();
int debug = 0;

int main(int argc,char *argv[])
{
    int ch;
    opterr = 0;
    int i, j;

    /*
    **Define the file stream
    */
    char inbuf[MAX_FILENAME+1], outbuf[MAX_FILENAME+1];
    BYTE S[KEY_LENGTH+1],T[KEY_LENGTH+1];
    char key[KEY_LENGTH+1];
    char* inf = NULL, *outf = NULL, *pkey = NULL;
    FILE *input,*output;
    /*
    **Define the variables
    */

    while((ch = getopt(argc,argv,"i:o:k:vh"))!=-1)
    {
        switch(ch)
        {
        case 'i':
            strncpy(inbuf,optarg,MAX_FILENAME);
            inf = inbuf;
            break;
        case 'o':
            strncpy(outbuf,optarg,MAX_FILENAME);
            outf = outbuf;
            break;
        case 'k':
            strncpy(key,optarg,KEY_LENGTH);
            pkey = key;
            break;
        case 'v':
            debug = 1;
            break;
        case 'h':
            usage();
            exit(0);
        }
    }
    /*
    **Check if the two strings are the same, if then, report error and end.
    */
    if(inf && outf && strcmp(inf, outf) == 0)
    {
        fprintf(stderr,"Input filename and output filename cannot be the same!\n");
        exit(0);
    }
    if(pkey == NULL)
    {
        usage();
        exit(0);
    }
    if(debug && !inf)
        fprintf(stderr,"No input file specified, use stdin as input.\n");
    if(debug && !outf)
        fprintf(stderr,"No output file specified, use stdout as output.\n");

    /*
    **Open files and check if the files are opened correctly.
    */
    input=inf?fopen(inf,"rb"):stdin;
    if(input==NULL ) perror(inf);
    output=outf?fopen(outf,"wb"):stdout;
    if(output==NULL ) perror(outf);

    initRC4(S,T,key);
    i = 0, j = 0;

    /*
    **The main work
    */
    while((ch=fgetc(input))!=EOF)
    {
        BYTE k = RC4(S,&i,&j);
        ch ^= k;
        fputc(ch,output);
        fflush(output);
    }

    /*
    **Close the files
    */
    if(input != stdin)fclose(input);
    if(output != stdout)fclose(output);
    if(debug) fprintf(stderr,"Assignment finished successfully!\n");
    return 0;
}

void initRC4(BYTE S[KEY_LENGTH], BYTE T[KEY_LENGTH], BYTE K[KEY_LENGTH])
{
    int i,j,k;
    /*The length of the key may not be KEY_LENGTH
      So, use strlen to get the real length*/
    int keylen = strlen(K);
    if(keylen > KEY_LENGTH) keylen = KEY_LENGTH;
    for(i = 0; i < KEY_LENGTH; i++)
    {
        S[i] = i;
        T[i] = K[i % keylen];
    }
    j = 0;
    for(i = 0; i < KEY_LENGTH; i++)
    {
        j = (j+S[i]+T[i]) % KEY_LENGTH;
        Swap(&S[i],&S[j]);
    }
    if(debug)
    {
        fprintf(stderr,"S:");
        for(i = 0; i < KEY_LENGTH; i++)
        {
            if(i % 16 == 0) fprintf(stderr,"\n");
            fprintf(stderr,"%x",S[i]/16);
            fprintf(stderr,"%x",S[i]%16);
        }
        fprintf(stderr,"\n");
    }
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

void usage()
{
    printf("Usage:RC4 -k key[-i inputfile][-o outfile][-v]\n");
}
