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


class SegmentTree{
    public:

    vector<int> seg;
    vector<int> lazy;
    vector<int> arr;
    
    SegmentTree(int n, vector<int> a){
        seg.resize(4*n, 0);
        lazy.resize(4*n, 0);
        arr.resize(n);
        arr = a;
    }
    void build(int root, int low, int high){
        if(low == high){ 
            seg[root] = arr[low];
            return;
        }

        int mid = low + (high-low)/2;

        build(2*root+1, low, mid);
        build(2*root+2, mid+1, high);
        seg[root] = seg[2*root+1] + seg[2*root+2];// sice we need range sum;
    }

    void rangeUpdate(int root, int low, int high, int l, int r, int val){
        //apply pending updates
        if (lazy[root] != 0) {
            seg[root] = (seg[root] + (high - low + 1) + lazy[root])%10;
            // if(seg[root]>9)seg[root] = 0;
            if (low != high) {
                lazy[2 * root + 1] = (lazy[2 * root + 1] + lazy[root])%10;
                lazy[2 * root + 2] = (lazy[2 * root + 2] + lazy[root])%10;
            }
            lazy[root] = 0;
        }

        if(r<low || l>high || low > high) return;

        if(l<=low &&  high<=r){
            seg[root] = seg[root] + (high - low + 1) + val;
            if(seg[root] > 9) seg[root] = 0;
            if (low != high) {
                lazy[2 * root + 1] += val;
                lazy[2 * root + 2] += val;
            }
            return;
        }
        // partial overlap
        int mid = low + (high-low)/2;
        rangeUpdate(2*root+1, low, mid, l, r, val);
        rangeUpdate(2*root+2, mid+1, high, l, r, val);
        seg[root] = seg[2*root+1] + seg[2*root+2];
    }

    int querySum(int root, int low, int high, int l, int r) {
        if (lazy[root] != 0) {
            seg[root] = (seg[root] +  (high - low + 1) * lazy[root])%10;
            if (low != high) {
                lazy[2 * root + 1] =  (lazy[2 * root + 1]+lazy[root])%10;
                lazy[2 * root + 2] = (lazy[2 * root + 2] + lazy[root])%10;
            }
            lazy[root] = 0;
        }

        if (r < low || l > high || low > high) return 0; // no overlap

        if (l<=low && high<=r) return seg[root]; // total overlap

        // partial overlap
        int mid = (low + high) / 2;
        return querySum(2 * root + 1, low, mid, l, r) +
               querySum(2 * root + 2, mid + 1, high, l, r);
    }
};
void vivek()
{   
    int n, m;
    cin >> n;
    string s;
    cin >> s;

    
    vector<int> arr(n);
    loop1(i, n){
        arr[i] = s[i]-'0';
    }

    int m;
    cin >> m;

    SegmentTree ST(n, arr);
    while(m--){
        int a, b;
        cin >> a >> b;
        cout<<ST.querySum(0, 0, n-1, a, b)<<endl;
        ST.rangeUpdate(0, 0, n-1, a,b, 1);

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