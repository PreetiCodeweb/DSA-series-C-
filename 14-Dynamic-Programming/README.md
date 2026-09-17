# Dynamic Programming — C++ DSA Notes

## Overview
DP solves problems with overlapping subproblems and optimal substructure by caching subproblem
results. Approach: define state, find recurrence, choose base cases, then implement top-down (memoized
recursion) or bottom-up (tabulation). Master 1D and 2D DP before touching bitmask/tree/digit DP.

## How to Recognize This Pattern
- "Count ways to do X" / "min/max cost to achieve X" -> DP
- Choices at each step affecting future state -> DP
- "Subsequence" (not substring) problems -> DP (often O(n^2))
- Grid path problems -> 2D DP
- "Partition into subsets with property" -> subset-sum style DP

## Core Templates (C++)
### Top-Down Memoization Skeleton
```cpp
unordered_map<int,long long> memo;
long long solve(int state) {
    if (/* base case */) return baseValue;
    if (memo.count(state)) return memo[state];
    long long best = /* init */;
    // transition: combine solve(smallerState) options
    return memo[state] = best;
}
```

### Bottom-Up: Fibonacci-style (Climbing Stairs)
```cpp
int climbStairs(int n) {
    if (n <= 2) return n;
    int prev2 = 1, prev1 = 2;
    for (int i = 3; i <= n; i++) {
        int cur = prev1 + prev2;
        prev2 = prev1; prev1 = cur;
    }
    return prev1;
}
```

### 0/1 Knapsack
```cpp
int knapsack(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];
            if (wt[i - 1] <= w)
                dp[i][w] = max(dp[i][w], dp[i - 1][w - wt[i - 1]] + val[i - 1]);
        }
    return dp[n][W];
}
```

### Longest Common Subsequence (2D DP)
```cpp
int lcs(string& a, string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (a[i-1] == b[j-1]) ? dp[i-1][j-1] + 1 : max(dp[i-1][j], dp[i][j-1]);
    return dp[n][m];
}
```

### Unbounded Knapsack / Coin Change (Min Coins)
```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int a = 1; a <= amount; a++)
        for (int c : coins)
            if (c <= a && dp[a - c] != INT_MAX)
                dp[a] = min(dp[a], dp[a - c] + 1);
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}
```

## Time & Space Complexity
| Pattern | Typical Time | Typical Space (optimizable) |
|---|---|---|
| 1D DP (Fibonacci/House Robber) | O(n) | O(n) -> O(1) rolling |
| 0/1 Knapsack | O(n * W) | O(n * W) -> O(W) rolling |
| LCS / Edit Distance (2D) | O(n * m) | O(n * m) -> O(min(n,m)) rolling |
| Bitmask DP (TSP-style) | O(2^n * n) | O(2^n * n) |
| Digit DP | O(digits * states) | O(digits * states) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 70 | [ ] Climbing Stairs | Easy | https://leetcode.com/problems/climbing-stairs/ |
| 198 | [ ] House Robber | Medium | https://leetcode.com/problems/house-robber/ |
| 322 | [ ] Coin Change | Medium | https://leetcode.com/problems/coin-change/ |
| 300 | [ ] Longest Increasing Subsequence | Medium | https://leetcode.com/problems/longest-increasing-subsequence/ |
| 1143 | [ ] Longest Common Subsequence | Medium | https://leetcode.com/problems/longest-common-subsequence/ |
| 416 | [ ] Partition Equal Subset Sum | Medium | https://leetcode.com/problems/partition-equal-subset-sum/ |
| 72 | [ ] Edit Distance | Medium | https://leetcode.com/problems/edit-distance/ |
| 139 | [ ] Word Break | Medium | https://leetcode.com/problems/word-break/ |
| 62 | [ ] Unique Paths | Medium | https://leetcode.com/problems/unique-paths/ |
| 64 | [ ] Minimum Path Sum | Medium | https://leetcode.com/problems/minimum-path-sum/ |
| 1035 | [ ] Uncrossed Lines | Medium | https://leetcode.com/problems/uncrossed-lines/ |
| 312 | [ ] Burst Balloons | Hard | https://leetcode.com/problems/burst-balloons/ |
| 10 | [ ] Regular Expression Matching | Hard | https://leetcode.com/problems/regular-expression-matching/ |
| 518 | [ ] Coin Change II | Medium | https://leetcode.com/problems/coin-change-ii/ |
| 152 | [ ] Maximum Product Subarray | Medium | https://leetcode.com/problems/maximum-product-subarray/ |

## Common Pitfalls
- Define the DP state precisely before coding — vague states lead to wrong recurrences.
- Initialize base cases correctly (dp[0], empty-string/empty-array cases) — most bugs live here.
- Watch iteration order for space-optimized DP (in-place 1D array): sometimes must iterate `w` in reverse (0/1 knapsack) vs forward (unbounded knapsack) to avoid reusing an item multiple times incorrectly.
- Memoization needs a hashable state key — use a map or tuple encoding, or a multi-dimensional array when state fits in small bounded ranges.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
