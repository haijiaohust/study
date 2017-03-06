#include <iostream>

using namespace std;

void swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

int partition(int a[], int low, int high)
{
	int pivot = a[high];
	int i = low;
	int j;
	for(j = low; j < high; j++)
	{
		if(a[j] < pivot)
		{
			swap(&a[i], &a[j]);
			i++;
		}
	}
	swap(&a[i], &a[high]);

	return i;
}

void quicksort(int a[], int low, int high)
{
	int mid;
	if(low < high)
	{
		mid = partition(a, low, high);
		quicksort(a, low, mid - 1);
		quicksort(a, mid + 1, high);
	}
}

#define MAX_SIZE 10

int main()
{
	int i;
	int a[MAX_SIZE] = {4,4,3,2,4,4,4,14,8,7};
	quicksort(a, 0, MAX_SIZE - 1);
	for(i = 0; i < MAX_SIZE; i++)
		cout << a[i] << ' ';
	cout << endl;

	return 0;
}
