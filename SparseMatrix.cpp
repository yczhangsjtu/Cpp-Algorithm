#include <iostream>

using namespace std;

typedef struct Triple
{
	int x;
	int y;
	int d;
	Triple(int a,int b,int c):x(a),y(b),d(c){}
	void print() {cout << x << ' ' << y << ' ' << d << endl;}
} Triple;

typedef struct Node
{
	Triple d;
	Node* prev;
	Node* next;
	Node(Triple m) :d(m) {}
	Node(int x, int y, int n) :d(Triple(x,y,n)) {}
} Node;

class List
{
public:
	List()
	{
		head = new Node(Triple(0,0,0));
		tail = new Node(Triple(0,0,0));
		head->prev = NULL;
		head->next = tail;
		tail->prev = head;
		tail->next = NULL;
	}

	~List()
	{
		Node *p = head;
		while(p)
		{
			Node *q = p;
			p = p->next;
			delete q;
		}
	}

	void insertToHead(Triple d)
	{
		Node *node = new Node(d);
		node->prev = head;
		node->next = head->next;
		head->next->prev = node;
		head->next = node;
	}

	void insertToTail(Triple d)
	{
		Node *node = new Node(d);
		node->prev = tail->prev;
		node->next = tail;
		tail->prev->next = node;
		tail->prev = node;
	}

	Node* del(Node* p)
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
		Node* t = p->prev;
		delete p;
		return t;
	}

	void print()
	{
		Node *p = head->next;
		while(p->next != NULL)
		{
			p -> d.print();
			p = p->next;
		}
	}

	Node *head;
	Node *tail;
}; 
int main()
{
	int n;
	cin >> n;
	List matrix[10000];
	for(int i = 0; i < n; i++)
	{
		int x,y,z;
		cin >> x >> y >> z;
		int j = x % 10000;
		matrix[j].insertToTail(Triple(x,y,z));
	}

	int m;
	cin >> m;
	for(int i = 0; i < m; i++)
	{
		int op, x, y;
		cin >> op >> x >> y;
		if(op == 0)
		{
			if(x == y) continue;
			int xx = x%10000;
			int yy = y%10000;
			Node* p = matrix[xx].head->next;
			List l, r;
			while(p != matrix[xx].tail)
			{
				if(p->d.x == x)
				{
					l.insertToTail(Triple(y,p->d.y,p->d.d));
					p = matrix[xx].del(p);
				}
				p = p->next;
			}
			p = matrix[yy].head->next;
			while(p != matrix[yy].tail)
			{
				if(p->d.x == y)
				{
					r.insertToTail(Triple(x,p->d.y,p->d.d));
					p = matrix[yy].del(p);
				}
				p = p->next;
			}
			p = l.head->next;
			while(p != l.tail)
			{
				matrix[yy].insertToTail(p->d);
				p = p->next;
			}
			p = r.head->next;
			while(p != r.tail)
			{
				matrix[xx].insertToTail(p->d);
				p = p->next;
			}
		}
		else if(op == 1)
		{
			if(x == y) continue;
			for(int i = 0; i < 10000; i++)
			{
				Node* p = matrix[i].head->next;
				while(p != matrix[i].tail)
				{
					if(p->d.y == x) p->d.y = y;
					else if(p->d.y == y) p->d.y = x;
					p = p->next;
				}
			}
		}
		else if(op == 2)
		{
			int xx = x%10000;
			Node* p = matrix[xx].head -> next;
			while(p != matrix[xx].tail)
			{
				if(p->d.x == x && p->d.y == y)
				{
					cout << p->d.d << endl;
					break;
				}
				p = p->next;
			}
			if(p == matrix[xx].tail)
				cout << 0 << endl;
		}
	}
	return 0;
}
