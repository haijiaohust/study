#include<stdio.h>
#include<string.h>
#define N   10000
int main(){
  int n;
  int a[N];
  n=1;
  memset(a,0,sizeof(a));
  a[1]=1;
  int k;
  scanf("%d",&k);
  while (k--){
    int x=0;
    for (int i=1;i<=n;i++){
        a[i]=a[i]*2+x;
        x=a[i]/10;
        a[i]%=10;
    }
    if (x) a[++n]=x;
  }
  for (int i=n;i>=1;i--)printf("%d",a[i]);
  putchar('\n');
  return 0;
}