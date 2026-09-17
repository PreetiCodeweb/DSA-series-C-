# Sliding Window — C++ DSA Notes

## Overview
A specialized two-pointer technique for contiguous subarray/substring problems where the window
grows and shrinks based on a condition. Two flavors: fixed-size window, and variable-size window.

## How to Recognize This Pattern
- "Longest/shortest subarray/substring satisfying condition X" -> variable window
- "Max/min of every window of size k" -> fixed window + deque
- Keywords: "contiguous", "subarray", "substring", "at most K distinct"::

## Core Templates (C++)
### Variable-Size Window
```cpp
int minSubArrayLen(int target, vector<int>& a) {
    int n = a.size(), l = 0, sum = 0, best = INT_MAX;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum >= target) {
            best = min(best, r - l + 1);
            sum -= a[l++];
        }
    }
    return best == INT_MAX ? 0 : best;
}
```

### Fixed-Size Window Max (Monotonic Deque)
```cpp
vector<int> maxSlidingWindow(vector<int>& a, int k) {
    deque<int> dq; // stores indices, decreasing values
    vector<int> res;
    for (int i = 0; i < a.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && a[dq.back()] < a[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}
```

### At-Most-K-Distinct Window
```cpp
int atMostKDistinct(string s, int k) {
    unordered_map<char,int> cnt;
    int l = 0, best = 0;
    for (int r = 0; r < s.size(); r++) {
        cnt[s[r]]++;
        while (cnt.size() > k) {
            if (--cnt[s[l]] == 0) cnt.erase(s[l]);
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}
```

## Time & Space Complexity
| Pattern | Time | Space |
|---|---|---|
| Variable window | O(n) | O(1)-O(k) |
| Fixed window + deque | O(n) | O(k) |
| At-most-K distinct | O(n) | O(k) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 3 | [ ] Longest Substring Without Repeating Characters | Medium | https://leetcode.com/problems/longest-substring-without-repeating-characters/ |
| 209 | [ ] Minimum Size Subarray Sum | Medium | https://leetcode.com/problems/minimum-size-subarray-sum/ |
| 239 | [ ] Sliding Window Maximum | Hard | https://leetcode.com/problems/sliding-window-maximum/ |
| 76 | [ ] Minimum Window Substring | Hard | https://leetcode.com/problems/minimum-window-substring/ |
| 438 | [ ] Find All Anagrams in a String | Medium | https://leetcode.com/problems/find-all-anagrams-in-a-string/ |
| 567 | [ ] Permutation in String | Medium | https://leetcode.com/problems/permutation-in-string/ |
| 1004 | [ ] Max Consecutive Ones III | Medium | https://leetcode.com/problems/max-consecutive-ones-iii/ |
| 424 | [ ] Longest Repeating Character Replacement | Medium | https://leetcode.com/problems/longest-repeating-character-replacement/ |
| 713 | [ ] Subarray Product Less Than K | Medium | https://leetcode.com/problems/subarray-product-less-than-k/ |

## Common Pitfalls
- Decide up front: does the window shrink one step at a time or reset entirely? Most correct solutions shrink one step at a time.
- Ensure the "while" shrink condition can't infinite-loop (l must strictly advance).
- For "exactly K" problems, use atMost(K) - atMost(K-1) trick instead of writing exact-K logic directly.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
