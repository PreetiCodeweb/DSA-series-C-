# Strings — C++ DSA Notes

## Overview
String problems in C++ revolve around `std::string`, character frequency maps, and pattern matching.
Key skill: recognizing when a problem is really a hashing, two-pointer, sliding-window, or DP problem in disguise.

## How to Recognize This Pattern
- "Anagram / permutation check" -> frequency array (size 26) or hashmap
- "Palindrome" -> two pointers / expand-around-center / DP
- "Substring search" -> KMP / Rabin-Karp / sliding window
- "Longest X substring" -> sliding window with hashmap

## Core Templates (C++)
### Frequency Count (lowercase only)
```cpp
array<int,26> freq{};
for (char c : s) freq[c - 'a']++;
```

### Expand Around Center (Palindromes)
```cpp
pair<int,int> expand(const string& s, int l, int r) {
    while (l >= 0 && r < s.size() && s[l] == s[r]) { l--; r++; }
    return {l + 1, r - 1};
}
```

### KMP Prefix Function
```cpp
vector<int> buildLPS(const string& p) {
    int n = p.size();
    vector<int> lps(n, 0);
    for (int i = 1, len = 0; i < n; ) {
        if (p[i] == p[len]) lps[i++] = ++len;
        else if (len) len = lps[len - 1];
        else lps[i++] = 0;
    }
    return lps;
}
```

### Sliding Window Template
```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char,int> last;
    int best = 0, start = 0;
    for (int i = 0; i < s.size(); i++) {
        if (last.count(s[i]) && last[s[i]] >= start)
            start = last[s[i]] + 1;
        last[s[i]] = i;
        best = max(best, i - start + 1);
    }
    return best;
}
```

## Time & Space Complexity
| Operation | Time | Space |
|---|---|---|
| Traversal | O(n) | O(1) |
| Concatenation (`+=`) in loop | O(n) amortized per op, O(n^2) worst if reallocated poorly | - |
| Substring `s.substr()` | O(k) | O(k) |
| KMP search | O(n + m) | O(m) |
| Rabin-Karp | O(n + m) avg | O(1) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 3 | [ ] Longest Substring Without Repeating Characters | Medium | https://leetcode.com/problems/longest-substring-without-repeating-characters/ |
| 5 | [ ] Longest Palindromic Substring | Medium | https://leetcode.com/problems/longest-palindromic-substring/ |
| 49 | [ ] Group Anagrams | Medium | https://leetcode.com/problems/group-anagrams/ |
| 242 | [ ] Valid Anagram | Easy | https://leetcode.com/problems/valid-anagram/ |
| 28 | [ ] Find the Index of the First Occurrence in a String | Easy | https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/ |
| 76 | [ ] Minimum Window Substring | Hard | https://leetcode.com/problems/minimum-window-substring/ |
| 271 | [ ] Encode and Decode Strings | Medium | https://leetcode.com/problems/encode-and-decode-strings/ |
| 14 | [ ] Longest Common Prefix | Easy | https://leetcode.com/problems/longest-common-prefix/ |
| 443 | [ ] String Compression | Medium | https://leetcode.com/problems/string-compression/ |
| 6 | [ ] Zigzag Conversion | Medium | https://leetcode.com/problems/zigzag-conversion/ |

## Common Pitfalls
- `string` is mutable in C++ (unlike Java/Python) — in-place edits are cheap.
- Comparing strings with `==` compares content, not pointers (safe, unlike C).
- Watch for Unicode/multi-byte assumptions — LeetCode strings are usually ASCII lowercase, verify constraints.
- `substr(pos, len)` copies — expensive in tight loops; use indices/string_view where possible.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
