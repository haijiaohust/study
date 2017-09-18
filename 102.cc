#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int str_int(string s){
    unsigned int i;
    int t = 0;
    for(i = 0; i < s.length(); ++i)
        t = 10 * t + s[i] - '0';
    return t;
}

bool comp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first < b.first;
}

void func(string &s)
{
    vector<pair<int, int> > out;
    vector<pair<int, int> > interval;
    unsigned int i;
    int n1, n3, n4;
    n1 = 0;
    n3 = s.find(',', 0);
    n4 = s.find(' ', 0);
    while(n4 != string::npos){
        interval.push_back(pair<int, int>(str_int(s.substr(n1, n3 - n1)), str_int(s.substr(n3 + 1, n4 - n3 - 1))));
        n1 = n4 + 1;
        n3 = s.find(',', n4 + 1);
        n4 = s.find(' ', n4 + 1);
    }
    interval.push_back(pair<int,int>(str_int(s.substr(n1, n3 - n1)), str_int(s.substr(n3 + 1, s.length() - n3 - 1))));
    //for(i = 0; i < interval.size(); ++i)
    //    cout << interval[i].first << ' ' << interval[i].second << endl;
    sort(interval.begin(), interval.end(), comp);
    out.push_back(interval[0]);
    for(i = 1; i < interval.size(); ++i)
    {
        if(out.back().second <= interval[i].first)
            out.push_back(interval[i]);
        else out.back().second = max(out.back().second, interval[i].second);
    }
    for(i = 0; i < out.size() - 1; ++i)
        cout << out[i].first << ',' << out[i].second << ' ';
    cout << out[out.size() - 1].first << ',' << out[out.size() - 1].second << endl;
}

int main()
{
    string s;
    while(getline(cin, s))
        func(s);

    return 0;
}
