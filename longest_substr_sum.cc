/**
*最大连续子序列和
*输入
*-23 17 -7 11 -2 1 -34
*输出
*21
*处理string到int
*处理输入数组，但是没有告诉数组长度
**/
#include <iostream>
#include <vector>
using namespace std;

int str_int(string s){
    int t = 0;
    for(int i = 0; i < s.length(); ++i)
        t = 10 * t + s[i] - '0';
    return t;
}

int str_to_int(string str)
{
    if(str[0] == '-')
        return 0-str_int(str.erase(0, 1));
    else return str_int(str);
}

long max_sub(vector<int> a)  
{
    int i;
    long max, tmp;
    int len = a.size();
    max = tmp = a[0];
    for (i = 1; i < len; ++i)
    {  
        if (tmp <= 0)  
            tmp = a[i];
        else  
            tmp += a[i];
        if (tmp > max) {  
            max = tmp;
        }  
    }  
    return max;  
}  

long longest(string str)
{
    vector<int> num;
    int pos = 0;
    int t;
    int len = str.length();
    int last = str.rfind(' ', len - 1);
    while(pos < last)
    {
        t = str.find(' ', pos);
        num.push_back(str_to_int(str.substr(pos, t - pos)));
        pos = t + 1;
    }
    num.push_back(str_to_int(str.substr(pos, len - pos)));
    return max_sub(num);
}

int main()
{
    string str;
    getline(cin, str);
    cout << longest(str) << endl;
    return 0;
}
