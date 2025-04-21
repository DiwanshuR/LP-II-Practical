#include <bits/stdc++.h>
using namespace std;

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
    
    queue<int> q;
    int src = 1;
    q.push(src);
    visited[src] = true;
    while(!q.empty()) {
        int sz = q.size();
        while(sz--) {
            int node = q.front(); //this is current node
            q.pop();
            cout<<node<<" ";
            //visit all its neighbours
            for(int nbr: gr[node]) {
                if(visited[nbr] == false) {
                    visited[nbr] = true;
                    q.push(nbr);
                }
            }
        }
        
    }

    return 0;
}
