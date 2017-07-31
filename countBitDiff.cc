/**
*两个int32整数m和n的二进制表达，有多少个位(bit)不同
*示例
*输入：1999 2299 
*输出：7
**/
#include <iostream>
using namespace std;
/**
*数字二进制中为1的bit数
**/
int bit_count(int n){
    int num =0;
    while(n != 0){
        num++;
        n = n & (n - 1);
    }
    return num++;
}
int countBitDiff(int m, int n) {
    int r = m ^ n;
    return bit_count(r);
}

int main()
{
    int m, n;
    while(cin >> m >> n)
        cout << countBitDiff(m, n) << endl;

    return 0;
}
