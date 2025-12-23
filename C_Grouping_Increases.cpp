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
void vivek()
{   
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(30, vector<int>(k, 0));
    for(int i = 0;i<30;i++){
        if(n & (1 << i)){ // odd one's
            for(int j = k;j<k;j++){
                a[i][j] = 1;
            }
            if(k%2 == 0){
                a[i][k-1] = 0;
            }
        }
    }
    for(int i = 0;i<k;i++){
        int val = 0;
        for(int j = 0;j<30;j++){
            val += (a[j][i] << j);
        }
        cout<<val<<" ";
    }
    NL
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