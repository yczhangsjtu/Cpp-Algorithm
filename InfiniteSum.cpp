#include <iostream>
#include <cstdlib>
#include <string>

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

	Node *head;
	Node *tail;
};

int main()
{
	List l,r;
	string L,R;
	cin >> L >> R;
	for(int i = 0; i < L.length(); i++)
		l.insertToTail(L.at(i)-'0');
	for(int i = 0; i < R.length(); i++)
		r.insertToTail(R.at(i)-'0');
	List s = l+r;
	s.print();
	cout << endl;
	return 0;
}
