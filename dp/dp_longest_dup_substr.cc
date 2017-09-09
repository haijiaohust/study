#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

size_t getCommLen(string &str1, string &str2) {
    size_t i;
    for (i = 0; i < str1.size() && i < str2.size(); i++) {
        if (str1[i] != str2[i])
            break;
    }
    return i;
}
int longest_dup_substr(string &str)
{
    vector<string> strs;
    for (size_t i = 0; i < str.size(); i++) {
        strs.push_back(str.substr(i));
    }
    sort(strs.begin(), strs.end());

    size_t maxLen = 0;
    for (size_t i = 0; i < strs.size()-1; i++) {
        size_t len = getCommLen(strs[i], strs[i+1]);
        maxLen = max(maxLen, len);
    }
    return maxLen;
}

int main()
{
    string str;
    cin >> str;
    cout << longest_dup_substr(str) << endl;

    return 0;
}