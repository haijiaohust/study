/**
*16进制字符串转换成数字10进制，int可以包含的范围内
*hex_to_dec()是最一般的想法，从个位开始做加法
*hex_to_dec1()是从最高位开始，
*两个函数都要注意，16进制可以用移位运算
*当时没有很好考虑：
*正数两种方法只要在int范围内都是正确的
*其实负数也是，负数最高位1，做加法后溢出，就成了负数
**/
#include <iostream>

using namespace std;

int hex_to_dec(string str)
{
    int out = 0;
    int base = 1;
    int len = str.length();
    for(int i = len - 1; i > 1; i--){
        if(str[i] >= '0' && str[i] <= '9')
            out += base * (str[i] - '0');
        else if(str[i] >= 'a' && str[i] <= 'f')
            out += base * (str[i] - 'a' + 10);
        else if(str[i] >= 'A' && str[i] <= 'F')
            out += base * (str[i] - 'A' + 10);
        base <<= 4;
    }
    return out;
}

int hex_to_dec1(string str)
{
    int out = 0;
    int len = str.length();
    int tmp;
    for(int i = 2; i < len; i++){
        if(str[i] >= '0' && str[i] <= '9')
            tmp = str[i] - '0';
        else if(str[i] >= 'a' && str[i] <= 'f')
            tmp = str[i] - 'a' + 10;
        else if(str[i] >= 'A' && str[i] <= 'F')
            tmp = str[i] - 'A' + 10;
        out = (out << 4) + tmp;
    }
    return out;
}

int main()
{
    string str;
    while(cin >> str){
        cout << hex_to_dec(str) << endl;
        cout << hex_to_dec1(str) << endl;
    }

    return 0;
}
