/*
*设计一个栈模板
*/
#include <iostream>
using namespace std;

template <class T, int MAXSIZE>
class stack{
public:
	T st[MAXSIZE];
	int top;
	void push(T const&);
	void pop(T &);
	bool is_empty() const {
		if(top == -1)
			return true;
		return false;
	}
	bool is_full() const {
		if(top == MAXSIZE - 1)
			return true;
		return false;
	}
	stack(): top(-1) {}
};

template <class T, int MAXSIZE>
void stack<T, MAXSIZE>::push(T const& a)
{
	if(is_full())
		cout << "push error! stack is full" << endl;
	else st[++top] = a;
}

template <class T, int MAXSIZE>
void stack<T, MAXSIZE>::pop(T& a)
{
	if(is_empty())
		cout << "pop error! stack is empty" << endl;
	else a = st[top--];
}

int main()
{
	stack<int, 20> s;
	int p;
	int a[] = {3, 4, 5, 1, 2, 6};
	for(int i = 0; i < 6; i++)
		s.push(a[i]);
	for(int i = 0; i < 6; i++)
	{
		s.pop(p);
		cout << i << ' ' << p << ' ' << endl;
	}
	cout << endl;
	return 0;
}