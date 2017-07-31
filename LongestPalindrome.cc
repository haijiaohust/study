/**
*最长回文字串
**/
#include <iostream>
#include <cstring>
using namespace std;

int LongestPalindrome(string str, int len)
{
    int max = 0;
    int i, j, t;
    if(str.length() < 1 || len < 1)
        return 0;
    for(i = 0; i < len; i++){
        t = 1;
        //回文字串长度是奇数
        for(j = 1; (i - j) >= 0 && (i + j) < len; j++){
            if(str[i - j] == str[i + j])
                t += 2;
            else break;
        }
        if(t > max)
            max = t;
        t = 0;
        //回文字串长度是奇数
        for(j = 0; (i - j) >= 0 && (i + j + 1) < len; j++){
            if(str[i - j] == str[i + j + 1])
                t += 2;
            else break;
        }
        if(t > max)
            max = t;
    }
    return max;
}
//Manacher算法有错误
int LongestPalindrome_Manacher(string str, int len)
{
    int id = 0, mx = 0, i;
    int *p = new int[2 * len + 1];
    string tmp;
    memset(p, 0, (2 * len + 1) * sizeof(int));
    for(i = 0; i < len; i++){
        tmp.append(1, '#');
        tmp.append(1, str[i]);
    }
    tmp.append(1, '#');

    for(i = 1; i < 2 * len + 1; i++){
        p[i] = (mx > i) ? min(p[2 * id - i], mx - i) : 1;
        while(tmp[i + p[i]] == tmp[i - p[i]])
            p[i]++;
        if(i + p[i] > mx){
            mx = i + p[i];
            id = i;
        }
    }
    mx = 0;
    for(i = 0; i < 2 * len + 1; i++)
        if(p[i] > mx)
            mx = p[i];
    delete[] p;
    return mx - 1;
}

int main()
{
    string str;
    while(cin >> str){
        cout << LongestPalindrome(str, str.length()) << endl;
        cout << LongestPalindrome_Manacher(str, str.length()) << endl;
    }

    return 0;
}
