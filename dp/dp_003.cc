#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print_dp(int a)
{
    cout << a << ' ';
}

bool func(vector<int> &coin)
{
	int i;
	int sum;
	int n = coin.size();
	vector<int> dp;
	dp.resize(n);
	if(n <= 2)
		return true;
	dp[n - 1] = coin[n - 1];
	dp[n - 2] = coin[n - 1] + coin[n - 2];
	dp[n - 3] = coin[n - 3] + coin[n - 2];
	for(i = n - 4; i >= 0; --i)
		dp[i] = max(coin[i] + min(dp[i + 2], dp[i + 3]), coin[i] + coin[i + 1] + min(dp[i + 3], dp[i + 4]));
	sum = 0;
	for(i = 0; i < n; ++i)
		sum += coin[i];
    //for_each(dp.begin(), dp.end(), print_dp);
    //cout << endl;
	return dp[0] > (sum - dp[0]);
}

int main()
{
	int values[] ={1,2,4,3,4,8,5,6,12};
	vector<int> coin(values, values + (sizeof(values)/sizeof(values[0])));
	cout << func(coin) << endl;

	return 0;
}
