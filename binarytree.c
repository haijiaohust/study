#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int keytype;

struct node{
    keytype key;
	struct node *lchild;
	struct node *rchild;
};

struct node* search(struct node* root, keytype key)
{
   struct node* p;
   p = root;
   if(p==NULL)
	   return NULL;
   else if(p->key==key)
	   return p;
   else if(p->key>key)
	   return search(p->lchild,key);
   else if(p->key<key)
	   return search(p->rchild,key);
}

void insert(struct node** root, struct node* t)
{
   	if(*root == NULL) 
   		*root = t;
   	else if(t->key < (*root)->key)
	   insert(&((*root)->lchild),t);
   	else if(t->key > (*root)->key)
	   insert(&((*root)->rchild),t);
}

void preorder(struct node* root)
{
	struct node* p = root;
 if(p!=NULL)
 {
    preorder(p->rchild);
	printf("%d ",p->key);
	preorder(p->lchild);
 }
}

void main()
{
	int a[10] = {5,9,1,7,2,8,3,5,2,9};
    int  i;
	struct node* tree = NULL;
	struct node* tmp  = NULL;
	for(i=0;i<10;i++)
	{
		if(!search(tree,a[i])){
	   		tmp = (struct node*)malloc(sizeof(struct node));
	  		tmp->lchild=NULL;
      		tmp->rchild=NULL;
	   		tmp->key=a[i];
	   		insert(&tree, tmp);
		}
	}
	preorder(tree);
	putchar('\n');
}
