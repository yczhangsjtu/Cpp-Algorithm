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

	int& first()
	{
		return head->next->d;
	}

	int& back()
	{
		return tail->prev->d;
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

	List operator*(const List& rh) const
	{
		List r;
		Node *p = head->next;
		Node *q = rh.head->next;
		while(p!=tail)
		{
			Node *pp = p, *qq = q;
			r.insertToTail(0);
			while(pp != tail && qq!= rh.head)
			{
				r.back() += pp->d * qq->d;
				pp = pp->next;
				qq = qq->prev;
			}
			if(q->next != rh.tail) q=q->next;
			else p=p->next;
		}
		r.flatten();
		return r;
	}
private:
	void flatten()
	{
		Node *p = tail->prev;
		while(p!=head)
		{
			if(p->d < 10)
			{
				p = p->prev;
				continue;
			}
			if(p->prev == head) insertToHead(0);
			p->prev->d += p->d/10;
			p->d %= 10;
			p = p->prev;
		}
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
	List s = l*r;
	s.print();
	cout << endl;
	return 0;
}
