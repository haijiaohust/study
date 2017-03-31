#include <iostream>
#include <cstring>
using namespace std;

struct ListNode{
	int data;
	struct ListNode* next;
};

class List{
public:
	ListNode *L;
	int insert_front(int);
	ListNode* find_i(int);
	ListNode* find_data(int);
	void insert(ListNode*, int);
	void del(ListNode*);
	int list_length();
	void print_list();
	List(){L = NULL;}
	~List(){
		ListNode* p = L;
		ListNode* q = NULL;
		while(p)
		{
			q = p;
			p = p->next;
			delete[] q;
		}
		L = NULL;
	}
};

int List::insert_front(int data)
{
	ListNode* p = new ListNode;
	if(!p)
		return 1;
	p->data = data;
	p->next = NULL;
	if(!L)
	{
		L = p;
		return 0;
	}
	p->next = L;
	L = p;
	return 0;
}

ListNode* List::find_i(int n)
{
	if(n < 1)
		return NULL;
	int i = 1;
	ListNode* p = L;
	while(p && i++ < n)
		p = p->next;
	return p;
}
ListNode* List::find_data(int data)
{
	ListNode* p = L;
	while(p && p->data != data)
		p = p->next;
	return p;
}
void List::insert(ListNode* p, int data)
{
	ListNode* q = new ListNode;
	q->data = data;
	q->next = p->next;
	p->next = q;
}
void List::del(ListNode* p)
{
	ListNode* q = p->next;
	memcpy(p, q, sizeof(ListNode));
	delete[] q;
}
int List::list_length()
{
	int i = 1;
	ListNode* p = L;
	while(p)
	{
		i++;
		p = p->next;
	}
	return i-1;
}
void List::print_list()
{
	ListNode* p = L;
	cout << "list lenght=" << list_length() << ": ";
	while(p)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}
int main()
{
	int a[6] = {1, 2, 3, 4, 5, 6};
	List list;
	ListNode* p = NULL;
	for(int i = 0; i < 6; i++)
		list.insert_front(a[i]);
	list.print_list();

	p = list.find_i(3);
	list.insert(p, 10);
	list.print_list();
	list.del(p);
	list.print_list();

	return 0;
}
