#include <opencv2/opencv.hpp>
#include <cstdio>

/*
 *
 * Makefile
LIBS = -lopencv_core -lopencv_highgui -lopencv_imgproc
FLAGS = -ggdb

thinner: thinner.cpp
	g++ $< -o $@ $(LIBS) $(FLAGS)
 *
 */

using namespace cv;

void thin(Mat & binaryImage, Mat & thinImage);
uchar result1(uchar p1, uchar p2, uchar p3, uchar p4, uchar p5, uchar p6, uchar p7, uchar p8, uchar p9);
uchar result2(uchar p1, uchar p2, uchar p3, uchar p4, uchar p5, uchar p6, uchar p7, uchar p8, uchar p9);

int main(int argc, char *argv[])
{
	Mat image = imread("Screenshot.bmp",1);
	Mat grayImage,binaryImage,thinImage;
	cvtColor(image,grayImage,CV_BGR2GRAY);
	imshow("Gray image", grayImage);
	threshold(grayImage,binaryImage, 127,255,0);
	imshow("Binary image", binaryImage);
	thin(binaryImage,thinImage);
	imshow("Thin image", thinImage);
	waitKey(0);
	return 0;
}

void thin(Mat & binaryImage, Mat & thinImage)
{
	thinImage = binaryImage.clone();
	while(true)
	{
		bool changed = false;
		Mat prevImage = thinImage.clone();
		for(int y = 1; y < thinImage.rows-1; y++)
		{
			for(int x = 1; x < thinImage.cols-1; x++)
			{
				uchar p1 = prevImage.at<uchar>(y,x);
				uchar p2 = prevImage.at<uchar>(y-1,x);
				uchar p3 = prevImage.at<uchar>(y-1,x+1);
				uchar p4 = prevImage.at<uchar>(y,x+1);
				uchar p5 = prevImage.at<uchar>(y+1,x+1);
				uchar p6 = prevImage.at<uchar>(y+1,x);
				uchar p7 = prevImage.at<uchar>(y+1,x-1);
				uchar p8 = prevImage.at<uchar>(y,x-1);
				uchar p9 = prevImage.at<uchar>(y-1,x-1);
				uchar p0 = result1(p1,p2,p3,p4,p5,p6,p7,p8,p9);
				if((p1 && !p0) || (!p1 && p0)) changed = true;
				thinImage.at<uchar>(y,x) = p0;
			}
		}
		if(!changed) break;
		changed = false;
		prevImage = thinImage.clone();
		for(int y = 1; y < thinImage.rows-1; y++)
		{
			for(int x = 1; x < thinImage.cols-1; x++)
			{
				uchar p1 = prevImage.at<uchar>(y,x);
				uchar p2 = prevImage.at<uchar>(y-1,x);
				uchar p3 = prevImage.at<uchar>(y-1,x+1);
				uchar p4 = prevImage.at<uchar>(y,x+1);
				uchar p5 = prevImage.at<uchar>(y+1,x+1);
				uchar p6 = prevImage.at<uchar>(y+1,x);
				uchar p7 = prevImage.at<uchar>(y+1,x-1);
				uchar p8 = prevImage.at<uchar>(y,x-1);
				uchar p9 = prevImage.at<uchar>(y-1,x-1);
				uchar p0 = result2(p1,p2,p3,p4,p5,p6,p7,p8,p9);
				if((p1 && !p0) || (!p1 && p0)) changed = true;
				thinImage.at<uchar>(y,x) = p0;
			}
		}
		if(!changed) break;
	}
}

uchar result1(uchar p1, uchar p2, uchar p3, uchar p4, uchar p5, uchar p6, uchar p7, uchar p8, uchar p9)
{
	if(p1) return (uchar)255;
	int black[9] = {
		p2? 0:1, p3? 0:1, p4? 0:1,
		p5? 0:1, p6? 0:1, p7? 0:1,
		p8? 0:1, p9? 0:1, p2? 0:1
	};
	int A = 0, B = 0;
	for(int i = 0; i < 8; i++)
	{
		A += (1-black[i])*black[i+1];
		B += black[i];
	}
	if(A != 1) return (uchar)0;
	if(B < 2 || B > 6) return (uchar)0;
	if(black[0]*black[2]*black[4]) return (uchar)0;
	if(black[2]*black[4]*black[6]) return (uchar)0;
	return (uchar)255;
}

uchar result2(uchar p1, uchar p2, uchar p3, uchar p4, uchar p5, uchar p6, uchar p7, uchar p8, uchar p9)
{
	if(p1) return (uchar)255;
	int black[9] = {
		p2? 0:1, p3? 0:1, p4? 0:1,
		p5? 0:1, p6? 0:1, p7? 0:1,
		p8? 0:1, p9? 0:1, p2? 0:1
	};
	int A = 0, B = 0;
	for(int i = 0; i < 8; i++)
	{
		A += (1-black[i])*black[i+1];
		B += black[i];
	}
	if(A != 1) return (uchar)0;
	if(B < 2 || B > 6) return (uchar)0;
	if(black[0]*black[2]*black[6]) return (uchar)0;
	if(black[0]*black[4]*black[6]) return (uchar)0;
	return (uchar)255;
}
