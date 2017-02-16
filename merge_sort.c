#include <stdio.h>
#include <stdlib.h>
void merge(int a[], int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int i, j, k;
	int *L = calloc((n1 + 1), sizeof(int));
	int *R = calloc((n2 + 1), sizeof(int));
	for(i = 0; i < n1; i++)
		L[i] = a[p + i];
	L[i] = 65535;
	for(i = 0; i < n2; i++)
		R[i] = a[q + i + 1];	
	R[i] = 65535;
	i = j = 0;
	for(k = p; k <= r; k++)
	{
		if(L[i] > R[j])
		{
			a[k] = R[j];
			j++;
		}
		else{
			a[k] = L[i];
			i++;
		}
	}
}

void merge_sort(int a[], int p, int q)
{
	int mid;
	if(p < q)
	{
		mid = (p + q)/2;
		merge_sort(a, p, mid);
		merge_sort(a, mid + 1, q);
		merge(a, p, mid, q);
	}	
}

int main()
{
	int a[] = {5, 2, 4, 6, 1, 3};
	int i;
	merge_sort(a, 0, 5);
	for(i = 0; i < 6; i++)
		printf("%d ", a[i]);
	putchar('\n');

	return 0;
}
