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
vector<int> parent;
vector<bool> occ;
vector<int> jump;
vector<vector<int>> table;
int mx = 19; // this mx is quite large , any will be reahed only in few cases 
// so improve time we can set mx baaed on the value of N.
// so this max = ceil(LOG2(N)); 

void build(int n){
    table[0] = parent;

    for(int i = mx-1;i>=0;i--){
        for(int node = 1;node<=n;node++){
            table[i][node]= table[i-1][table[i-1][node]];
        }
    }
}

int calJump(int c){
    int curr = jump[c];
    if(occ[curr])return 0;
    int jmp = 1;
    for(int j = mx-1;j>=0;j--){
        int jp = table[j][curr]; //2^j th parent of curr;
        if(occ[jp]) continue;
        else{
            curr = jp;
            jmp += 1<<j;
        }
    }
    occ[curr] = true;
    return jmp;
}
void vivek()
{   
    int n;
    cin >> n;
    // one based indexing
    parent.resize(n+1);
    occ.resize(n+1, false);
    occ[0]= true;
    parent[1] = 0;
    parent[0] = 0;
    loop2(i, n){
        cin >> parent[i];
    }
     jump.resize(n+1);
     loop2(i, n){
        cin >> jump[i];
     } 

     table.resize(mx, vector<int>(n+1, 1));

     build(n);

    for(int i=1;i<=n;i++){
        int ans = calJump(i);
        cout<<ans<<endl;
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    /*is Single Test case?*/ cin >> t;
    while (t--)
    {
        vivek();
    }

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}