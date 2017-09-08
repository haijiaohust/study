#include <iostream>
using namespace std;

#define LENGTH(a) (sizeof(a) / sizeof(a[0]))

int LICS(int a[], int n)
{
    int *dp = new int[n];
    int i, j;
    for(i = 0; i < n; ++i)
        dp[i] = 1;
    for(i = 1; i < n; ++i)
        for(j = 0; j < i; ++j)
            if(a[j] <= a[i] && (dp[j] + 1) > dp[i])
                dp[i] = dp[j] + 1;
    i = dp[n - 1];
    delete [] dp;
    return i;
}

int binary_search(int a[], int len, int key)
{
    int l = 0;
    int r = len - 1;
    int m;
    while(l <= r){
        m = (l + r) >> 1;
        if(a[m] > key)
            r = m - 1;
        else if(a[m] < key) 
            l = m + 1;
        else return m;
    }
    return l;
}

int LICS_2(int a[], int n)
{
    int *dp = new int[n];
    int len = 1;
    int i, pos;
    dp[0] = a[0];
    for(i = 1; i < n; ++i){
        if(dp[len - 1] <= a[i])
            dp[len++] = a[i];
        else{
            pos = binary_search(dp, len, a[i]);
            dp[pos] = a[i];
        }
    }

    delete []  dp;
    return len;
}

int main()
{
    int a[] = {35, 36, 39, 3, 15, 40, 27, 6, 42};
    cout << "one\t" << LICS(a, LENGTH(a)) << endl;
    cout << "two\t" << LICS_2(a, LENGTH(a)) << endl;

    return 0;
}