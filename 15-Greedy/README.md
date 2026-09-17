# Greedy Algorithms — C++ DSA Notes

## Overview
Greedy picks the locally optimal choice at each step, hoping it leads to a global optimum.
Works only when the problem has the "greedy choice property" + optimal substructure — always sanity-check
with a small counterexample before trusting a greedy idea; if it fails, the problem likely needs DP instead.

## How to Recognize This Pattern
- "Interval scheduling / non-overlapping intervals" -> sort by end time, greedy pick
- "Minimum number of X to cover Y" -> sort + greedy
- "Assign resources to maximize/minimize" -> sort + two-pointer greedy
- Activity selection, jump game, gas station -> classic greedy templates

## Core Templates (C++)
### Interval Scheduling (Max Non-Overlapping)
```cpp
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) { return a[1] < b[1]; });
    int count = 0, end = INT_MIN;
    for (auto& iv : intervals) {
        if (iv[0] >= end) end = iv[1];
        else count++; // must remove this interval
    }
    return count;
}
```

### Jump Game (Greedy Reachability)
```cpp
bool canJump(vector<int>& nums) {
    int reach = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (i > reach) return false;
        reach = max(reach, i + nums[i]);
    }
    return true;
}
```

### Gas Station
```cpp
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int total = 0, tank = 0, start = 0;
    for (int i = 0; i < gas.size(); i++) {
        int diff = gas[i] - cost[i];
        total += diff; tank += diff;
        if (tank < 0) { start = i + 1; tank = 0; }
    }
    return total >= 0 ? start : -1;
}
```

### Merge Intervals (Sort + Sweep)
```cpp
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> res;
    for (auto& iv : intervals) {
        if (!res.empty() && iv[0] <= res.back()[1])
            res.back()[1] = max(res.back()[1], iv[1]);
        else res.push_back(iv);
    }
    return res;
}
```

## Time & Space Complexity
| Pattern | Time | Space |
|---|---|---|
| Sort + linear scan | O(n log n) | O(1)-O(n) |
| Jump Game (single pass) | O(n) | O(1) |
| Gas Station (single pass) | O(n) | O(1) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 455 | [ ] Assign Cookies | Easy | https://leetcode.com/problems/assign-cookies/ |
| 435 | [ ] Non-overlapping Intervals | Medium | https://leetcode.com/problems/non-overlapping-intervals/ |
| 55 | [ ] Jump Game | Medium | https://leetcode.com/problems/jump-game/ |
| 45 | [ ] Jump Game II | Medium | https://leetcode.com/problems/jump-game-ii/ |
| 134 | [ ] Gas Station | Medium | https://leetcode.com/problems/gas-station/ |
| 56 | [ ] Merge Intervals | Medium | https://leetcode.com/problems/merge-intervals/ |
| 621 | [ ] Task Scheduler | Medium | https://leetcode.com/problems/task-scheduler/ |
| 763 | [ ] Partition Labels | Medium | https://leetcode.com/problems/partition-labels/ |
| 860 | [ ] Lemonade Change | Easy | https://leetcode.com/problems/lemonade-change/ |
| 406 | [ ] Queue Reconstruction by Height | Medium | https://leetcode.com/problems/queue-reconstruction-by-height/ |

## Common Pitfalls
- Greedy is easy to get wrong silently — always try to construct a counterexample before committing.
- Choice of sort key (by start vs end vs some ratio) determines correctness — think through why that key works.
- If greedy seems to fail on edge cases, the problem is probably DP, not greedy.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
