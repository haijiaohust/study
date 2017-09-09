#include <iostream>
#include <vector>
using namespace std;

#define max(a, b) (((a) > (b)) ? (a) : (b))

int LCS(string &s1, string &s2, int m, int n)
{
    int L[m+1][n+1];
    int i, j;
    for (i = 0; i <= m; ++i){
        for (j = 0; j <= n; j++){
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (s1[i-1] == s2[j-1])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }
    return L[m][n];
}

void print_lcs(vector<vector<int> > &b, string &s1, string &out, int i, int j)
{
    if(i == 0 || j == 0)
        return;
    if(b[i][j] == 0){
        out.append(1, s1[i]);
        print_lcs(b, s1, out, i - 1, j - 1);
    }
    else if(b[i][j] == 1)
        print_lcs(b, s1, out, i - 1, j);
    else print_lcs(b, s1, out, i, j - 1);
}

int LCS_length(string &s1, string &s2, int m, int n)
{
    string out;
    int L[m+1][n+1];
    vector<vector<int> > b(m + 1, vector<int>(n + 1, 0));
    int i, j;
    for (i = 0; i <= m; ++i){
        for (j = 0; j <= n; j++){
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (s1[i - 1] == s2[j - 1]){
                L[i][j] = L[i - 1][j - 1] + 1;
                b[i][j] = 0;
            }
            else if(L[i - 1][j] >= L[i][j - 1]){
                L[i][j] = L[i - 1][j];
                b[i][j] = 1;
            }
            else{
                L[i][j] = L[i][j - 1];
                b[i][j] = 2;
            }
        }
    }
    print_lcs(b, s1, out, m, n);
    cout << out << endl;
    return L[m][n];
}

int main()
{
    string s1("ABCBDAB");
    string s2("BDCABA");
    cout << LCS(s1, s2, s1.length(), s2.length()) << endl;
    cout << LCS_length(s1, s2, s2.length(), s2.length()) << endl;

    return 0;
}
