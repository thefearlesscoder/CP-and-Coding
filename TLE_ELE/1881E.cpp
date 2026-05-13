#include <bits/stdc++.h>
#include<iostream>
#include <climits>

#define int long long int

using namespace std;

int solve(int idx, vector<int> &a, vector<int> &dp){
    int n = a.size();

    if(idx >= n) return 0;

    if(dp[idx]  != -1) return dp[idx];

    int take = LLONG_MAX;
    
    int not_take = 1 + solve(idx + 1, a, dp);

    if(idx + a[idx] + 1 <= n){
        take = solve(idx + a[idx] + 1, a, dp);
    }

    return dp[idx] = min(take, not_take);
}

void vivek(){   
    int n;
    cin >> n;

    vector<int> a(n);

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> dp(n+1, -1);
    int ans = solve(0, a, dp);

    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    cin >> t;

    while(t--){
        vivek();
    }

    return 0;
}