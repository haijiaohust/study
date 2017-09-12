#include <iostream>
using namespace std;

int lowbit(int x)  
{  
    return x&~(x-1);  
}  
  
void find(int a[] , int n)  
{  
    int i , xors;  
    xors = 0;  
	for(i = 0 ; i < n ; ++i)  
	{
		xors ^= a[i];  
	}
    // 三个数两两的异或后lowbit有两个相同，一个不同，可以分为两组  
    int fips = 0;  
    for(i = 0 ; i < n ; ++i)  
	{
		fips ^= lowbit(xors ^ a[i]);  
	}
    // 表示的是：flips=lowbit(a^b)^lowbit(a^c)^lowbit(b^c)   
    int b;    // 假设三个只出现一次的其中一个数为b  
    b = 0;  
    for(i = 0 ; i < n ; ++i)  
    {  
        if(lowbit(xors ^ a[i]) == fips)  
		{
			b ^= a[i];  
		}
    }  
    // 成功找到三个数中一个数  
    cout<<b<<endl;  
} 

int main()
{
	int a[]={1,1,2,2,3,4,4,5,6};
	find(a,sizeof(a)/sizeof(a[0]));

    return 0;
}
