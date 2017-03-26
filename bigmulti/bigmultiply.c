#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ch_stoi(int a[], char *b)
{
	int len = strlen(b);
	int i;
	for(i = 0; i < len; i++)
		a[i] = b[len - 1 - i] - '0';
}

void bigmultiply(int a[], int b[], int c[], int lena, int lenb)
{
	int i, j;
	for(i = 0; i < lena; i++)
		for(j = 0; j < lenb; j++)
			c[i + j] += a[i] * b[j];
	for(i = 0; i < lena + lenb; i++)
	{
		c[i + 1] += c[i] / 10;
		c[i] = c[i] % 10;
	}
}

int len_int(int a[], int len)
{
	int i;
	for(i = len - 1; i >= 0; i--)
		if(a[i])
			return i + 1;
}

int main()
{
	int i;
	char s1[1024], s2[1024];
	scanf("%s%s", s1, s2);
	int lena = strlen(s1);
	int lenb = strlen(s2);
	int *a = (int *)calloc(lena, sizeof(int));
	int *b = (int *)calloc(lenb, sizeof(int));
	int *c = (int *)calloc(lena + lenb, sizeof(int));
	ch_stoi(a, s1);
	ch_stoi(b, s2);
	bigmultiply(a, b, c, lena, lenb);
	for(i = len_int(c, lena + lenb) - 1; i >= 0; i--)
		printf("%d", c[i]);
	printf("\n");
	free(a);
	free(b);
	free(c);

	return 0;
}