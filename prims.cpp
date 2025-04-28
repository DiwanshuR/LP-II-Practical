#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Graph {
    int V;  //no of vertices
    vector<vector<pair<int,int>>> adj;  //{y,w}

    public:
        Graph(int n) {
            V = n + 1; //just for safe indexing
            adj.resize(V);
        }

        void addEdge(int x, int y, int w) {
            adj[x].push_back({y,w});
            adj[y].push_back({x,w});

        }

        int prims_mst() {
            //visited 
            vector<bool> visited(V, false);
            int ans = 0;

            // declare the priority queue as min heap(comparator) to hold active edges- (edge from one vertex in V[] to another in MST set)
            // {w,y}
            priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > Q;
            Q.push({0,1});  // source = 1, weight = 0

            while(!Q.empty()) {
                pair<int,int> best = Q.top();
                Q.pop();
                int weight = best.first;
                int node = best.second;

                //check if node is visited
                if(visited[node] == true) 
                    continue;
                
                ans += weight;
                visited[node] = true;

                //add edges starting from y(node) in active edge list(Q) only if not visited
                for( pair<int,int> nbr: adj[node]) {
                    if(visited[nbr.first] == false) {
                        Q.push({nbr.second, nbr.first});

                    }
                }

            }

            return ans;

        }
            

};

int main() {

    int n, m;
    cin>>n>>m;
    Graph g(n);
    for(int i=0; i<m; i++) {
        int x, y, w;
        cin>>x>>y>>w;
        g.addEdge(x,y,w);

    }

    cout<<"Minimum Spanning Tree weight = "<<g.prims_mst();
    return 0;
}