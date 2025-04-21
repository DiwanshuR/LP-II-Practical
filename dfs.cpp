#include <bits/stdc++.h>
using namespace std;
void dfs(int node, vector<vector<int>> &gr, vector<bool> &visited) {
    cout<<node<<" ";
    visited[node] = true;
    for(int nbr: gr[node]) {
        if( !visited[nbr] ) {
            dfs(nbr, gr, visited);
        }
    }
}
int main()
{
    
    int v, e;
    cin>>v>>e;
    vector<vector<int>> gr(v+1);
    vector<bool> visited(v+1, false);
    for(int i=0; i<e; i++) {
        int x,y;
        cin>>x>>y;
        gr[x].push_back(y);
        gr[y].push_back(x);
        
        
    }
    dfs(1, gr, visited);

    return 0;
}
