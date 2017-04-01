/*
*循环队列
*/
#include <iostream>
using namespace std;

class Queue{
public:
	int Max;
	int *Q;
	int front;
	int rear;
	void enqueue(int a){
		if(is_full()){
			cout << "Queue is full" << endl;
			return;
		}
		Q[rear] = a;
		rear = (rear + 1) % Max;
	}
	int outqueue(){
		if(is_empty()){
			cout << "Queue is empty" << endl;
			//return ;
		}
		int t = Q[front];
		front = (front + 1) % Max;
		return t;
	}
	void print_Q(){
		for(int i = front; i != rear; i++)
		{
			i = i % Max;
			cout << Q[i] << ' ';
		}
	}
	bool is_full(){
		return (((rear + 1) % Max) == front);
	}
	bool is_empty(){
		return (rear == front);
	}
	Queue(int n): Max(n){
		Q = new int[n];
		front = rear = 0;
	}
	~Queue(){delete[] Q;}
};

int main()
{
	Queue qu(6);
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
	for(int i =0; i < 8; i++)
	{
		qu.enqueue(a[i]);
		qu.print_Q();
		cout << endl;
	}
	for(int i =0; i < 8; i++)
	{
		cout << qu.outqueue() << '\t';
		qu.print_Q();
		cout << endl;
	}
	return 0;
}