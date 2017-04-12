/*
* 已知二叉树的中序遍历和先序遍历或者后序遍历
* 得到另外一种遍历，或者构建该树
*/
#include <iostream>
using namespace std;

#define LENGTH(a) (sizeof(a) / sizeof(a[0]))

struct treenode
{
	int key;
	struct treenode* left;
	struct treenode* right;
};

void build_after(int pre[], int in[], int len)
{
	int i;
	if(len < 1)
		return;
	for(i = 0; i < len; i++)
		if(in[i] == *pre)
			break;
	build_after(pre + 1, in , i);
	build_after(pre + i + 1, in + i + 1, len - i - 1);
	cout << *pre << ' ';
}

void build_pre(int after[], int in[], int len)
{
	int i;
	if(len < 1)
		return;
	for(i = 0; i < len; i++)
		if(in[i] == *(after + len - 1))
			break;
	cout << *(after + len - 1) << ' ';
	build_pre(after, in, i);
	build_pre(after + i, in + i + 1, len - i - 1);
}

void build_tree_after(treenode** node, int pre[], int in[], int len)
{
	int i;
	if(len < 1)
		return;
	for(i = 0; i < len; i++)
		if(in[i] == *pre)
			break;
	*node = new treenode;
	(*node)->left = (*node)->right = 0;
	(*node)->key = *pre;
	build_tree_after(&((*node)->left), pre + 1, in, i);
	build_tree_after(&((*node)->right), pre + i + 1, in + i + 1, len - i - 1);
}

void build_tree_pre(treenode** node, int after[], int in[], int len)
{
	int i;
	if(len < 1)
		return;
	for(i = 0; i < len; i++)
		if(in[i] == *(after + len - 1))
			break;
	*node = new treenode;
	(*node)->left = (*node)->right = 0;
	(*node)->key = *(after + len - 1);
	build_tree_pre(&((*node)->left), after, in, i);
	build_tree_pre(&((*node)->right), after + i, in + i + 1, len - i - 1);
}

void preorder(treenode* root)
{
	if(root){
		cout << root->key << ' ';
		preorder(root->left);
		preorder(root->right);
	}
}

void tree_destory(treenode* root)
{
	if(!root)
		return;
	tree_destory(root->left);
	tree_destory(root->right);
	delete root;
}

int main()
{
	int pre[] = {13, 8, 1, 6, 11, 17, 15, 25, 22, 27};
	int in[] = {1, 6, 8, 11, 13, 15, 17, 22, 25, 27};
	int after[] = {6, 1, 11, 8, 15, 22, 27, 25, 17, 13};
	build_after(pre, in, LENGTH(pre));
	cout << endl;
	build_pre(after, in, LENGTH(in));
	cout << endl;

	treenode* root = 0;
	build_tree_after(&root, pre, in, LENGTH(in));
	if(!root)
		cout << "root is NULL" << endl;
	preorder(root);
	cout << endl;
	tree_destory(root);

	treenode* tree = 0;
	build_tree_pre(&tree, after, in, LENGTH(in));
	if(!tree)
		cout << "root is NULL" << endl;
	preorder(tree);
	cout << endl;
	tree_destory(tree);

	return 0;
}