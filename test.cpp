#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
void bfs(vector<vector<int>> &adj, vector<int> &dist, int start) {
    queue<int> q;
 
    dist.assign(adj.size(), -1);
    dist[start] = 0;
    q.push(start);
 
    while (!q.empty()) {
        int node = q.front();
        q.pop();
 
        for (auto nxt : adj[node]) {
            if (dist[nxt] == -1) {
                dist[nxt] = dist[node] + 1;
                q.push(nxt);
            }
        }
    }
}
 
void vivek() {
    int n;
    cin >> n;
 
    vector<vector<int>> adj(n);
 
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
 
        u--;
        v--;
 
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    // First BFS from any node (0)
    vector<int> dist;
    bfs(adj, dist, 0);

    
 
    int mx = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] > dist[mx]) {
            mx = i;
        }
    }
    
    int fist_FN = mx;
    // Second BFS from farthest node
    bfs(adj, dist, mx);

    int sec_FN = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] > dist[sec_FN]) {
            sec_FN = i;
        }
    }

    vector<int> dist2;
    bfs(adj, dist2, sec_FN);

    for(int i = 0;i<n;i++){
        cout<<max(dist[i], dist2[i])<<" ";
    }
    cout<<"\n";
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t = 1;
    // cin >> t;
 
    while (t--) {
        vivek();
    }
 
    return 0;
}