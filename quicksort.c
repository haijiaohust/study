#include <stdio.h>

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int partition(int a[], int p, int r)
{
    int x = a[r];
    int i = p - 1;
    int j;
    for(j = p; j <= r - 1; j++)
    {
		if(a[j] <= x)
		{
	    	i++;
	    	swap(&a[i], &a[j]);
		}
    }
    swap(&a[i + 1], &a[r]);

    return i + 1;
}
void quicksort(int a[], int p, int r)
{
    int t;
    if(p < r)
    {
		t = partition(a, p, r);
		quicksort(a, p, t - 1);
		quicksort(a, t + 1, r);
    }
}

int main()
{
	int a[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	int len = 10;
	int i;
	quicksort(a, 0, len - 1);
	for(i = 0; i < len; i++)
		printf("%d ", a[i]);
	putchar('\n');

	return 0;
}
