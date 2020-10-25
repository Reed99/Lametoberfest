#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;

struct Edge {
    int u; 
    int v;
    friend bool operator==(const Edge& lhs, const Edge& rhs) {
        return (lhs.u == rhs.u && lhs.v == rhs.v) || (lhs.u == rhs.v && lhs.v == rhs.u);
    }
    Edge(int i, int j){
        u=i;
        v=j;
    }
};

int main()
{
    int edges;
    map<int, vector<int> > graph;

    cin >> edges;

    int u, v;
    for(int i = 0; i < edges; ++i) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    map<int, bool> visited;
    map<int, int> parentOf;
    vector<Edge> openRoads;
    queue<int> Q;

    Q.push(u);
    visited[u] = true;
    parentOf[u] = u;

    while(!Q.empty()) {
        v = Q.front();
        Q.pop();

        for(int w : graph[v]) {
            if(!visited[w]) {
                visited[w] = true;
                parentOf[w] = v;
                openRoads.push_back({v, w});
                Q.push(w);
            }
        }
    }

                vector<Edge> closedRoads;
                bool c = false;
                for(const auto& kv : graph) {
                    for(int i : kv.second) {
                        c = false; 
                        Edge t(kv.first, i);
                        for(const auto& te : openRoads){
                            if (t == te) {
                                c = true;
                            }
                        } 
                        for(const auto& te : closedRoads){
                            if (t == te) {
                                c = true;
                            }
                        } 
                        if (c == false) closedRoads.push_back(t);
                    }
                }

    cout << "closed roads: " << endl;
    
    for(const Edge& edge : closedRoads) {
        cout << "("<<edge.u<<","<<edge.v<<")"<<endl;
    }
    cout << endl;

while(true) {
    int a, b;
    cin >> a >> b;
    if(a == 0 && b == 0) break;

    queue<int> as;
    stack<int> bs;

    int x = a;
    while(parentOf[x] != x) {
        as.push(x);
        x = parentOf[x];
    }
    as.push(x);

    x = b;
    while(parentOf[x] != x) {
        bs.push(x);
        x = parentOf[x];
    }


    while(!as.empty()) {
        cout << as.front() << " ";
        as.pop();
    }


    while(!bs.empty()) {
        cout << bs.top() << " ";
        bs.pop();
    }
    cout << endl;
    cout << endl;

}

    return 0;
}