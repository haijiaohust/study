#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printarray(int p[], int N, int W)
{
    int i, j;
    for(i = 0; i <= N; i++)
	{
		for(j = 0; j <= W; j++)
			printf("%d\t", p[i * (W + 1) + j]);
		putchar('\n');
	}
}

void printknacpack(int s[],int w[], int a, int b, int N, int W)
{
	if(a == 0 || b == 0)
		return;
	if(s[a * (W + 1) + b] == 1)
	{
		printknacpack(s, w, a - 1, b - w[a - 1], N, W);
		printf("%d ", a);
	}
	else
		printknacpack(s, w, a - 1, b, N, W);
}

int main()
{
	const int N = 4;
	const int W = 5;
	int w[4] = {2, 1, 3, 2};
	int v[4] = {12, 10, 20, 15};
	int *p = (int *)malloc((N + 1) * (W + 1) * sizeof(int));
	int *s = (int *)malloc((N + 1) * (W + 1) * sizeof(int));
	memset(p, 0, (N + 1) * (W + 1) * sizeof(int));
	memset(s, 0, (N + 1) * (W + 1) * sizeof(int));
	int i, j;
	for(i = 1; i <= N; i++)
	{
		for(j = 1; j <= W; j++)
		{
			if(w[i - 1] > j)
			{
				p[i  * (W + 1) + j] = p[(i - 1) * (W + 1) + j];
				s[i * (W + 1) + j] = 2;
			}
			else
			{
				if(p[(i - 1) * (W + 1) + j] > p[(i - 1) * (W + 1) + j - w[i - 1]] + v[i - 1])
				{
					p[i * (W + 1) + j] = p[(i - 1) * (W + 1) + j];
					s[i * (W + 1) + j] = 2;
				}
				else
				{
					p[i * (W + 1) + j] = p[(i - 1) * (W + 1) + j - w[i - 1]] + v[i - 1];
					s[i * (W + 1) + j] = 1;
				}
			}
		}
	}
	printarray(p, N, W);
	printf("\n");
	printarray(s, N, W);
	printf("\n");
	printf("the pack we chooseis: ");
	printknacpack(s, w, N, W, N, W);
	printf("\n");
	free(p);
	free(s);

	return 0;
}
