# Binary Search — C++ DSA Notes

## Overview
Binary search isn't just "find X in sorted array" — it's a general technique for searching any
monotonic (boolean) predicate space in O(log n). Think "search on answer" for optimization problems.

## How to Recognize This Pattern
- Sorted array lookup -> classic binary search
- "Find boundary / first true / last true of a monotonic predicate" -> binary search on predicate
- "Minimize the maximum" / "Maximize the minimum" -> binary search on the answer
- Rotated sorted array -> modified binary search

## Core Templates (C++)
### Classic Binary Search
```cpp
int search(vector<int>& a, int target) {
    int lo = 0, hi = a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        else if (a[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
```

### Lower/Upper Bound (find first True in predicate)
```cpp
int firstTrue(int lo, int hi, function<bool(int)> pred) {
    // predicate is false...false,true...true ; find first true
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (pred(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
```

### Binary Search on Answer (e.g., Koko Eating Bananas)
```cpp
int minEatingSpeed(vector<int>& piles, int h) {
    int lo = 1, hi = *max_element(piles.begin(), piles.end());
    auto canFinish = [&](int speed) {
        long long hours = 0;
        for (int p : piles) hours += (p + speed - 1) / speed;
        return hours <= h;
    };
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canFinish(mid)) hi = mid; else lo = mid + 1;
    }
    return lo;
}
```

### Rotated Array Search
```cpp
int searchRotated(vector<int>& a, int target) {
    int lo = 0, hi = a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[lo] <= a[mid]) {              // left half sorted
            if (a[lo] <= target && target < a[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {                            // right half sorted
            if (a[mid] < target && target <= a[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}
```

## Time & Space Complexity
| Operation | Time | Space |
|---|---|---|
| Search in sorted array | O(log n) | O(1) |
| Binary search on answer | O(log(range) * check_cost) | O(1) |
| `std::lower_bound`/`upper_bound` | O(log n) | O(1) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 704 | [ ] Binary Search | Easy | https://leetcode.com/problems/binary-search/ |
| 33 | [ ] Search in Rotated Sorted Array | Medium | https://leetcode.com/problems/search-in-rotated-sorted-array/ |
| 153 | [ ] Find Minimum in Rotated Sorted Array | Medium | https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/ |
| 34 | [ ] Find First and Last Position of Element in Sorted Array | Medium | https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/ |
| 875 | [ ] Koko Eating Bananas | Medium | https://leetcode.com/problems/koko-eating-bananas/ |
| 410 | [ ] Split Array Largest Sum | Hard | https://leetcode.com/problems/split-array-largest-sum/ |
| 4 | [ ] Median of Two Sorted Arrays | Hard | https://leetcode.com/problems/median-of-two-sorted-arrays/ |
| 74 | [ ] Search a 2D Matrix | Medium | https://leetcode.com/problems/search-a-2d-matrix/ |
| 162 | [ ] Find Peak Element | Medium | https://leetcode.com/problems/find-peak-element/ |
| 1011 | [ ] Capacity To Ship Packages Within D Days | Medium | https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/ |

## Common Pitfalls
- `mid = lo + (hi - lo) / 2` avoids overflow vs `(lo + hi) / 2`.
- Decide the loop invariant clearly: `lo <= hi` with return -1 vs `lo < hi` converging to a boundary — mixing them causes infinite loops.
- For "search on answer", verify the predicate is truly monotonic before applying binary search.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
