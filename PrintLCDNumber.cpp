#include <cstdio>
#include <cstring>

using namespace std;

void printt(const char buf[], int n)
{
	for(int i = 0; i < n; i++)
		printf("%s",buf);
}

void printhline(int s)
{
	printf(" ");
	printt("-",s);
	printf(" ");
}

void printlvline(int s)
{
	printf("|");
	printt(" ",s);
	printf(" ");
}

void printrvline(int s)
{
	printf(" ");
	printt(" ",s);
	printf("|");
}

void printlrvline(int s)
{
	printf("|");
	printt(" ",s);
	printf("|");
}

void printemptyline(int s)
{
	printt(" ",s+2);
}

void print1(int s, int line)
{
	if(line == 0 || line == s+1 || line == 2*s+2)
		printemptyline(s);
	else
		printrvline(s);
}
void print2(int s, int line)
{
	if(line == 0 || line == s+1 || line == 2*s+2)
		printhline(s);
	else if(line > 0 && line < s+1)
		printrvline(s);
	else
		printlvline(s);
}
void print3(int s, int line)
{
	if(line == 0 || line == s+1 || line == 2*s+2)
		printhline(s);
	else
		printrvline(s);
}
void print4(int s, int line)
{
	if(line == 0)
		printemptyline(s);
	else if(line > 0 && line < s+1)
		printlrvline(s);
	else if(line == s+1)
		printhline(s);
	else if(line == 2*s+2)
		printemptyline(s);
	else
		printrvline(s);
}
void print5(int s, int line)
{
	if(line == 0 || line == s+1 || line == 2*s+2)
		printhline(s);
	else if(line > 0 && line < s+1)
		printlvline(s);
	else
		printrvline(s);
}
void print6(int s, int line)
{
	if(line == 0 || line == s+1 || line == 2*s+2)
		printhline(s);
	else if(line > 0 && line < s+1)
		printlvline(s);
	else
		printlrvline(s);
}
void print7(int s, int line)
{
	if(line == 0)
		printhline(s);
	else if(line > 0 && line < s+1)
		printrvline(s);
	else if(line == s+1 || line == 2*s+2)
		printemptyline(s);
	else
		printrvline(s);
}
void print8(int s, int line)
{
	if(line == 0 || line == s+1 || line == 2*s+2)
		printhline(s);
	else if(line > 0 && line < s+1)
		printlrvline(s);
	else
		printlrvline(s);
}
void print9(int s, int line)
{
	if(line == 0 || line == s+1 || line == 2*s+2)
		printhline(s);
	else if(line > 0 && line < s+1)
		printlrvline(s);
	else
		printrvline(s);
}
void print0(int s, int line)
{
	if(line == 0 || line == 2*s+2)
		printhline(s);
	else if(line > 0 && line < s+1)
		printlrvline(s);
	else if(line == s+1)
		printemptyline(s);
	else
		printlrvline(s);
}

void printLCD(int s, char nums[])
{
	int l = strlen(nums);
	for(int line = 0; line < 2*s+3; line++)
	{
		for(int i = 0; i < l; i++)
		{
			if(i > 0) printf(" ");
			if(nums[i] == '0') print0(s,line);
			if(nums[i] == '1') print1(s,line);
			if(nums[i] == '2') print2(s,line);
			if(nums[i] == '3') print3(s,line);
			if(nums[i] == '4') print4(s,line);
			if(nums[i] == '5') print5(s,line);
			if(nums[i] == '6') print6(s,line);
			if(nums[i] == '7') print7(s,line);
			if(nums[i] == '8') print8(s,line);
			if(nums[i] == '9') print9(s,line);
		}
		printf("\n");
	}
}

int main()
{
	int s;
	char buf[10];
	while(true)
	{
		/*
		 * s is size (the length of a stick), buf is the string of numbers
		 */
		scanf("%d%s",&s,buf);
		if(s == 0) break;
		printLCD(s,buf);
		printf("\n");
	}
	return 0;
}
