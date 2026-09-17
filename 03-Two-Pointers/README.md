# Two Pointers — C++ DSA Notes

## Overview
Two pointers reduce O(n^2) brute force to O(n) by moving indices inward, outward, or in tandem
based on a monotonic condition. Requires the array to be sorted or the condition to be monotonic.

## How to Recognize This Pattern
- Sorted array + "find pair/triplet with sum" -> opposite-direction pointers
- "Remove duplicates in-place" -> slow/fast pointers
- "Merge two sorted structures" -> parallel pointers
- Linked list "cycle detection / middle node" -> fast & slow pointers

## Core Templates (C++)
### Opposite Direction (Sorted Array Pair Sum)
```cpp
bool pairSum(vector<int>& a, int target) {
    int l = 0, r = a.size() - 1;
    while (l < r) {
        int s = a[l] + a[r];
        if (s == target) return true;
        else if (s < target) l++;
        else r--;
    }
    return false;
}
```

### Slow/Fast (Remove Duplicates)
```cpp
int removeDuplicates(vector<int>& a) {
    int slow = 0;
    for (int fast = 1; fast < a.size(); fast++)
        if (a[fast] != a[slow]) a[++slow] = a[fast];
    return slow + 1;
}
```

### Fast/Slow (Linked List Cycle)
```cpp
bool hasCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

## Time & Space Complexity
| Pattern | Time | Space |
|---|---|---|
| Opposite pointers on sorted array | O(n) | O(1) |
| Slow/fast in-place dedup | O(n) | O(1) |
| Fast/slow cycle detection | O(n) | O(1) |
| 3Sum (sort + 2 pointers) | O(n^2) | O(1) extra |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 167 | [ ] Two Sum II - Input Array Is Sorted | Medium | https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/ |
| 15 | [ ] 3Sum | Medium | https://leetcode.com/problems/3sum/ |
| 11 | [ ] Container With Most Water | Medium | https://leetcode.com/problems/container-with-most-water/ |
| 26 | [ ] Remove Duplicates from Sorted Array | Easy | https://leetcode.com/problems/remove-duplicates-from-sorted-array/ |
| 75 | [ ] Sort Colors | Medium | https://leetcode.com/problems/sort-colors/ |
| 42 | [ ] Trapping Rain Water | Hard | https://leetcode.com/problems/trapping-rain-water/ |
| 141 | [ ] Linked List Cycle | Easy | https://leetcode.com/problems/linked-list-cycle/ |
| 876 | [ ] Middle of the Linked List | Easy | https://leetcode.com/problems/middle-of-the-linked-list/ |
| 18 | [ ] 4Sum | Medium | https://leetcode.com/problems/4sum/ |
| 977 | [ ] Squares of a Sorted Array | Easy | https://leetcode.com/problems/squares-of-a-sorted-array/ |

## Common Pitfalls
- Two pointers requires a monotonic/sorted structure — check constraints before assuming applicability.
- Skip duplicate values carefully in 3Sum/4Sum to avoid duplicate triplets.
- Off-by-one when pointers cross (`l < r` vs `l <= r`) — decide based on whether l==r is a valid state.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
