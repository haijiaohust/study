/*
*二叉查找树
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

template <class T, int MAXSIZE>
class Stack{
public:
	T st[MAXSIZE];
	int top;
	void push(T const&);
	void pop(T &);
	int getsize() const{
		return top + 1;
	}
	void gettop(T& a){
		if(is_empty())
			cout << "pop error! stack is empty" << endl;
		else a = st[top];
	}
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
	Stack(): top(-1) {}
};

template <class T, int MAXSIZE>
void Stack<T, MAXSIZE>::push(T const& a)
{
	if(is_full())
		cout << "push error! stack is full" << endl;
	else st[++top] = a;
}

template <class T, int MAXSIZE>
void Stack<T, MAXSIZE>::pop(T& a)
{
	if(is_empty())
		cout << "pop error! stack is empty" << endl;
	else a = st[top--];
}

struct treenode{
	int data;
	struct treenode* left;
	struct treenode* right;
	struct treenode* parent;
};

class Bitree{
public:
	treenode* root;
	bool insert(int);
	bool del(treenode*);
	treenode* successor(treenode*) const;
	treenode* predecessor(treenode*) const;
	treenode* _search(treenode*, int) const;
	treenode* _search_iter(treenode*, int) const;
	treenode* search(int) const;
	int high() const;
	int high(treenode*) const;
	void visit(int) const;
	void _preorder(treenode*) const;
	void _inorder(treenode*) const;
	void _afterorder(treenode*) const;
	void _depth_order(treenode*) const;
	void _level_order(treenode*) const;
	void _preorder_iter(treenode*) const;
	void _inorder_iter(treenode*) const;
	void _afterorder_iter(treenode*) const;
	void destory(treenode*);
	treenode* min_node(treenode* p) const;
	treenode* max_node(treenode* p) const;
	Bitree(){root = NULL;}
	Bitree(int a[], int n){
		root = NULL;
		for(int i = 0; i < n; i++)
			insert(a[i]);
	}
	~Bitree(){destory(root);}
};
int Bitree::high()  const
{
	return high(root);
}
int Bitree::high(treenode* p)  const
{
	int lhigh, rhigh;
	if(!p)
		return 0;
	else {
		lhigh = high(p->left);
		rhigh = high(p->right);
		return 1 + (lhigh > rhigh ? lhigh : rhigh);
	}
}
treenode* Bitree::min_node(treenode* p) const
{
	if(p){
		while(p->left)
			p = p->left;
		return p;
	}
	return NULL;
}
treenode* Bitree::max_node(treenode* p)  const
{
	if(p){
		while(p->right)
			p = p->right;
		return p;
	}
	return NULL;
}
treenode* Bitree::search(int a)  const
{
	return _search_iter(root, a);
}
treenode* Bitree::_search_iter(treenode* p, int a)  const
{
	treenode* q = p;
	if(!q)
		return NULL;
	while(q && q->data != a){
		if(q->data > a)
			q = q->left;
		else q = q->right;
	}
	return q;
}
treenode* Bitree::_search(treenode* p, int a)  const
{
	if(!p)
		return NULL;
	if(p->data == a)
		return p;
	if(p->data > a)
		return _search(p->left, a);
	else return _search(p->right, a);
}
bool Bitree::insert(int a)
{
	treenode* p = new treenode;
	treenode* q = root;
	treenode* y = root;
	if(!p)
		return false;
	p->data = a;
	p->left = p->right = p->parent = NULL;
	while(q){
		y = q;
		if(q->data > a)
			q = q->left;
		else q = q->right;
	}
	if(!y)
		root = p;
	else if(y->data > a)
	{
		y->left = p;
		p->parent = y;
	}
	else{
		y->right = p;
		p->parent = y;
	}
	return true;
}

treenode* Bitree::predecessor(treenode* p)  const
{
	if(!p)
		return NULL;
	else if(p->left)
		return max_node(p->left);
	treenode* y = p->parent;
	while(y && p == y->left)
	{
		p = y;
		y = y->parent;
	}
	return y;
}
treenode* Bitree::successor(treenode* p)  const
{
	if(!p)
		return NULL;
	else if(p->right)
		return min_node(p->right);
	treenode* y = p->parent;
	while(y && p == y->right){
		p = y;
		y = y->parent;
	}
	return y;
}
bool Bitree::del(treenode* p)
{
	treenode* child = NULL;
	treenode* parent = NULL;
	if(!p)
		return false;
	if(!p->left)
		child = p->right;
	else if(!p->right)
		child = p->left;
	else{
		treenode* y = successor(p);
		p->data = y->data;
		del(y);
		return true;
	}
	if(child)
		child->parent = p->parent;
	if(p->parent){
		if(p->parent->left == p)
			p->parent->left = child;
		else p->parent->right = child;
	}
	else root = child;
	delete p;
	return true;
}

void Bitree::visit(int flag) const
{
	switch(flag)
	{
		case 1: _preorder(root);
				break;
		case 2:	_inorder(root);
				break;
		case 3: _afterorder(root);
				break;
		case 4: _depth_order(root);
				break;
		case 5: _level_order(root);
				break;
		case 6: _preorder_iter(root);
				break;
		case 7: _inorder_iter(root);
				break;
		case 8: _afterorder_iter(root);
				break;
	}
}
void Bitree::_preorder(treenode* p) const
{
	if(p)
	{
		cout << p->data << ' ';
		_preorder(p->left);
		_preorder(p->right);
	}
}
void Bitree::_preorder_iter(treenode* p) const
{
	Stack< treenode*, 1024 > s;
	treenode* q = p;
	while(q || !s.is_empty()){
		while(q){
			cout << q->data << ' ';
			s.push(q);
			q = q->left;
		}
		if(!s.is_empty()){
			s.pop(q);
			q = q->right;
		}
	}
}

void Bitree::_inorder(treenode* p) const
{
	if(p)
	{
		_inorder(p->left);
		cout << p->data << ' ';
		_inorder(p->right);
	}
}
void Bitree::_inorder_iter(treenode* p) const
{
	treenode* q = p;
	Stack < treenode*, 1024 > s;
	while(q || !s.is_empty()){
		while(q){
			s.push(q);
			q = q->left;
		}
		if(!s.is_empty()){
			s.pop(q);
			cout << q->data << ' ';
			q = q->right;
		}
	}
}
void Bitree::_afterorder(treenode* p) const
{
	if(p)
	{
		_afterorder(p->left);
		_afterorder(p->right);
		cout << p->data << ' ';
	}
}

void Bitree::_afterorder_iter(treenode* p) const
{
	int flag[100];
	treenode* q = p;
	Stack < treenode*, 1024 > s;
	if(!p)
		return;
	while(q || !s.is_empty()){
		while(q){
			s.push(q);
			flag[s.getsize()] = 0;
			q = q->left;
		}
		while(!s.is_empty() && flag[s.getsize()] == 1){
			s.pop(q);
			cout << q->data << ' ';
		}
		if(!s.is_empty()){
			flag[s.getsize()] = 1;
			s.gettop(q);
			q = q->right;
		}
		else break;
	}
}
void Bitree::_depth_order(treenode* p) const
{
	treenode* q = NULL;
	Stack< treenode*, 1024 > stack;
	if(!p)
		return;
	stack.push(p);
	while(!stack.is_empty())
	{
		stack.pop(q);
		cout << q->data << ' ';
		if(q->right)
			stack.push(q->right);
		if(q->left)
			stack.push(q->left);
	}
}
void Bitree::_level_order(treenode* p) const
{
	treenode* q = NULL;
	Queue< treenode*, 1024> qu;
	if(!p)
		return;
	qu.enqueue(p);
	while(!qu.is_empty())
	{
		qu.outqueue(q);
		cout << q->data << ' ';
		if(q->left)
			qu.enqueue(q->left);
		if(q->right)
			qu.enqueue(q->right);
	}
}
void Bitree::destory(treenode* p)
{
	if(!p)
		return;
	destory(p->left);
	destory(p->right);
	delete[] p;
	p = NULL;
}
int main()
{
	treenode* p = NULL;
	const int num = 8;
	int a[num] = {10, 4, 2, 6, 45, 12, 78, 26};
	Bitree tree(a, num);

	tree.visit(1);
	cout << endl;
	tree.visit(6);
	cout << endl;
	tree.visit(2);
	cout << endl;
	tree.visit(7);
	cout << endl;
	tree.visit(3);
	cout << endl;
	tree.visit(8);
	cout << endl;
	tree.visit(4);
	cout << endl;
	tree.visit(5);
	cout << endl;
	cout << "ab" << endl;
	p = tree.search(26);
	if(p)
		cout << p->data << endl;
	else cout << "search error" << endl;
	tree._depth_order(p->left);
	cout << endl;
	p = tree.min_node(tree.root);
	if(p)
		cout << p->data << endl;
	else cout << "min error" << endl;
	p = tree.max_node(tree.root);
	if(p)
		cout << p->data << endl;
	else cout << "max error" << endl;
	p = tree.search(10);
	if(p)
		cout << p->left->data << ' ' << p->right->data << endl;
	else cout << "search error" << endl;
	p = tree.search(100);
	if(p)
		cout << p->left->data << ' ' << p->right->data << endl;
	else cout << "search error" << endl;
	cout << "high: " << tree.high() << endl;
	p = tree.search(a[3]);
	if(p)
		cout << "high: " << tree.high(p) << endl;
	else cout << "search error" << endl;
	for(int i = 0; i < num; i++)
	{
		p = tree.search(a[i]);
		p = tree.predecessor(p);
		cout << a[i] << ' ';
		if(p)
			cout << p->data << ' ';
		else cout << "no predecessor" << ' ';
		p = tree.search(a[i]);
		p = tree.successor(p);
		if(p)
			cout << p->data << endl;
		else cout << "no successor" << endl;
	}
	for(int i = 0; i < num; i++)
	{
		p = tree.search(a[i]);
		if(p)
			tree.del(p);
		else cout << "find :" << a[i] << " error" << endl;
		tree.visit(2);
		cout << endl;
	}
	return 0;
}