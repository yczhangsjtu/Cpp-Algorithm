#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct Node
{
	int num;
	Node* next[26];
	Node()
	{
		num = 0;
		for(int i = 0; i < 26; i++)
			next[i] = NULL;
	}
} Node;

int main()
{
	int n,m;
	scanf("%d",&n);
	Node s;
	char buf[11];
	for(int i = 0; i < n; i++)
	{
		scanf("%s",buf);
		char c;
		int k = 0;
		Node* p = &s;
		p->num++;
		while((c=buf[k])!='\0')
		{
			if(p->next[c-'a']==NULL)
				p->next[c-'a'] = new Node;
			p = p->next[c-'a'];
			p->num++;
			k++;
		}
	}
	scanf("%d",&m);
	for(int i = 0; i < m; i++)
	{
		scanf("%s",buf);
		char c;
		int k = 0;
		Node* p = &s;
		p->num++;
		int res = 0;
		while((c=buf[k])!='\0')
		{
			p = p->next[c-'a'];
			if(p == NULL)
			{
				res = 0;
				break;
			}
			k++;
		}
		if(p != NULL) res = p->num;
		printf("%d\n",res);
	}
	return 0;
}
