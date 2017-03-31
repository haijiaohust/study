/*
*设计一个栈，使它可以在O(1)复杂度实现
*pop，push和min
*/
#include <iostream>
using namespace std;

class Stack{
public:
	int *stack;
	int *stack_min;
	int top;
	int max;
	int min(){
		if(!is_empty())
			return stack_min[top];
		else cout << "min() error, stack is empty" << endl;
	}
	void push(int a){
		if(!is_full())
		{
			top++;
			stack[top] = a;
			if(top == 0)
				stack_min[top] = a;
			else stack_min[top] = stack_min[top - 1] > a ? a : stack_min[top - 1];
		}
		else cout << "push error! stack is full" << endl;
	}
	int pop(){
		if(!is_empty())
			return stack[top--];
		else cout << "pop error! stack is empty" << endl;
	}
	int is_empty(){
		if(top == -1)
			return 1;
		return 0;
	}
	int is_full() {
		if(top == max - 1)
			return 1;
		return 0;
	}
	Stack(int n): top(-1), max(n) {
		stack = new int[n];
		stack_min = new int[n];
	}
	~Stack(){delete[] stack; delete[] stack_min;}
};

int main()
{
	Stack s(20);
	int a[] = {3, 4, 5, 1, 2, 6};
	for(int i = 0; i < 6; i++)
		s.push(a[i]);
	for(int i = 0; i < 6; i++)
		cout << s.pop() << "  " << s.min() << endl;
	cout << endl;
	return 0;
}