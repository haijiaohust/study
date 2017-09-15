#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void toplogic_sort(vector<vector<int> > &adj, vector<int> &indegre, vector<int> &out)
{
    int n = adj.size();
    int i, t;
    stack<int> st;
    for(i = 0; i < n; ++i)
        if(indegre[i] == 0)
            st.push(i);
    while(!st.empty()){
        t = st.top();
        out.push_back(t);
        st.pop();
        for(vector<int>::iterator it = adj[t].begin(); it != adj[t].end(); ++it)
        {
            indegre[*it]--;
            if(indegre[*it] == 0)
                st.push(*it);
        }
    }
}

int main()
{
    vector<vector<int> > adj;
    vector<int> indegre;
    vector<int> out;
    
    int i, n, m, t, p;
    cin >> n >> m;
    adj.resize(n);
    indegre.assign(n, 0);
    for(i = 0; i < m; ++i){
        cin >> p >> t;
        adj[p].push_back(t);
        indegre[t]++;
    }

    toplogic_sort(adj, indegre, out);
    
    if(out.size() != n)
        cout << "None" << endl;
    else{
        for(i = 0; i < n - 1; ++i)
            cout << out[i] << ' ';
        cout << out[n - 1] << endl;
    }
    return 0;
}