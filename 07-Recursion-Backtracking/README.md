# Recursion & Backtracking — C++ DSA Notes

## Overview
Recursion solves a problem by solving smaller identical subproblems. Backtracking is recursion +
explicit "undo" of a choice, used to explore all combinatorial possibilities (subsets, permutations, paths).

## How to Recognize This Pattern
- "Generate all subsets/permutations/combinations" -> backtracking
- "N-Queens / Sudoku / word search on grid" -> backtracking with pruning
- Tree/graph problems phrased recursively -> DFS recursion
- Divide and conquer (merge sort, quickselect) -> recursion with combine step

## Core Templates (C++)
### Backtracking Skeleton
```cpp
void backtrack(vector<int>& path, vector<int>& choices, vector<vector<int>>& result) {
    if (/* base case */) {
        result.push_back(path);
        return;
    }
    for (int i = 0; i < choices.size(); i++) {
        // prune invalid choices here
        path.push_back(choices[i]);
        backtrack(path, choices, result); // or recurse on i+1.. to avoid reuse
        path.pop_back(); // undo
    }
}
```

### Subsets
```cpp
void subsets(vector<int>& nums, int idx, vector<int>& cur, vector<vector<int>>& res) {
    res.push_back(cur);
    for (int i = idx; i < nums.size(); i++) {
        cur.push_back(nums[i]);
        subsets(nums, i + 1, cur, res);
        cur.pop_back();
    }
}
```

### Permutations (using a `used[]` array)
```cpp
void permute(vector<int>& nums, vector<bool>& used, vector<int>& cur, vector<vector<int>>& res) {
    if (cur.size() == nums.size()) { res.push_back(cur); return; }
    for (int i = 0; i < nums.size(); i++) {
        if (used[i]) continue;
        used[i] = true;
        cur.push_back(nums[i]);
        permute(nums, used, cur, res);
        cur.pop_back();
        used[i] = false;
    }
}
```

### N-Queens Pruning Pattern
```cpp
bool isSafe(vector<int>& queens, int row, int col) {
    for (int r = 0; r < row; r++) {
        int c = queens[r];
        if (c == col || abs(c - col) == abs(r - row)) return false;
    }
    return true;
}
```

## Time & Space Complexity
| Problem | Time | Space |
|---|---|---|
| Subsets (n elements) | O(2^n) | O(n) recursion + O(2^n) output |
| Permutations (n elements) | O(n!) | O(n) recursion |
| N-Queens | O(n!) worst, pruned in practice | O(n) |
| Combination Sum | O(2^n) worst | O(target/min) depth |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 78 | [ ] Subsets | Medium | https://leetcode.com/problems/subsets/ |
| 46 | [ ] Permutations | Medium | https://leetcode.com/problems/permutations/ |
| 39 | [ ] Combination Sum | Medium | https://leetcode.com/problems/combination-sum/ |
| 22 | [ ] Generate Parentheses | Medium | https://leetcode.com/problems/generate-parentheses/ |
| 51 | [ ] N-Queens | Hard | https://leetcode.com/problems/n-queens/ |
| 79 | [ ] Word Search | Medium | https://leetcode.com/problems/word-search/ |
| 17 | [ ] Letter Combinations of a Phone Number | Medium | https://leetcode.com/problems/letter-combinations-of-a-phone-number/ |
| 37 | [ ] Sudoku Solver | Hard | https://leetcode.com/problems/sudoku-solver/ |
| 131 | [ ] Palindrome Partitioning | Medium | https://leetcode.com/problems/palindrome-partitioning/ |
| 77 | [ ] Combinations | Medium | https://leetcode.com/problems/combinations/ |

## Common Pitfalls
- Forgetting to "undo" the choice (`pop_back`) after recursing leaves shared state corrupted.
- Passing containers by reference (not by value) to avoid O(n) copies at every call — but then must remember to backtrack.
- No pruning = exponential blowup even when the constraints expect it; always prune early (bounds check before recursing).
- Watch recursion depth vs stack size for large n (>~10^4 depth risks stack overflow).

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
