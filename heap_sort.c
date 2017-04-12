#include <stdio.h>

#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)
#define PARENT(i) ((i % 2) ? (i / 2) : (i / 2 - 1))

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
//down to top approach
void MAX_HEAPIFY(int a[], int i, int heapsize)
{
    int largest;
    int l, r;
    l = LEFT(i);
    r = RIGHT(i);
    if(l < heapsize && a[l] > a[i])
		largest = l;
    else largest = i;
    if(r < heapsize && a[r] > a[largest])
        largest = r;
    if(largest != i)
    {
		swap(&a[i], &a[largest]);
		MAX_HEAPIFY(a, largest, heapsize);
    }
}

void BUILD_MAX_HEAP(int a[], int len)
{
    int i;
    for(i = PARENT(len - 1); i >= 0; i--)
		MAX_HEAPIFY(a, i, len);
} 

void HEAP_SORT(int a[], int len)
{
    int i;
    BUILD_MAX_HEAP(a, len);
    for(i = len - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);
		MAX_HEAPIFY(a, 0, i);
    }	
}

//top to down approach
void insert_to_heap(int heap[], int i)
{
	int p = PARENT(i);
	while(p >= 0 && heap[p] < heap[i]){
		swap(&heap[p], &heap[i]);
		i = p;
		p = PARENT(p);
	}
}
void build_max_heap(int heap[], int len)
{
	int i;
	for(i = 1; i < len; i++)
		insert_to_heap(heap, i);
}
void heap_sort(int heap[], int len)
{
	int i;
	build_max_heap(heap, len);
	for(i = len - 1; i > 0; i--)
	{
		swap(&heap[0], &heap[i]);
		MAX_HEAPIFY(heap, 0, i);
	}
}

int main()
{
	int a[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	int b[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	int len = 10;
	int i;
	HEAP_SORT(a, len);
	for(i = 0; i < len; i++)
		printf("%d ", a[i]);
	putchar('\n');

	heap_sort(b, len);
	for(i = 0; i < len; i++)
		printf("%d ", b[i]);
	putchar('\n');
	return 0;
}
