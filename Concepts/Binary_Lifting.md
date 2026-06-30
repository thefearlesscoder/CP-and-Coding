# Binary Lifting (Quick Revision)

## What it is
- Technique to answer ancestor and LCA queries on a tree in `O(log N)` per query.
- Precompute `up[v][k]` = 2^k-th ancestor of node `v`.
- Useful for: LCA, k-th ancestor, distance queries.

## Key ideas
- Do a DFS/BFS to compute `depth[v]` and `parent[v]`.
- Build `up[v][0] = parent[v]`.
- For `k > 0`: `up[v][k] = up[ up[v][k-1] ][k-1]`.
- Maximum `K = floor(log2(N))`.

## Preprocessing time
- `O(N log N)` to build the `up` table.
- `O(N)` to compute depths and parents by DFS/BFS.

## Query patterns
- Raise a node by `d` levels using binary decomposition of `d`.
- LCA of `u` and `v`:
  1. Lift deeper node to same depth.
  2. If equal return it.
  3. Lift both nodes up from highest power down until parents differ.
  4. Return parent of either node.

## Common formula
- `kthAncestor(v, d)` lifts `v` by `d`:
  - for each bit `i` in `d`: if set, `v = up[v][i]`.

## Why it works
- The table encodes binary jumps, so any distance can be represented as sum of powers of two.
- We only need `log N` levels because `2^K >= N` covers the tree height.

## Short checklist
- [ ] Build adjacency list
- [ ] Compute `depth` and `parent`
- [ ] Initialize `up[v][0]`
- [ ] Build `up[v][k]` for `k=1..K`
- [ ] Use same-depth lifting for LCA
- [ ] Use binary lifting for k-th ancestor if needed

## Minimal C++ code
```cpp
#include <bits/stdc++.h>
using namespace std;

int N, LOG;
vector<vector<int>> adj;
vector<vector<int>> up;
vector<int> depth;

void dfs(int u, int p) {
    up[u][0] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

void build(int root = 1) {
    LOG = 1;
    while ((1 << LOG) <= N) LOG++;
    up.assign(N + 1, vector<int>(LOG));
    depth.assign(N + 1, 0);

    dfs(root, 0);
    for (int j = 1; j < LOG; j++) {
        for (int v = 1; v <= N; v++) {
            int mid = up[v][j - 1];
            up[v][j] = mid ? up[mid][j - 1] : 0;
        }
    }
}

int lift(int v, int k) {
    for (int j = 0; v && j < LOG; j++) {
        if (k & (1 << j)) {
            v = up[v][j];
        }
    }
    return v;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    u = lift(u, depth[u] - depth[v]);
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    adj.assign(N + 1, {});
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    build(1);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
    return 0;
}
```

## Quick usage notes
- Root can be `1` or any node.
- If tree is 0-indexed, adjust arrays and loops to `0..N-1`.
- `lift(v, d)` returns `0` if ancestor does not exist.
- `lca(u, v)` works only after depths and `up` are built.

## Memory
- `up` uses `O(N log N)` space.
- `depth` uses `O(N)`.

## Good to remember
- Binary lifting is the standard way to solve LCA in `O(log N)`.
- It is also useful for answering `k`-th ancestor queries quickly.
- Always align depths first before comparing ancestors.
