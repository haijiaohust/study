#include <iostream> 
#include <cstring> 
using namespace std;
int solve(int layer)  
{  
    int i , j , k;
    int *dp = new int[layer + 1];
    memset(dp, 0, (layer + 1) * sizeof(int));
    dp[0] = 0;
    dp[1] = 1;
    for(i = 2 ; i < (layer + 1) ; ++i)  
    {  
        dp[i] = i;  
        for(j = 1 ; j < i ; ++j)  
        {  
            k = (j >= (1 + dp[i-j])) ? j : (1 + dp[i-j]);  
            if(dp[i] > k)  
                dp[i] = k;  
        }
    }
    i = dp[layer];
    delete[] dp;
    return i;
}  
  
int main(void)  
{  
    int layer;
    while(cin >> layer)
    	cout << solve(layer) << endl;

    return 0;  
}  