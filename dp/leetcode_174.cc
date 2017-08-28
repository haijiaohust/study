#include <iostream>
#include <climits>
#include <vector>
using namespace std;
class Solution {
public:
    int calculateMinimumHP(vector<vector<int> >& dungeon) {
        int i, j;
        int m, n;
        m = dungeon.size();
        n = dungeon[0].size();
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m - 1][n] = 1;
	    for(i = m - 1; i >= 0; --i){
		    for(j = n - 1; j >= 0; --j)
		    {
			    dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j];
			    dp[i][j] = max(1, dp[i][j]);
		    }
	    }
	    return dp[0][0];
    }
};

int main()
{
    vector<vector<int> > s;
    vector<int> t;
    int i, j;
    int m, n;
    cin >> m >> n;
    for(i = 0; i < m; ++i){
        t.clear();
        t.resize(n);
        for(j = 0; j < n; ++j)
            cin >> t[j];
        s.push_back(t);
    }
    Solution a;
    cout << a.calculateMinimumHP(s) << endl;

    return 0;
}
