// DP with bit masking :
// ques 1
// given a set write function to add an element , remove an elemnt and display the set.
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
void add(int &set, int val){
    int bit = val-1;
    set = set | (1<<bit);
}
void display(int set){
    for(int i=0;i<=31;i++){ // int is 32 bit;
        if(set & (1<<i)){
            cout<<i+1<<" "; // if ith bit is set means i+1 is present in the set.
        }
    }
    NL
}
void remove(int &set, int val){ // passed by ref to refect changes
    // inittally check if val is presetn in subset or not
    // for now we assume it is present
    int bit = val - 1;
    set = set ^ (1<<bit);
}
void vivek()
{   
    int set = 15;
    display(set);
    remove(set, 2);
    display(set);
    add(set, 6);
    display(set);
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