#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class DSU {
    vector<int> parent;
    vector<int> rank;
public:
    DSU(int n) {
        parent.resize(n+1);
        rank.resize(n+1);
        
        //iniialise parent and rank
        for(int i=0; i<=n; i++) {
            parent[i] = -1;  //the i itself is the leader element uska koi baap nhi and initially toh sab aise hi hote hai
            rank[i] = 1;      //intially all are independent and so size = 1, rank = 1
        }
    }

    

    int find(int x) {
        if(parent[x] == -1) {
            //that element itself is the set id or the root(leader)
            return x;
        }
        //means it has some parent so search for parent
        return parent[x] = find(parent[x]);
    }

    bool Union(int x, int y) {
        //find the set ids of both
        int s1 = find(x);
        int s2 = find(y);
        //if set ids are same (same root element) then adding another edge would create a cycle so return true 
        if(s1 == s2)
            return true;
        
        //merge s2 into s1 or s1 into s2 but optimal is to merge a smaller size set to larget size set
        if(rank[s1] > rank[s2]) {
            //rank means the size only so merge s2 into s1
            parent[s2] = s1;
            rank[s1] += rank[s2];  //size bhi toh badhega

        }
        else {
            //merge s1 into s2
            parent[s1] = s2;
            rank[s2] += rank[s1];
        }
        return false;
    }
};

class Graph {
    public:
    //edge list(x,y,w) but for sorting is based on first element so store as (w,x,y)
    vector<vector<int>> edgeList;
    int V;

    Graph(int n) {
        V = n + 1;

    }

    void addEdge(int x, int y, int w) {
        edgeList.push_back({w,x,y});
    }

    int kruskal_mst() {
        sort(edgeList.begin(), edgeList.end());
        int ans = 0;
        DSU d(V);

        vector<pair<int,int>> mstEdges;

        //sorted acc to weights now go through each edge and add it but not form a cycle

        for( vector<int> &edge: edgeList) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];
            if(d.find(x) != d.find(y)) {
                //same leader raha toh cycle ban jaayega toh skip karo 
                //alag hai toh union kardo
                ans += w;
                d.Union(x,y);
                mstEdges.push_back({x,y});
            }
        }

        //print the mst
        cout<<"\n ----MST---- \n";
        for(auto &edge: mstEdges) {
            cout<<edge.first<<" - "<<edge.second<<endl;
        }
        return ans;
    }

};

int main() {

    int n,m; cin>>n>>m;
    Graph g(n);
    for(int i=0; i<m; i++) {
        int x,y,w; cin>>x>>y>>w;
        g.addEdge(x,y,w);
    }
    cout<<"Ans = "<<g.kruskal_mst();
    return 0;
}