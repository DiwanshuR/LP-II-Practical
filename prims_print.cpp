#include<iostream>
#include<vector>
#include<queue>
#include<climits>
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
        void printgraph() {
            cout<<"\n Graph Adjacency List---\n";
            for(int i=1; i<V; i++) {
                cout<<i<<" --> ";
                for(auto nbr: adj[i]) {
                    cout<<"("<<nbr.first<<","<<nbr.second<<") ";
                }
                cout<<endl;
            }
        }

        void prims_mst() {
            //visited 
            vector<bool> visited(V, false);
            vector<int> parent(V, -1);
            vector<int> key(V, INT_MAX); // key = [w,w,w,w,w] value = weight, index = node
            int ans = 0;

            // declare the priority queue as min heap(comparator) to hold active edges- (edge from one vertex in V[] to another in MST set)
            // {w,y}
            priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > Q;
            Q.push({0,1});  // source = 1, weight = 0
            key[1] = 0;

            while(!Q.empty()) {
                pair<int,int> best = Q.top();
                Q.pop();
                int weight = best.first;
                int node = best.second;

                //check if node is visited
                if(visited[node] == true) 
                    continue;
                
                ans += key[node];
                visited[node] = true;

                //add edges starting from y(node) in active edge list(Q) only if not visited
                for( pair<int,int> nbr: adj[node]) {
                    int v = nbr.first;
                    int wt = nbr.second;
                    if(visited[nbr.first] == false && wt < key[v]) {
                        key[nbr.first] = wt;
                        parent[nbr.first] = node;

                        Q.push({key[v], nbr.first});

                    }
                }

            }

            cout<<"\n----Minimum Spanning Tree Edges ---\n";
            for(int i=2; i<V; i++) {
                cout<<parent[i]<<" - "<<i<<" (weight: "<< key[i]<<")\n";
            }

            cout<<"Total weight = "<<ans;
            

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

    g.printgraph();
    g.prims_mst();
    return 0;
}