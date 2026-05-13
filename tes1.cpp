#include <bits/stdc++.h>
#define int long long int
#define no cout << "NO" << endl;
#define yes cout << "YES" << endl;
#define Sort(v) sort(v.begin(), v.end())
#define Sortr(v) sort(v.rbegin(), v.rend())
#define vecpair vector<pair<int, int>>
#define loop1(i, n) for (int i = 0; i < n; i++)
#define loop2(i, n) for (int i = 1; i <= n; i++)
#define print1(x) cout << x << endl;
#define print2(x) cout << x << " ";
#define NL cout << "\n";
#define umap unordered_map
#define all(v) v.begin(), v.end()
using namespace std;

// RATING IS SHIT, YOU ARE HERE JUST FOR FUN!, RATING MAY DECREASES BUT NOT THE EXPERIENCE.
// NEVER SUBMIT A DUMB CODE! YOU DO EVERYTIME REMIND IT!
// SEE EDGE CASES SPECIALLY (0 & 1)
void vivek() {  
    int n; 
    cin >> n;
    vector<vector<char>> grid(n, vector<char>(n));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> grid[i][j];
        }
    }

    // Edge case: grid is 1x1
    if (n == 1) {
        cout << grid[0][0] << endl;
        return;
    }

    string ans = "";
    ans += grid[0][0];

    // 'active' stores the coordinates of the cells we are currently standing on
    vector<pair<int, int>> active;
    active.push_back({0, 0});

    // 'vis' prevents us from processing the same cell twice (e.g. reaching (1,1) from both (0,1) and (1,0))
    vector<vector<bool>> vis(n, vector<bool>(n, false));
    vis[0][0] = true;

    // A path from (0,0) to (n-1, n-1) takes exactly 2*n - 1 characters.
    // We already have 1 character, so we loop 2*n - 2 times.
    for (int step = 1; step < 2 * n - 1; ++step) {
        char min_char = '{'; // '{' is ASCII 123, which is greater than 'z' (122)
        vector<pair<int, int>> next_cells;

        // Step 1: Find the minimum character among all reachable neighbors
        for (auto p : active) {
            int r = p.first;
            int c = p.second;
            
            if (c + 1 < n) min_char = min(min_char, grid[r][c+1]); // Look right
            if (r + 1 < n) min_char = min(min_char, grid[r+1][c]); // Look down
        }

        // Add the best character to our final answer
        ans += min_char;

        // Step 2: Only keep the neighbors that actually have this minimum character
        for (auto p : active) {
            int r = p.first;
            int c = p.second;
            
            // If the right cell is valid, hasn't been visited, AND matches the min_char
            if (c + 1 < n && grid[r][c+1] == min_char && !vis[r][c+1]) {
                vis[r][c+1] = true;
                next_cells.push_back({r, c+1});
            }
            // If the down cell is valid, hasn't been visited, AND matches the min_char
            if (r + 1 < n && grid[r+1][c] == min_char && !vis[r+1][c]) {
                vis[r+1][c] = true;
                next_cells.push_back({r+1, c});
            }
        }
        
        // Update our active list for the next iteration
        active = next_cells;
    }

    cout << ans << endl;
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