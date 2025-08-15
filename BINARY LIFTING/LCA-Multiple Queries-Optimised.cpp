#include <bits/stdc++.h>
#define int long long int
#define no cout<<"NO"<<endl;
#define yes cout<<"YES"<<endl;
#define Sort(v) sort(v.begin(), v.end())
#define Sortr(v) sort(v.rbegin(), v.rend())
#define vecpair vector<pair<int, int>> 
#define loop1(i,n) for(int i=0;i<n;i++)
#define loop2(i,n) for(int i=1;i<=n;i++)
#define print1(x) cout<<x<<endl;
#define print2(x) cout<<x<<" ";
#define NL cout<<"\n";
#define umap unordered_map
#define all(v) v.begin(), v.end()
using namespace std;

//RATING IS SHIT, YOU ARE HERE JUST FOR FUN!, RATING MAY DECREASES BUT NOT THE EXPERIENCE.
//NEVER SUBMIT A DUMB CODE! YOU DO EVERYTIME REMIND IT!
//SEE EDGE CASES SPECIALLY (0 & 1)
vector<int> level;
vector<int> parent;
vector<vector<int>> adj;
vector<vector<int>> table;
int MX = 10; // log2(1000) ≈ 10

void build(int n){
    table.assign(MX, vector<int>(n + 1, 1)); // Ensure all entries are valid

    table[0] = parent;

    for(int i = 1; i < MX; i++){
        for(int node = 1; node <= n; node++){
            table[i][node] = table[i - 1][table[i - 1][node]];
        }
    }
}

void dfs(int src, int l){
    level[src] = l;
    for (int c : adj[src]) {
        if (c != parent[src]) { // prevents backtracking to parent
            parent[c] = src;
            dfs(c, l + 1);
        }
    }
}

int lca(int u, int v){
    if(level[u] > level[v]){
        swap(u,v);
    }
    //levle[u] < level[v]
    int jump = level[v] - level[u];
    for(int i=MX;i>=0;i--){
        int mask = 1<<i;
        if(jump&(mask))
        {
            v = table[i][v];
        }
    }
    if (u == v) return u;
    for (int i = MX-1; i >= 0; i--) {
        if (table[i][u] != table[i][v]) {
            u = table[i][u];
            v = table[i][v];
        }
    }
    return parent[u];   
}

void vivek()
{   
    adj.clear();
    level.clear();
    parent.clear();
    int n;
    cin >> n;
    adj.resize(n+1); // i based

    for(int i=1;i<=n;i++){
        int c;
        cin >> c;
        for(int j = 1;j<=c;j++){
            int x;
            cin >> x;
            adj[i].push_back(x);
        }
    }

    level.resize(n+1);
    parent.resize(n+1, 0);
    parent[1] = 1;
    dfs(1, 1) ; // to find level and parent of each node;

    build(n);
    int q;
    cin >> q;

    while(q--){
        int u, v;
        cin >> u >> v;
        int ans = lca(u, v);
        cout<<ans<<endl;
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    /*is Single Test case?*/ cin >> t;
    for(int i=1;i<=t;i++)
    {
        cout<<"Case "<<i<<":"<<endl;
        vivek();
    }

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}