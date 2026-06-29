Concept of BIT MASKING

Suppose we want to generate/ store all the elements of a subset, using as less space as possible. What would the most optimal approach.

Suppose is there are N elements in a Set. { Each element represented by its index(say)}.

Then we need N bits to represent the whole set as well as any subet.

A set-bit -> the element is presetn in the subset
else the element is not present.

so those combination of bits would translate into an integer that wouls represent the set;

say subset = {1, 2, 3, 4} and N = 10 {1, 2, ---- , 10}

Which integer would represent this set ? 
so basically we would set the 0th, 1st, 2nd, and the 3rd bits, that would result into interger 15.

If we want to add something into the set, -> set that corresonding bit -> ( 1 << i)^(val) (same for removing an element as well). [first check if the element is preset or not].
If we want to check if a number (i) is present in the set of not -> (1<< (i-1) & val).

-------------------------------------------------------------------------------------------------------------

Example Question:

Problem Statement

Let there be N workers and N jobs. Any worker can be assigned to perform any job, incurring some cost that may vary depending on the work-job assignment. It is required to perform all jobs by assigning exactly one worker to each job and exactly one job to each agent in such a way that the total cost of the assignment is minimized.

Input Format
Number of workers and job: N
Cost matrix C with dimension N*N where C(i,j) is the cost incurred on assigning ith Person to jth Job.

Sample Input
4

[
9 2 7 8
6 4 3 7
5 8 1 8
7 6 9 4
]

Sample Output
13

Constraints
N <= 20

Solution:

```
int cost[21][21];

int dp[21][1 << 21];

int solve(int i, int mask, int&n){
    if(i == n) return 0;


    if(dp[i][mask] != -1){
        return dp[i][mask];
    }

    int ans = INT_MAX;

    for(int j = 0;j<n;j++){ // j represent jth worker 
        if(mask & (1 << j)) { // check if jth bit is set i.e. if jth person available or not
            ans = min(ans, cost[j][i] + solve(i+1, (mask ^ (1 << j)), n));
        }
    }
    return dp[i][mask] = ans;   ₹
}
```
