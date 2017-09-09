#include <iostream>
using namespace std;

int longest_substr(string &s1, string &s2)
{
    int m = s1.length();
    int n = s2.length();
    int L[m+1][n+1];
    int i, j;
    int maxlen = 0;
    int pos;
    for (i = 0; i <= m; ++i){
        for (j = 0; j <= n; j++){
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (s1[i-1] == s2[j-1]){
                L[i][j] = L[i-1][j-1] + 1;
                if(maxlen < L[i][j]){
                    pos = i;
                    maxlen = L[i][j];
                }
            }
            else
                L[i][j] = 0;
        }
    }
    cout << s1.substr(pos - maxlen, maxlen)<< endl;
    return maxlen;
}

int main()
{
    string s1("acbac");
    string s2("acaccbabb");
    cout << longest_substr(s1, s2) << endl;

    return 0;
}
