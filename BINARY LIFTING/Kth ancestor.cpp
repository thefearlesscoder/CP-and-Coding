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
int MX = 17;
vector<vector<int>> table;
void build(vector<int>& parent){
    int n = parent.size();
    table.resize(MX, vector<int>(n, 0));
    for(int i=0;i<n;i++){
        table[0][i] = parent[i]; // 2^0 -> 1st parent;
    }

    for(int i=1;i<MX;i++){
        for(int j = 0;j<n;j++){
            table[i][j] = table[i-1][table[i-1][j]]; // parent of previous parent;
        }
    }
}
int query(int node, int k){
    // sirdt MX tak jane ki jaroorat hai
    for(int i=0;i<MX;i++){
        int mask = 1<<i;

        if(k&mask){
            node = table[i][node];
        }
    }
    return node;
}
void vivek()
{   
    int n;
    cin >> n;
    vector<int> parent(n);
    loop1(i, n){
        cin >> parent[i];
    }
    build(parent);

    int q;
    cin >> q; // q queries;

    while(q--){
        int node, k;
        cin >> node >> k; // node ka kth ancestor(parent);
        
        int ans = query(node, k);
        cout<< ans<<endl;
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // /*is Single Test case?*/ cin >> t;
    while (t--)
    {
        vivek();
    }

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}