# Important algo to learn

- Diameter of tree graph

- re-rooting DP on Trees 

    HINT: we have to calculate same type of data for every node

    [Example Ques 1](https://codeforces.com/problemset/problem/1092/F) | [Eg Ques 2](https://cses.fi/problemset/task/1133)

    N is generally 10^5 > so brute force(BFS/ DFS) wont't work here.

    In the re-rooting approach, we need pnly 2 dfs calls to calculate the whole thing.

    - we main teo arrays 1. subtree_size/sum[N] 2. dist[N] ( we make updation using DFS in these arrays and get final output. (For details watch video of Why Not DP by Piyush)).
    - initally, dist[n] = {0} and subtree_size[n] = {1 or values corresponding to each node}.
    - dist[i] = dist[i] + dist[all children] + subtree_size[all children].
    - subtree_size[i] = subtree_size[i] + subtree_size[all childres].

    