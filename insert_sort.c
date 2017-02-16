#include <stdio.h>

void insert_sort(int a[], int len)
{
	int i, j;
	int key;
	for(i = 1; i < len; i++)
	{
		key = a[i];
		for(j = i - 1; j >= 0 && a[j] > key; j--)
			a[j + 1] = a[j];
		a[j + 1] = key;
	}
}

int main()
{
	int a[] = {5, 2, 4, 6, 1, 3};
	int i;
	insert_sort(a, 6);
	for(i = 0; i < 6; i++)
		printf("%d ", a[i]);
	putchar('\n');

	return 0;
}
