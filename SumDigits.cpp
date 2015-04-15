#include <iostream>

using namespace std;

typedef struct Node
{
	int d;
	Node* prev;
	Node* next;
	Node(int m) :d(m) {}
} Node;

class List
{
public:
	List()
	{
		head = new Node(0);
		tail = new Node(0);
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

	void insertToHead(int d)
	{
		Node *node = new Node(d);
		node->prev = head;
		node->next = head->next;
		head->next->prev = node;
		head->next = node;
	}

	void insertToTail(int d)
	{
		Node *node = new Node(d);
		node->prev = tail->prev;
		node->next = tail;
		tail->prev->next = node;
		tail->prev = node;
	}

	void print()
	{
		Node *p = head->next;
		while(p->next != NULL)
		{
			cout << p->d;
			p = p->next;
		}
	}

	List operator+(const List& rh) const
	{
		Node *p = tail->prev;
		Node *q = rh.tail->prev;
		List r;
		int carry = 0;
		while(p!=head || q!=rh.head)
		{
			int l1 = p==head?0:p->d;
			int l2 = q==rh.head?0:q->d;
			int s = l1+l2+carry;
			carry = s/10;
			s %= 10;
			r.insertToHead(s);
			if(p!=head) p = p->prev;
			if(q!=rh.head) q = q->prev;
		}
		if(carry > 0) r.insertToHead(carry);
		return r;
	}

	List operator=(const List& rh)
	{
		Node *p = head;
		while(p)
		{
			Node *q = p;
			p = p->next;
			delete q;
		}
		head = new Node(0);
		tail = new Node(0);
		head->prev = NULL;
		tail->prev = head;
		head->next = tail;
		tail->next = NULL;
		p = rh.head->next;
		while(p!=rh.tail)
		{
			insertToTail(p->d);
			p = p->next;
		}
		return *this;
	}

	Node *head;
	Node *tail;
};

int main()
{
	List a,b;
	List l; l.insertToTail(1);
	int e,f;
	char c;
	while((c=cin.get())>='0' && c<='9')
	{
		a.insertToTail(c-'0');
	}
	cin >> e;
	while((c=cin.get())>'9' || c<'0')
		;
	cin.putback(c);
	while((c=cin.get())>='0' && c<='9')
	{
		b.insertToTail(c-'0');
	}
	cin >> f;
	int g = e+f;
	List h = a+b;
	if(g > 99)
	{
		List t = h+l;
		t.print();
	}
	else
	{
		h.print();
	}
	g%=100;
	cout << "." << g/10 << g%10 << endl;
	return 0;
}
