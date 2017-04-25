#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(a) (sizeof(a)/sizeof(a[0]))
typedef int ElemType;

struct node{
	ElemType data;
	struct node* next;
};

int insert(struct node** head, ElemType data)
{
	struct node* p = *head;
	struct node *t = (struct node*)malloc(sizeof(struct node));
	if(t){
		t->data = data;
		t->next = NULL;
	}
	else{
		printf("Allocate mem error\n");
		return -1;
	}
	t->next = *head;
	*head = t;
	return 0;
}

void print(struct node* head)
{
	struct node* p = head;
	while(p){
		printf("%p\t%d\t%p\n", p, p->data, p->next);
		p = p->next;
	}
}

struct node* search(struct node* head, ElemType data)
{
	struct node* p = head;
	if(!p)
		return NULL;
	while(p){
		if(p->data == data)
			return p;
		p = p->next;
	}
	return NULL;
}

void destory(struct node** head)
{
	struct node* p = *head;
	struct node* t = NULL;
	while(p){
		t = p->next;
		free(p);
		p = t;
	}
	*head = NULL;
}

void delete_node(struct node* node)
{
	if(!node)
		return;
	struct node* t = node->next;
	memcpy(node, t, sizeof(struct node));
	free(t);
}

void delete_data(struct node* head, ElemType data)
{
	struct node* p = search(head, data);
	if(p)
		delete_node(p);
	else printf("ElemType data=%d not found\n", data);
}

void reverse(struct node** head)
{
	if(!(*head) || !((*head)->next))
		return;
	struct node* p = *head;
	struct node* q = (*head)->next;
	struct node* t = NULL;
	p->next = NULL;
	while(q){
		t = q->next;
		q->next = p;
		p = q;
		q = t;
	}
	*head = p;
}

int main()
{
	ElemType array[] = {1, 2, 3, 4, 5, 6};
	int i;
	struct node* head = NULL;
	struct node* p = NULL;
	for(i = 0; i < LENGTH(array); i++)
		insert(&head, array[i]);

	print(head);
	printf("list\n");
	p = search(head, 4);
	if(p)
		delete_node(p);
	delete_data(head, 4);
	delete_data(head, 3);
	print(head);
	reverse(&head);
	printf("list\n");
	print(head);
	destory(&head);
	//printf("%d %d\n", head->data, head->next->data);

	return 0;
}