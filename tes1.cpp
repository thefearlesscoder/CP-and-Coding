#include <bits/stdc++.h>

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#define int long long int
#define Sort(v) sort(v.begin(), v.end())
#define Sortr(v) sort(v.rbegin(), v.rend())
#define loop1(i,n) for(int i=0;i<n;i++)
#define NL cout<<"\n";

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order, order_of_key
// PBDS usage: refer : https://github.com/Priyansh19077/YouTube-links/blob/main/PBDS.cpp
// -------------------------------------------------------------------
int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
long long power(long long a, long long b, long long mod){long long res = 1;while(b){if(b & 1) res = (res * a) % mod;a = (a * a) % mod;b >>= 1;}return res;}
long long modInverse(long long a, long long mod){return power(a, mod - 2, mod);}
long long lcm(long long a, long long b){return (a / gcd(a, b)) * b;}
long long binpow(long a, long b){int res = 1;while(b){if(b & 1) res *= a;a *= a;b >>= 1;}return res;}
//=====================================================================
//=========================seive==========================================
vector<int> sieve(int n){
    vector<bool> prime(n + 1, true);vector<int> ans;
    prime[0] = prime[1] = false;
    for(int i = 2; i <= n; i++){if(prime[i]){ans.push_back(i);
            for(int j = i * i; j <= n; j += i){prime[j] = false;}}
    }
    return ans;
}//=======================================================================
// ===============================Factorial mod========================
int fact(int n, int mod){int res = 1;for(int i = 1; i <= n; i++){res = (res * i) % mod;}return res;}
//=================================nCr modular ==========================
int nCr(int n, int r, int mod){if(r > n) return 0;int num = fact(n, mod);int den = (fact(r, mod) * fact(n-r, mod)) % mod;return (num * modInverse(den, mod)) % mod;
}
// ===============================for debugging==========================
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif


void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

//RATING IS SHIT, YOU ARE HERE JUST FOR FUN!, RATING MAY DECREASES BUT NOT THE EXPERIENCE.
//NEVER SUBMIT A DUMB CODE! YOU DO EVERYTIME REMIND IT!
//SEE EDGE CASES SPECIALLY (0 & 1)

void vivek() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    Sort(a);
    int odd = 0;
    int sz = 1;
    for (int i = 1;i < n;i++) {
        if (a[i] -a[i-1] <= k) {
            sz++;
        } else {
            odd += (sz &1);
            sz = 1;
        }
    }
    odd += (sz & 1);
    cout << (odd <= 1 ? "YES" : "NO") << endl;
}

signed main()
{   
    #ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
    #endif
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