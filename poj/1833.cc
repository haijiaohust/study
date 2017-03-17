#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
	int m,  n, k;
	scanf("%d", &m);
	int p[1024];
	while(m--)
	{
		scanf("%d%d", &n, &k);
		for(int i = 0; i < n; i++)
			scanf("%d", &p[i]);
		while(k--)
			next_permutation(p, p + n);
		
		for(int i = 0; i < n - 1; i++)
			printf("%d ", p[i]);
		printf("%d\n", p[n - 1]);
	}

	return 0;
}