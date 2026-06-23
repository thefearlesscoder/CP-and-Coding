#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// DSU (Union-Find) helper to safely handle component connections
struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        // Path compression
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            // Union by rank to keep trees flat
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_i] = root_j;
                rank[root_j]++;
            }
            return true;
        }
        return false; // Cycle detected
    }
};

// The required function to complete
long long solve(int n, vector<vector<int>>& edges) {
    long long total_cost = 0;
    long long msf_cost = 0;

    // 1. Calculate total cost
    for (const auto& edge : edges) {
        total_cost += edge[2];
    }

    // 2. Sort edges descending by cost to find the Maximum Spanning Forest
    sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] > b[2];
    });

    // 3. Build the MSF
    DSU dsu(n);
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        long long cost = edge[2];

        if (dsu.unite(u, v)) {
            msf_cost += cost; // Edge kept
        }
    }

    // 4. The minimum cost to break and add is what's left
    return total_cost - msf_cost;
}

// Boilerplate template
void vivek() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            // A tree/forest with n nodes has n-1 edges
            vector<vector<int>> edges(n - 1, vector<int>(3));
            for (int i = 0; i < n - 1; i++) {
                cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
            }
            cout << solve(n, edges) << "\n";
        }
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vivek();
    return 0;
}