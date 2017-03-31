/*
*二叉查找树
*/
#include <iostream>
using namespace std;

struct treenode{
	int data;
	struct treenode* left;
	struct treenode* right;
};

class Bitree{
public:
	treenode* root;
	void insert(int);
	treenode* search(treenode*, int);
	void preorder(treenode*);
	void inorder(treenode*);
	void afterorder(treenode*);
	void destory(treenode*);
	treenode* min(treenode* p){
		if(p){
			while(p->left)
				p = p->left;
			return p;
		}
		return NULL;
	}
	treenode* max(treenode* p){
		if(p){
			while(p->right)
				p = p->right;
			return p;
		}
		return NULL;
	}
	Bitree(){root = NULL;}
	~Bitree(){destory(root);}
};
treenode* Bitree::search(treenode* p, int a)
{
	if(!p)
		return NULL;
	if(p->data == a)
		return p;
	if(p->data > a)
		search(p->left, a);
	else search(p->right, a);
}
void Bitree::insert(int a)
{
	treenode* p = new treenode;
	treenode* q = root;
	treenode* y = root;
	p->data = a;
	p->left = p->right = NULL;
	while(q){
		y = q;
		if(q->data > a)
			q = q->left;
		else q = q->right;
	}
	if(!y)
		root = p;
	else if(y->data > a)
		y->left = p;
	else y->right = p;
}

void Bitree::preorder(treenode* p)
{
	if(p)
	{
		cout << p->data << ' ';
		preorder(p->left);
		preorder(p->right);
	}
}

void Bitree::inorder(treenode* p)
{
	if(p)
	{
		inorder(p->left);
		cout << p->data << ' ';
		inorder(p->right);
	}
}
void Bitree::afterorder(treenode* p)
{
	if(p)
	{
		inorder(p->left);
		inorder(p->right);
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
}
int main()
{
	Bitree tree;
	treenode* p = NULL;
	int a[] = {10, 4, 2, 6, 12, 78, 45, 26};
	for(int i = 0; i < 8; i++)
		tree.insert(a[i]);

	tree.preorder(tree.root);
	cout << endl;
	tree.inorder(tree.root);
	cout << endl;
	p = tree.min(tree.root);
	if(p)
		cout << p->data << endl;
	else cout << "min error" << endl;
	p = tree.max(tree.root);
	if(p)
		cout << p->data << endl;
	else cout << "max error" << endl;
	p = tree.search(tree.root, 10);
	if(p)
		cout << p->left->data << ' ' << p->right->data << endl;
	else cout << "search error" << endl;
	return 0;
}