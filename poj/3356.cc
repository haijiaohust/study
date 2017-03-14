#include <iostream>
#include <string.h>

using namespace std;

const int MAX = 1005;
int n, m;
int dp[MAX][MAX];
char x[MAX], y[MAX];

int main()
{
    while(cin >> n >> x)
    {
        cin >> m >> y;
        for(int i = 0; i <= m; i++)
            dp[0][i] = i;
        for(int i = 1; i <= n; i++)
            dp[i][0] = i;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j - 1] + (x[i - 1] == y[j - 1] ? 0 : 1);
                dp[i][j] = min(dp[i][j], min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
            }
        }
        cout << dp[n][m] << endl;
    }

    return 0;
}
