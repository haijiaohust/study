#include <iostream>
#include <stack>
using namespace std;

template<typename T>
void swap(T* a, T* b)
{
    T c = *a;
    *a = *b;
    *b = c;
}

int partition(int a[], int l, int h)
{
    int pivot = a[h];
    int i, j;
    i = l;
    for(j = l; j < h; ++j){
        if(a[j] < pivot){
            swap(&a[i], &a[j]);
            ++i;
        }
    }
    swap(&a[i], &a[h]);
    return i;
}

void quick_sort(int a[], int l, int h)
{
    stack<int> st;
    int m = partition(a, l, h);
    if(l < h){
        if(l < (m - 1)){
            st.push(l);
            st.push(m - 1);
        }
        if((m + 1) < h){
            st.push(m + 1);
            st.push(h);
        }
        while(!st.empty()){
            int p2 = st.top();
            st.pop();
            int p1 = st.top();
            st.pop();
            int md = partition(a, p1, p2);
            if(p1 < (md - 1)){
                st.push(p1);
                st.push(md - 1);
            }
            if((md + 1) < p2){
                st.push(md + 1);
                st.push(p2);
            }
        }
    }
}

int main()
{
    int a[] = {0,1,2,10,4,5};
    quick_sort(a, 0, 5);
    for(int i = 0; i < 6; ++i)
        cout << a[i] << ' ';
    cout << endl;

    return 0;
}