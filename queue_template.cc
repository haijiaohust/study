/*
*循环队列
*/
#include <iostream>
using namespace std;

template <class T, int MAXSIZE>
class Queue{
public:
	T Q[MAXSIZE];
	int front;
	int rear;
	void enqueue(T& a){
		if(is_full()){
			cout << "Queue is full" << endl;
			return;
		}
		Q[rear] = a;
		rear = (rear + 1) % MAXSIZE;
	}
	void outqueue(T& a){
		if(is_empty()){
			cout << "Queue is empty" << endl;
			return ;
		}
		a = Q[front];
		front = (front + 1) % MAXSIZE;
	}
	bool is_full(){
		return (((rear + 1) % MAXSIZE) == front);
	}
	bool is_empty(){
		return (rear == front);
	}
	Queue(): front(0), rear(0) {}
};

int main()
{
	Queue<int, 10> qu;
	int t;
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
	for(int i =0; i < 8; i++)
		qu.enqueue(a[i]);
	while(!qu.is_empty())
	{
		qu.outqueue(t);
		cout << t << ' ';
	}
	cout << endl;

	for(int i =2; i < 6; i++)
		qu.enqueue(a[i]);
	while(!qu.is_empty())
	{
		qu.outqueue(t);
		cout << t << ' ';
	}
	cout << endl;
	return 0;
}