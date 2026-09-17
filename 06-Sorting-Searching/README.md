# Sorting & Searching — C++ DSA Notes

## Overview
Understand each sort's complexity/stability trade-offs, and know C++'s built-in `sort`, `stable_sort`,
`nth_element`, and comparator syntax cold — most interview sorting is "use the right STL call correctly."

## How to Recognize This Pattern
- "Sort with custom rule" -> comparator lambda
- "Kth largest/smallest without full sort" -> `nth_element` or heap
- "Count inversions / merge two sorted lists" -> merge sort mechanics
- "Sort almost-sorted / limited-range values" -> counting sort / bucket sort

## Core Templates (C++)
### Custom Comparator
```cpp
sort(a.begin(), a.end(), [](int x, int y) { return x > y; }); // descending
sort(v.begin(), v.end(), [](auto& p1, auto& p2) {
    if (p1.first != p2.first) return p1.first < p2.first;
    return p1.second > p2.second;
});
```

### nth_element (Kth smallest in O(n) average)
```cpp
nth_element(a.begin(), a.begin() + k - 1, a.end());
int kth_smallest = a[k - 1];
```

### Merge Sort (Count Inversions)
```cpp
long long mergeCount(vector<int>& a, int l, int r) {
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    long long cnt = mergeCount(a, l, m) + mergeCount(a, m, r);
    vector<int> tmp;
    int i = l, j = m;
    while (i < m && j < r) {
        if (a[i] <= a[j]) tmp.push_back(a[i++]);
        else { cnt += m - i; tmp.push_back(a[j++]); }
    }
    while (i < m) tmp.push_back(a[i++]);
    while (j < r) tmp.push_back(a[j++]);
    copy(tmp.begin(), tmp.end(), a.begin() + l);
    return cnt;
}
```

### Counting Sort
```cpp
void countingSort(vector<int>& a, int maxVal) {
    vector<int> cnt(maxVal + 1, 0);
    for (int x : a) cnt[x]++;
    int idx = 0;
    for (int v = 0; v <= maxVal; v++)
        while (cnt[v]--) a[idx++] = v;
}
```

## Time & Space Complexity
| Algorithm | Time (avg) | Time (worst) | Space | Stable |
|---|---|---|---|---|
| `std::sort` (introsort) | O(n log n) | O(n log n) | O(log n) | No |
| `std::stable_sort` | O(n log n) | O(n log n) | O(n) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n^2) | O(log n) | No |
| Counting Sort | O(n + k) | O(n + k) | O(k) | Yes |
| `nth_element` | O(n) | O(n) | O(1) | No |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 912 | [ ] Sort an Array | Medium | https://leetcode.com/problems/sort-an-array/ |
| 215 | [ ] Kth Largest Element in an Array | Medium | https://leetcode.com/problems/kth-largest-element-in-an-array/ |
| 56 | [ ] Merge Intervals | Medium | https://leetcode.com/problems/merge-intervals/ |
| 148 | [ ] Sort List | Medium | https://leetcode.com/problems/sort-list/ |
| 75 | [ ] Sort Colors | Medium | https://leetcode.com/problems/sort-colors/ |
| 493 | [ ] Reverse Pairs | Hard | https://leetcode.com/problems/reverse-pairs/ |
| 179 | [ ] Largest Number | Medium | https://leetcode.com/problems/largest-number/ |
| 347 | [ ] Top K Frequent Elements | Medium | https://leetcode.com/problems/top-k-frequent-elements/ |

## Common Pitfalls
- Comparator must define strict weak ordering — returning true for equal elements causes UB/crashes.
- `sort` on custom structs without operator< needs an explicit comparator.
- Counting/bucket sort only works with bounded/known value ranges.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
