# Arrays — C++ DSA Notes

## Overview
Arrays are contiguous memory blocks — the foundation for almost every other data structure.
Most array problems reduce to: prefix sums, two pointers, sliding window, sorting, or in-place manipulation.
In C++, prefer `vector<int>` over raw arrays for safety and STL support.

## How to Recognize This Pattern
- "Find pair/triplet with sum X" -> two pointers / hashing
- "Subarray with property X" -> prefix sum / sliding window
- "Rearrange in-place" -> two pointers, swap tricks
- "Kth largest/smallest" -> sorting / heap / quickselect

## Core Templates (C++)
### Prefix Sum
```cpp
vector<int> prefix(n + 1, 0);
for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + a[i];
// sum(l, r inclusive) = prefix[r+1] - prefix[l]
```

### Kadane's Algorithm (Max Subarray Sum)
```cpp
int maxSubArray(vector<int>& a) {
    int best = a[0], cur = a[0];
    for (int i = 1; i < a.size(); i++) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}
```

### In-place Reversal
```cpp
void reverse(vector<int>& a, int l, int r) {
    while (l < r) swap(a[l++], a[r--]);
}
```

### Dutch National Flag (3-way partition)
```cpp
void sortColors(vector<int>& a) {
    int lo = 0, mid = 0, hi = a.size() - 1;
    while (mid <= hi) {
        if (a[mid] == 0) swap(a[lo++], a[mid++]);
        else if (a[mid] == 1) mid++;
        else swap(a[mid], a[hi--]);
    }
}
```

## Time & Space Complexity
| Operation | Time | Space |
|---|---|---|
| Access | O(1) | - |
| Search (unsorted) | O(n) | O(1) |
| Search (sorted, binary) | O(log n) | O(1) |
| Insert/Delete at end | O(1) amortized | O(1) |
| Insert/Delete at arbitrary index | O(n) | O(1) |
| Prefix sum build | O(n) | O(n) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 1 | [ ] Two Sum | Easy | https://leetcode.com/problems/two-sum/ |
| 53 | [ ] Maximum Subarray | Medium | https://leetcode.com/problems/maximum-subarray/ |
| 283 | [ ] Move Zeroes | Easy | https://leetcode.com/problems/move-zeroes/ |
| 238 | [ ] Product of Array Except Self | Medium | https://leetcode.com/problems/product-of-array-except-self/ |
| 152 | [ ] Maximum Product Subarray | Medium | https://leetcode.com/problems/maximum-product-subarray/ |
| 48 | [ ] Rotate Image | Medium | https://leetcode.com/problems/rotate-image/ |
| 56 | [ ] Merge Intervals | Medium | https://leetcode.com/problems/merge-intervals/ |
| 41 | [ ] First Missing Positive | Hard | https://leetcode.com/problems/first-missing-positive/ |
| 128 | [ ] Longest Consecutive Sequence | Medium | https://leetcode.com/problems/longest-consecutive-sequence/ |
| 169 | [ ] Majority Element | Easy | https://leetcode.com/problems/majority-element/ |
| 31 | [ ] Next Permutation | Medium | https://leetcode.com/problems/next-permutation/ |
| 287 | [ ] Find the Duplicate Number | Medium | https://leetcode.com/problems/find-the-duplicate-number/ |

## Common Pitfalls
- Off-by-one errors in prefix sums and sliding windows — always test with n=0,1.
- Modifying array while iterating with index — be careful with erase/insert on vector (O(n) each).
- Integer overflow on sums — use `long long` for accumulations.
- `vector::size()` returns `size_t` (unsigned) — mixing with negative ints causes bugs; cast to `int`.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
