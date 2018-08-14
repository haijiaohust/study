#include <stdio.h>
#include <stdlib.h>
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))
#define MAX_LEVEL 10

struct skiplistnode{
	int key;
	int value;
	struct skiplistnode* next[1];	//柔性数组
};
struct skiplist{
	int level;
	struct skiplistnode* head;
};

struct skiplistnode* skiplist_create_node(int level, int key, int value)
{
	int i;
	struct skiplistnode* p = (struct skiplistnode*)malloc(sizeof(struct skiplistnode)
										 + level * sizeof(struct skiplistnode*));
	if(!p){
		printf("alloc node error\n");
		return NULL;
	}
	p->key = key;
	p->value = value;
	for(i = 0; i < level; i++)
		p->next[i] = NULL;

	return p;
}

struct skiplist* skiplist_init()
{
	struct skiplist* sl = (struct skiplist*)malloc(sizeof(struct skiplist));
	if(!sl){
		printf("init skiplist error\n");
		return NULL;
	}
	sl->level = 0;
	sl->head = skiplist_create_node(MAX_LEVEL, 0, 0);

	return sl;
}

void skiplist_destory(struct skiplist* sl)
{
	if(!sl)
		return;
	struct skiplistnode* p = sl->head;
	struct skiplistnode* q = NULL;
	if(!p)
		return;
	while(p){
		q = p->next[0];
		free(p);
		p = q;
	}
	free(sl->head);
	free(sl);
}

struct skiplistnode* skiplist_search(struct skiplist* sl, int key)
{
	int i, k;
	struct skiplistnode* p = NULL;
	struct skiplistnode* q = NULL;
	if(!sl)
		return NULL;
	p = sl->head;
	k = sl->level;
	if(!p)
		return NULL;
	for(i = k - 1; i >= 0; i--){
		while((q = p->next[i]) && (q->key <= key)){
			if(q->key == key)
				return q;
			p = q;
		}
	}
	return NULL;
}

int skiplist_insert(struct skiplist* sl, int key, int value)
{
	int i, k, level;
	struct skiplistnode* p = NULL;
	struct skiplistnode* q = NULL;
	struct skiplistnode* node = NULL;
	struct skiplistnode* update[MAX_LEVEL];
	level = (random() % MAX_LEVEL) + 1;
	node = skiplist_create_node(level, key, value);
	if(!sl)
		return -1;
	if(!node)
		return -1;
	k = sl->level;
	p = sl->head;
	for(i = k - 1; i >= 0; i--){
		while((q = p->next[i]) && (q->key < key))
			p = q;
		update[i] = p;
	}
	if(level > sl->level){
		for(i = sl->level; i < level; i++)
			update[i] = sl->head;
		sl->level = level;
	}
	for(i = 0; i < level; i++)
	{
		node->next[i] = update[i]->next[i];
		update[i]->next[i] = node;
	}
	return 0;
}

int skiplist_del(struct skiplist* sl, int key)
{
	int i, k;
	struct skiplistnode* p = NULL;
	struct skiplistnode* q = NULL;
	struct skiplistnode* update[MAX_LEVEL];
	if(!sl)
		return -1;
	p = sl->head;
	k = sl->level;
	if(!p)
		return -1;
	for(i = k - 1; i >= 0; i--)
	{
		while((q = p->next[i]) && (q->key < key))
			p = q;
		update[i] = p;
	}
	if(q && q->key == key){
		for(i = 0; i < sl->level; i++){
			if(update[i]->next[i] != q)
				break;
			update[i]->next[i] = q->next[i];
		}
		free(q);
		for(i = sl->level - 1; i >= 0; i--)
			if(sl->head->next[i] == NULL)
				sl->level--;
		return 0;
	}
	else return -2;
}

void skiplist_print(struct skiplist* sl)
{
	int i;
	struct skiplistnode* p = NULL;
	struct skiplistnode* q = NULL;
	if(!sl)
		return;
	p = sl->head;
	if(!p)
		return;
	for(i = sl->level - 1; i >= 0; i--){
		p = sl->head;
		printf("%p %p ", p, p->next[i]);
		while(p->next[i]){
			p = p->next[i];
			printf("%d %d %p %p\t", p->key, p->value, p, p->next[i]);
		}
		printf("\n\n");
	}
}

int main()
{
	int i, k;
	struct skiplist* sl = skiplist_init();
	struct skiplistnode* p = NULL;
	for(i = 0; i < 10; i++){
		k = (random() % 10000) + 1;
		p = skiplist_search(sl, k);
		printf("%d %p\n", k, p);
		if(!p)
			skiplist_insert(sl, k, k * 10);
	}
	skiplist_print(sl);
	printf("\n");
	p = NULL;
	p = skiplist_search(sl, 4);
	if(p)
		printf("%d %d %p %p\n", p->key, p->value, p, p->next[0]);
	else printf("error\n");
	printf("\n");
	skiplist_del(sl, 3);
	skiplist_print(sl);
	printf("\n");
	skiplist_del(sl, 5);
	skiplist_print(sl);
	printf("\n");
	skiplist_del(sl, 6);
	skiplist_print(sl);

	skiplist_destory(sl);

	return 0;
}
