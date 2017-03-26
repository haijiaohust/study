#include <iostream>
#include <cstring>
using namespace std;

#define LINEAR 1

int main()
{
	const int N = 20;
	int *check = new int[N + 1];
	int *prime = new int[N];
	int cnt = 0;

	memset(check, 0, N + 1);
	memset(prime, 0, N);
#if LINEAR == 1
	for(int i = 2; i <= N; i++)
	{
		if(!check[i])
			prime[cnt++] = i;
		for(int j = i + i; j <= N; j += i)
			check[j] = 1;
	}
#else
	for(int i =2; i <= N; i++)
	{
		if(!check[i])
			prime[cnt++] = i;
		for(int j = 0; j < cnt; j++)
		{
			if(i * prime[j] > N)
				break;
			check[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
#endif

	for(int i = 1; i <= N; i++)
		cout << check[i] << ' ';
	cout << endl;
	for(int i = 0; i < N && prime[i]; i++)
		cout << prime[i] << ' ';
	cout << endl;

	delete[] check;
	delete[] prime;
	return 0;
}