# Important algo to learn

- Diameter of tree graph

- re-rooting DP on Trees 

    HINT: we have to calculate same type of data for every node

    [Example Ques 1](https://codeforces.com/problemset/problem/1092/F) | [Eg Ques 2](https://cses.fi/problemset/task/1133)

    N is generally 10^5 > so brute force(BFS/ DFS) wont't work here.

    In the re-rooting approach, we need pnly 2 dfs calls to calculate the whole thing.

    - we main teo arrays 1. subtree_size/sum[N] 2. dist[N] ( we make updation using DFS in these arrays and get final output. (For details watch video of Why Not DP by Piyush)).
    - initally, dist[n] = {0} and subtree_size[n] = {1 or values corresponding to each node}.
    - dist[i] = dist[i] + dist[all children] + subtree_size[all children].
    - subtree_size[i] = subtree_size[i] + subtree_size[all childres].

-- Code for the CSES problem -- Reference code --
```
//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
//--------------------------------WRITE_HERE-------------------------------------------
 
vector<int>g[200000+1];
vector<int>subtree_size(200000+1);
vector<ll>cost(200000+1);
vector<ll>res(200000+1);
 
void preCalc(int node, int p)
{   subtree_size[node]=1;
    cost[node]=0;
 
    for(int &c:g[node]){
        if(c!=p){
            preCalc(c,node);
            subtree_size[node] += subtree_size[c];
            cost[node] += (cost[c]+subtree_size[c]);
        }
    }
}
 
void dfs(int node,int p){
    res[node]=cost[node];
 
    for(int &c:g[node]){
        if(c!=p){
            cost[node] -= (cost[c]+subtree_size[c]);
            subtree_size[node] -= subtree_size[c];
 
            cost[c] += (cost[node]+subtree_size[node]);
            subtree_size[c] += subtree_size[node];
 
            dfs(c, node);
 
            cost[c] -= (cost[node] + subtree_size[node]);
            subtree_size[c] -= subtree_size[node];
 
            cost[node] += (cost[c] + subtree_size[c]);
            subtree_size[node] += subtree_size[c];
        }
    }
}
 
void _144()
{
    int n;cin>>n;
 
    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
 
    preCalc(1,-1);
    dfs(1,-1);
 
    for(int i=1;i<=n;i++) cout<<res[i]<<" ";
    return;
}
 
//--------------------------------END--------------------------------------------------
 
// Main
int main()
{
//freopen("input.in", "r",stdin);
//freopen("output.out", "w",stdout);
 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    ll t = 1;
    // cin >> t;
    while (t--)
    {
        _144();
    }
}

```

    