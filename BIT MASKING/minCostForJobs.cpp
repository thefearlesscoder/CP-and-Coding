// Problem Statement

// Let there be N workers and N jobs. Any worker can be assigned to perform any job, 
//incurring some cost that may vary depending on the work-job assignment. 
//It is required to perform all jobs by assigning exactly one worker to each job
// and exactly one job to each agent in such a way that
// the total cost of the assignment is minimized.

// Input Format
// Number of workers and job: N
// Cost matrix C with dimension N*N where C(i,j) is the cost incurred on assigning ith Person to jth Job.

// Sample Input
// 4

// [
// 9 2 7 8
// 6 4 3 7
// 5 8 1 8
// 7 6 9 4
// ]

// Sample Output
// 13

// Constraints
// N <= 20





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
int cost[21][21];
int dp[21][1<<21]; // idx, mask (but locality of reference woul suggest ro keep 1<<21 in first bracket)
// dp[i][mask] = min cost to assign jobs geom i to n, to availve people represented by mask;
int solve(int i, int mask, int &n){

    if(i==n)return 0; 

    if(dp[i][mask] != -1) return dp[i][mask];

    int ans = INT_MAX;

    for(int person = 0;person<n;person++){
        if(mask & (1<<person)){ // if that person is avialble
            ans = min(ans, cost[person][i] + solve(i+1, (mask ^ (1<<person)), n));
        }
    }
    return dp[i][mask] = ans;
}
void vivek()
{
    int n;
    cin >> n;
    loop1(i, n)
    {
        loop1(j, n)
        {
            cin >> cost[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    cout<<solve(0, (1<<n)-1 ,n);
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

/// optimed verison
// #include <bits/stdc++.h>
// using namespace std;

// #define int long long

// const int INF = 1e18;
// int cost[21][21];
// int dp[1 << 20];

// int solve(int mask, int n) {
//     if(mask == (1 << n) - 1) return 0; // all jobs done

//     if(dp[mask] != -1) return dp[mask];

//     int ans = INF;
//     int job = __builtin_popcount(mask); // number of jobs already assigned

//     for(int person = 0; person < n; person++) {
//         if(!(mask & (1 << person))) { // if this person is not yet assigned
//             ans = min(ans, cost[job][person] + solve(mask | (1 << person), n));
//         }
//     }
//     return dp[mask] = ans;
// }

// void vivek() {
//     int n;
//     cin >> n;

//     for(int i = 0; i < n; i++)
//         for(int j = 0; j < n; j++)
//             cin >> cost[i][j];

//     memset(dp, -1, sizeof(dp));
//     cout << solve(0, n) << "\n";
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     vivek();
//     return 0;
// }
