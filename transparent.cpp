#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master\stb_image.h"
#include "stb-master\stb_image_write.h"

using namespace std;

void usage()
{
	fprintf(stderr,"Usage: trans -i inputfile -o outputfile [-r Rvalue][-g Gvalue][-b Bvalue]\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	int ch, x, y, n;
	const char *input = NULL;
	const char *output = NULL;
	unsigned char *data = NULL, *ndata = NULL;
	char inputBuf[256];
	char outputBuf[256];
	unsigned char r = 0, g = 0, b = 0;
	while((ch = getopt(argc,argv,"i:o:r:g:b:"))!=-1)
	{
		switch(ch)
		{
		case 'i': strncpy(inputBuf,optarg,255); input = inputBuf; break;
		case 'o': strncpy(outputBuf,optarg,255); output = outputBuf; break;
		case 'r': r = atoi(optarg); break;
		case 'g': g = atoi(optarg); break;
		case 'b': b = atoi(optarg); break;
		}
	}
	
	if(!input || !output) usage();
	
	data = stbi_load(input,&x,&y,&n,0);
	if(!data)
	{
		fprintf(stderr,"Failed to open %s.\n",input);
		exit(1);
	}
	if(n == 3)
	{
		ndata = new unsigned char[x*y*4];
		int N = x*y;
		for(int i = 0; i < N; i++)
		{
			int offset = i*4;
			ndata[offset] = data[i*3];
			ndata[offset+1] = data[i*3+1];
			ndata[offset+2] = data[i*3+2];
			if(ndata[offset] == r && ndata[offset+1] == g && ndata[offset+2] == b)
				ndata[offset+3] = 0;
			else
				ndata[offset+3] = 255;
		}
		stbi_image_free(data);
		data = ndata;
	}
	else if(n == 4)
	{
		int N = x*y;
		for(int i = 0; i < N; i++)
		{
			int offset = i*4;
			if(data[offset] == r && data[offset+1] == g && data[offset+2] == b)
			{
				data[offset] = 255;
				data[offset+1] = 255;
				data[offset+2] = 255;
				data[offset+3] = 0;
			}
		}
	}
	else
	{
		fprintf(stderr,"Image format invalid.\n");
		stbi_image_free(data);
		exit(1);
	}
	if(!stbi_write_png(output,x,y,4,data,4*x))
	{
		stbi_image_free(data);
		fprintf(stderr,"Failed to write to %s.\n",output);
		exit(1);
	}
	stbi_image_free(data);
	
	return 0;
}
