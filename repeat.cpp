#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"
#include "stb-master/stb_image_write.h"

using namespace std;

void usage()
{
	fprintf(stderr,"Usage: repeat -i inputfile -o outputfile [-n Repeat number]\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	int ch, x, y, n, k = 1;
	const char *input = NULL;
	const char *output = NULL;
	unsigned char *data = NULL, *ndata = NULL;
	char inputBuf[256];
	char outputBuf[256];
	unsigned char r = 0, g = 0, b = 0;
	while((ch = getopt(argc,argv,"i:o:n:"))!=-1)
	{
		switch(ch)
		{
		case 'i': strncpy(inputBuf,optarg,255); input = inputBuf; break;
		case 'o': strncpy(outputBuf,optarg,255); output = outputBuf; break;
		case 'n': k = atoi(optarg); break;
		}
	}
	
	if(!input || !output) usage();
	
	data = stbi_load(input,&x,&y,&n,0);
	if(!data)
	{
		fprintf(stderr,"Failed to open %s.\n",input);
		exit(1);
	}
	if(n != 4)
	{
		fprintf(stderr,"Invalid png file.\n");
		exit(1);
	}
	
	int len = x * n, llen = len * k;
	ndata = new unsigned char[llen*y];
	for(int l = 0; l < y; l++)
	{
		for(int kk = 0; kk < k; kk++)
			memcpy(&ndata[l*llen+kk*len],&data[l*len],len);
	}
	stbi_image_free(data);
	data = ndata;
	
	if(!stbi_write_png(output,x*k,y,n,data,llen))
	{
		stbi_image_free(data);
		fprintf(stderr,"Failed to write to %s.\n",output);
		exit(1);
	}
	stbi_image_free(data);
	
	return 0;
}
