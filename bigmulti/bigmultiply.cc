#include <iostream>
#include <vector>
using namespace std;

void str_to_vec(vector<int> &v, string &s)
{
	int len = s.length();
	v.resize(len);
	for(unsigned int i = 0; i < len; ++i)
		v[len - i - 1] = s[i] - '0';
}

int vec_len(vector<int> &v)
{
	int i;
	int len = v.size();
	for(i = len - 1; i >= 0; --i)
		if(v[i])
			break;
	return i;
}

void bigmultiply(vector<int> &v1, vector<int> &v2, vector<int> &v3)
{
	int l1 = v1.size();
	int l2 = v2.size();
	v3.assign(l1 + l2, 0);
	int i, j, x;
	for(i = 0; i < l1; ++i)
		for(j = 0; j < l2; ++j)
			v3[i + j] += v1[i] * v2[j];
	for(i = 0; i < (l1 + l2); ++i)
	{
		v3[i + 1] += v3[i] / 10;
		v3[i] %= 10;
	}
	x = vec_len(v3);
	v3.resize(x + 1);
}

void func(string &s1, string &s2)
{
	if(s1.length() == 0 || s2.length() == 0)
		return;
	if(s1[0] == 0 || s2[0] == 0){
		cout << 0 << endl;
		return;
	}
	int i;
	vector<int> v1, v2, v3;
	str_to_vec(v1, s1);
	str_to_vec(v2, s2);
	bigmultiply(v1, v2, v3);
	for(i = v3.size() - 1; i >= 0; --i)
		cout << v3[i];
	cout << endl;
}

int main()
{
	string s1, s2;
	while(cin >> s1 >> s2)
		func(s1, s2);

	return 0;
}