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
    int n;
    cin >> n;
    string a;
    cin >> a;
    string b;
    cin>>b;

    if(a[0] == ')' || a[n-1] == '(' || b[0] == ')' || b[n-1] == '('){
        cout<<"NO"<<endl;
        return;
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