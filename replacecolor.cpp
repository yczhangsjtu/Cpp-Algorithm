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
	fprintf(stderr,"Usage: replacecolor -i inputfile -o outputfile [-r int][-g int][-b\
	int][-R int][-G int][-B int][-e error]\n");
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
	unsigned char r = 0, g = 0, b = 0, R = 0, G = 0, B = 0, e = 0;
	while((ch = getopt(argc,argv,"i:o:r:g:b:R:G:B:"))!=-1)
	{
		switch(ch)
		{
		case 'i': strncpy(inputBuf,optarg,255); input = inputBuf; break;
		case 'o': strncpy(outputBuf,optarg,255); output = outputBuf; break;
		case 'r': r = atoi(optarg); break;
		case 'g': g = atoi(optarg); break;
		case 'b': b = atoi(optarg); break;
		case 'R': R = atoi(optarg); break;
		case 'G': G = atoi(optarg); break;
		case 'B': B = atoi(optarg); break;
		case 'e': e = atoi(optarg); break;
		}
	}
	
	if(!input || !output) usage();
	
	data = stbi_load(input,&x,&y,&n,0);
	if(!data)
	{
		fprintf(stderr,"Failed to open %s.\n",input);
		exit(1);
	}
	if(n < 3)
	{
		fprintf(stderr,"Invalid image.\n");
		exit(1);
	}
	
	for(int i = 0; i < y; i++)
	{
		for(int j = 0; j < x; j++)
		{
			int offset = i * x * n + j * n;
			if(abs((char)data[offset] - (char)r) + 
			   abs((char)data[offset+1] - (char)g) +
			   abs((char)data[offset+2] - (char)b) <= e)
			{
				data[offset] = R;
				data[offset+1] = G;
				data[offset+2] = B;
			}
		}
	}
	
	if(!stbi_write_png(output,x,y,n,data,x*n))
	{
		stbi_image_free(data);
		fprintf(stderr,"Failed to write to %s.\n",output);
		exit(1);
	}
	stbi_image_free(data);
	
	return 0;
}
