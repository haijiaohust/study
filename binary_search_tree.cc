/*
*二叉查找树
*/
#include <iostream>
using namespace std;

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
	treenode* successor(treenode*);
	treenode* predecessor(treenode*);
	treenode* _search(treenode*, int);
	treenode* _search_iter(treenode*, int);
	treenode* search(int);
	int high();
	int high(treenode*);
	void visit(int);
	void _preorder(treenode*);
	void _inorder(treenode*);
	void _afterorder(treenode*);
	void destory(treenode*);
	treenode* min_node(treenode* p);
	treenode* max_node(treenode* p);
	Bitree(){root = NULL;}
	Bitree(int a[], int n){
		root = NULL;
		for(int i = 0; i < n; i++)
			insert(a[i]);
	}
	~Bitree(){destory(root);}
};
int Bitree::high()
{
	return high(root);
}
int Bitree::high(treenode* p)
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
treenode* Bitree::min_node(treenode* p){
	if(p){
		while(p->left)
			p = p->left;
		return p;
	}
	return NULL;
}
treenode* Bitree::max_node(treenode* p){
	if(p){
		while(p->right)
			p = p->right;
		return p;
	}
	return NULL;
}
treenode* Bitree::search(int a)
{
	return _search_iter(root, a);
}
treenode* Bitree::_search_iter(treenode* p, int a)
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
treenode* Bitree::_search(treenode* p, int a)
{
	if(!p)
		return NULL;
	if(p->data == a)
		return p;
	if(p->data > a)
		_search(p->left, a);
	else _search(p->right, a);
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

treenode* Bitree::successor(treenode* p)
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
treenode* Bitree::predecessor(treenode* p)
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
	if(!p)
		return false;
	else if(!p->left && !p->right){
		if(!p->parent)
			root = NULL;
		else if(p->parent->left == p)
			p->parent->left = NULL;
		else p->parent->right = NULL;
		delete p;
		return true;
	}
	else if(!p->left && p->right){
		p->right->parent = p->parent;
		if(!p->parent){
			root = p->right;
			p->right->parent = NULL;
		}
		else if(p->parent->left == p)
			p->parent->left = p->right;
		else p->parent->right = p->right;
		delete p;
		return true;
	}
	else if(p->left && !p->right){
		p->left->parent = p->parent;
		if(!p->parent){
			root = p->left;
			p->left->parent = NULL;
		}
		else if(p->parent->left == p)
			p->parent->left = p->left;
		else p->parent->right = p->left;
		delete p;
		return true;
	}
	else{
		treenode* y = successor(p);
		if(!y){
			cout << "find aftersuccessor error"<< endl;
			return false;
		}
		else p->data = y->data;
		del(y);
		return true;
	}
}

void Bitree::visit(int flag)
{
	switch(flag)
	{
		case 1: _preorder(root);
				break;
		case 2:	_inorder(root);
				break;
		case 3: _afterorder(root);
				break;
	}
}
void Bitree::_preorder(treenode* p)
{
	if(p)
	{
		cout << p->data << ' ';
		_preorder(p->left);
		_preorder(p->right);
	}
}

void Bitree::_inorder(treenode* p)
{
	if(p)
	{
		_inorder(p->left);
		cout << p->data << ' ';
		_inorder(p->right);
	}
}
void Bitree::_afterorder(treenode* p)
{
	if(p)
	{
		_afterorder(p->left);
		_afterorder(p->right);
		cout << p->data << ' ';
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
	tree.visit(2);
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
		else cout << "no aftersuccessor" << ' ';
		p = tree.search(a[i]);
		p = tree.successor(p);
		if(p)
			cout << p->data << endl;
		else cout << "no presuccessor" << endl;
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