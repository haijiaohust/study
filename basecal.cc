/**
*有四种运算add/sub/mul/div，分别代表加/减/乘/除
*四种运算只考虑整数，结果也只保留整数，比如5/3=1
*例子1
*输入
*div (mul (add 1 3) 5) 2
*输出
*10
**/
#include <iostream>
#include <stack>
using namespace std;

int str_int(string s){
    int t = 0;
    for(int i = 0; i < s.length(); ++i)
        t = 10 * t + s[i] - '0';
    return t;
}
string int_str(int a)
{
    string out;
    int t = a;
    int len;
    if(a == 0){
    	out.push_back('0');
    	return out;
    }
    while(t){
        out.push_back((t % 10) + '0');
        t /= 10;
    }
    len = out.length();
    for(int i = 0; i < len/2; ++i)
    {
        char c = out[i];
        out[i] = out[len - i - 1];
        out[len - i - 1] = c;
    }
    return out;
}

string base(string str)
{
    int tb;
    int tc;
    int r;
    int found, t;
    string a, b, c;
    found = str.find(' ');
    a = str.substr(0, found);
    t = str.find(' ', found + 1);
    b = str.substr(found + 1, t - found - 1);
    c = str.substr(t + 1, str.length() - t - 1);
    tc = str_int(c);
    tb = str_int(b);
    if(!a.compare("add"))
        r = tb + tc;
    else if(!a.compare("sub"))
        r = tb - tc;
    else if(!a.compare("mul"))
        r = tb * tc;
    else if(!a.compare("div"))
        r = tb / tc;
    return int_str(r);
}

void cal(string &s, int i, int j)
{
    string str = s.substr(i + 1, j - i - 1);
    string t = base(str);
    s.replace(i, j - i + 1, t);
}

string result(string s)
{
    stack<int> st;
    int i;
    for(i = 0; i < s.length(); ++i){
        if(s[i] == '(')
            st.push(i);
        else if(s[i] == ')'){
            cal(s, st.top(), i);
            i = st.top();
            st.pop();
        }
    }
    return base(s);
}

int main()
{
    string s;
    while(getline(cin, s))
        cout << result(s) << endl;
    return 0;
}