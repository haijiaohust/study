#include <stdio.h>
void bubble_sort(int a[], int len)
{
	int i, j, tmp;
	int pivot;
	for(i = 0; i < len - 1; i++)
	{
		pivot = 1;
		for(j = len - 1; j > i; j--)
		{
			if(a[j] < a[j - 1])
			{
				tmp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = tmp;
				pivot = 0;	
			}
		}
		if(pivot)
			break;
	}
	printf("%d\n", i);
}

int main()
{
	int a[] = {5, 2, 4, 6, 1, 3};
	int b[] = {1, 2, 4, 3, 5, 6};
	int i;
	bubble_sort(b, 6);
	for(i = 0; i < 6; i++)
		printf("%d ", b[i]);
	putchar('\n');

	return 0;
}
