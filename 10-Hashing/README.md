# Hashing (HashMap / HashSet) — C++ DSA Notes

## Overview
Hashing trades space for O(1) average lookup/insert. In C++: `unordered_map`, `unordered_set`,
`map`/`set` (ordered, O(log n)). Recognizing "have I seen this before" or "count frequency" problems is key.

## How to Recognize This Pattern
- "Find pair/complement" -> hashmap of value -> index
- "Count frequency / find duplicates" -> hashmap or hashset
- "Group by some key" -> hashmap of key -> list
- "Check existence in O(1)" -> hashset

## Core Templates (C++)
### Two Sum via Hashmap
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int,int> seen; // value -> index
    for (int i = 0; i < nums.size(); i++) {
        int need = target - nums[i];
        if (seen.count(need)) return {seen[need], i};
        seen[nums[i]] = i;
    }
    return {};
}
```

### Group Anagrams (key = sorted string)
```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (string s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    vector<vector<string>> res;
    for (auto& [k, v] : groups) res.push_back(v);
    return res;
}
```

### Custom Hash for pair<int,int> (unordered_map key)
```cpp
struct pair_hash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<long long>()(((long long)p.first << 32) ^ (unsigned int)p.second);
    }
};
unordered_map<pair<int,int>, int, pair_hash> mp;
```

## Time & Space Complexity
| Operation | Avg | Worst |
|---|---|---|
| `unordered_map`/`set` insert/find/erase | O(1) | O(n) (hash collisions) |
| `map`/`set` (RB-tree) insert/find/erase | O(log n) | O(log n) |
| Iterating all elements | O(n) | O(n) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 1 | [ ] Two Sum | Easy | https://leetcode.com/problems/two-sum/ |
| 49 | [ ] Group Anagrams | Medium | https://leetcode.com/problems/group-anagrams/ |
| 128 | [ ] Longest Consecutive Sequence | Medium | https://leetcode.com/problems/longest-consecutive-sequence/ |
| 560 | [ ] Subarray Sum Equals K | Medium | https://leetcode.com/problems/subarray-sum-equals-k/ |
| 383 | [ ] Ransom Note | Easy | https://leetcode.com/problems/ransom-note/ |
| 349 | [ ] Intersection of Two Arrays | Easy | https://leetcode.com/problems/intersection-of-two-arrays/ |
| 36 | [ ] Valid Sudoku | Medium | https://leetcode.com/problems/valid-sudoku/ |
| 205 | [ ] Isomorphic Strings | Easy | https://leetcode.com/problems/isomorphic-strings/ |
| 30 | [ ] Substring with Concatenation of All Words | Hard | https://leetcode.com/problems/substring-with-concatenation-of-all-words/ |

## Common Pitfalls
- `unordered_map` has worst-case O(n) due to hash collisions (rare, but LeetCode adversarial tests can trigger it) — prefer `map` if worried, or reserve buckets.
- No built-in hash for `pair`/`vector`/custom structs — must supply your own hash functor.
- Modifying a map/set while iterating it (other than via iterator-safe erase) invalidates iterators.
- `mp[key]` on a `const` map or when key absent inserts a default value — use `.find()`/`.count()` for read-only checks.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
