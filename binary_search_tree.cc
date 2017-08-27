/*
*二叉查找树
*/
#include <iostream>
#include <stack>
#include <queue>
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
void Bitree::_preorder(treenode* root) const
{
	if(root)
	{
		cout << root->data << ' ';
		_preorder(root->left);
		_preorder(root->right);
	}
}
void Bitree::_preorder_iter(treenode* root) const
{
	stack< treenode* > s;
	treenode* cur = root;
	while(cur || !s.empty()){
		while(cur){
			cout << cur->data << ' ';
			s.push(cur);
			cur = cur->left;
		}
		if(!s.empty()){
			cur = s.top();
			s.pop();
			cur = cur->right;
		}
	}
}

void Bitree::_inorder(treenode* root) const
{
	if(root)
	{
		_inorder(root->left);
		cout << root->data << ' ';
		_inorder(root->right);
	}
}
void Bitree::_inorder_iter(treenode* root) const
{
	treenode* cur = root;
	stack < treenode* > s;
	while(cur || !s.empty()){
		while(cur){
			s.push(cur);
			cur = cur->left;
		}
		if(!s.empty()){
			cur = s.top();
			s.pop();
			cout << cur->data << ' ';
			cur = cur->right;
		}
	}
}
void Bitree::_afterorder(treenode* root) const
{
	if(root)
	{
		_afterorder(root->left);
		_afterorder(root->right);
		cout << root->data << ' ';
	}
}

void Bitree::_afterorder_iter(treenode* root) const
{
	treenode* cur;
	stack < treenode* > s;
	if(!root)
		return;
	s.push(root);
	treenode *pre = NULL;
	while(!s.empty()){
		cur = s.top();
		//左孩子和右孩子同时为空，或者当前结点的左孩子或右孩子已经遍历过了
		if(((cur->left == NULL) && (cur->right == NULL)) || ((pre != NULL) && (pre == cur->left || pre == cur->right)))
		{
			cout << cur->data << ' ';
			s.pop();
			pre = cur;
		}
		else{
			if(cur->right)
				s.push(cur->right);
			if(cur->left)
				s.push(cur->left);
		}
	}
}
void Bitree::_depth_order(treenode* root) const
{
	treenode* cur = NULL;
	stack< treenode* > s;
	if(!root)
		return;
	s.push(root);
	while(!s.empty())
	{
		cur = s.top();
		cout << cur->data << ' ';
		s.pop();
		if(cur->right)
			s.push(cur->right);
		if(cur->left)
			s.push(cur->left);
	}
}
void Bitree::_level_order(treenode* root) const
{
	treenode* cur = NULL;
	queue< treenode*> qu;
	if(!root)
		return;
	qu.push(root);
	while(!qu.empty())
	{
		cur = qu.front();
		cout << cur->data << ' ';
		qu.pop();
		if(cur->left)
			qu.push(cur->left);
		if(cur->right)
			qu.push(cur->right);
	}
}
void Bitree::destory(treenode* root)
{
	if(!root)
		return;
	destory(root->left);
	destory(root->right);
	delete root;
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