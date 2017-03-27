#include <iostream>
using namespace std;

void print(int a[], int len)
{
	for(int i = 0; i < len; i++)
		cout << a[i] << ' ';
	cout << endl;
}

void swap(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void shell_sort(int a[], int len)
{
	int i, j, gap;
	for(gap =  len >> 1; gap > 0; gap >>= 1)
		for(i = gap; i < len; i++)
			for(j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
				swap(&a[j], &a[j + gap]);
}

int main()
{
	int a[] = {49, 38, 65, 97, 26, 13, 27, 49, 4, 4};
	shell_sort(a, 10);
	print(a, 10);

	return 0;
}