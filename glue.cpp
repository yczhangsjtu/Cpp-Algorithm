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
	fprintf(stderr,"Usage: glue -i inputfile1 -j inputfile2 -o outputfile [-v]\n");
	exit(1);
}

inline int max(int x1, int x2)
{
	return x1>x2?x1:x2;
}

void copyto(unsigned char *dst, int x0, int y0, int W, int H, unsigned char *src, int w, int h)
{
	int w4 = w*4, x04 = x0*4, W4 = W*4;
	for(int l = 0; l < h; l++)
		memcpy(&dst[(l+y0)*W4+x04],&src[l*w4],w4);
}

int main(int argc, char *argv[])
{
	int ch, x1, y1, n1, x2, y2, n2;
	bool v = false;
	const char *input1 = NULL;
	const char *input2 = NULL;
	const char *output = NULL;
	unsigned char *data1 = NULL, *data2 = NULL, *ndata = NULL;
	char inputBuf1[256];
	char inputBuf2[256];
	char outputBuf[256];
	unsigned char r = 0, g = 0, b = 0;
	while((ch = getopt(argc,argv,"i:j:o:v"))!=-1)
	{
		switch(ch)
		{
		case 'i': strncpy(inputBuf1,optarg,255); input1 = inputBuf1; break;
		case 'j': strncpy(inputBuf2,optarg,255); input2 = inputBuf2; break;
		case 'o': strncpy(outputBuf,optarg,255); output = outputBuf; break;
		case 'v': v = true;
		}
	}
	
	if(!input1 || !input2 || !output) usage();
	
	data1 = stbi_load(input1,&x1,&y1,&n1,0);
	if(!data1)
	{
		fprintf(stderr,"Failed to open %s.\n",input1);
		exit(1);
	}
	data2 = stbi_load(input2,&x2,&y2,&n2,0);
	if(!data2)
	{
		fprintf(stderr,"Failed to open %s.\n",input2);
		exit(1);
	}
	if(n1 != 4 || n2 != 4)
	{
		fprintf(stderr,"Invalid png file.\n");
		exit(1);
	}
	
	int W,H,x0,y0;
	if(v)
	{
		W = max(x1,x2);
		H = y1+y2;
		x0=0;
		y0=y1;
	}
	else
	{
		W = x1+x2;
		H = max(y1,y2);
		x0= x1;
		y0= 0;
	}
	
	ndata = new unsigned char[W*H*4];
	copyto(ndata,0,0,W,H,data1,x1,y1);
	copyto(ndata,x0,y0,W,H,data2,x2,y2);
	stbi_image_free(data1);
	stbi_image_free(data2);
	
	if(!stbi_write_png(output,W,H,4,ndata,W*4))
	{
		stbi_image_free(ndata);
		fprintf(stderr,"Failed to write to %s.\n",output);
		exit(1);
	}
	stbi_image_free(ndata);
	
	return 0;
}
