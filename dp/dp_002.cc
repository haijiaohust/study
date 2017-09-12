#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d\n", &n);
    vector<int> data(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &data[i]);
    }
    vector<int> sum(n + 1, 0);
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] ^ data[i];
    }

    map<int, int> index;
    index[sum[0]] = 7;
    for (int i = 1; i <= n; i++) {
        if (index[sum[i]] == 0) {
            dp[i] = dp[i - 1];
        } else {
            dp[i] = dp[index[sum[i]] - 7] + 1;
            dp[i] = max(dp[i-1],dp[i]);
        }
        index[sum[i]] = i + 7;
    }

    printf("%d\n", dp[n]);

    return 0;
}