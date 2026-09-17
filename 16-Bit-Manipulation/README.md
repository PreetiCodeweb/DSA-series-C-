# Bit Manipulation — C++ DSA Notes

## Overview
Bit tricks give O(1) or O(log(value)) solutions to problems involving XOR, parity, subsets of bits,
and power-of-two checks. A small toolkit of tricks covers the vast majority of LeetCode bit problems.

## How to Recognize This Pattern
- "Single number appearing once (others appear twice/thrice)" -> XOR tricks
- "Count set bits" -> Brian Kernighan's algorithm
- "Power of two/four check" -> `n & (n-1) == 0`
- "Generate all subsets" -> bitmask enumeration `0..(1<<n)-1`

## Core Templates (C++)
### Useful Bit Tricks
```cpp
n & (n - 1)        // removes the lowest set bit
n & (-n)           // isolates the lowest set bit
n & (n - 1) == 0   // true if n is a power of two (n > 0)
__builtin_popcount(n)   // count set bits (GCC/Clang builtin)
```

### Single Number (XOR trick — every other element appears twice)
```cpp
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int n : nums) res ^= n;
    return res;
}
```

### Single Number II (every other appears thrice) — bit counting
```cpp
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int bit = 0; bit < 32; bit++) {
        int cnt = 0;
        for (int n : nums) cnt += (n >> bit) & 1;
        if (cnt % 3) res |= (1 << bit);
    }
    return res;
}
```

### Counting Bits (DP + bit trick)
```cpp
vector<int> countBits(int n) {
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) dp[i] = dp[i >> 1] + (i & 1);
    return dp;
}
```

### Iterate All Subsets of a Bitmask (submask enumeration)
```cpp
for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
    // process subset `sub`
}
```

## Time & Space Complexity
| Operation | Time | Space |
|---|---|---|
| XOR / AND / OR / shift | O(1) | O(1) |
| `__builtin_popcount` | O(1) (hardware) | O(1) |
| Subset generation via bitmask (n bits) | O(2^n) | O(1) per subset |
| Submask enumeration of a mask with k bits | O(3^k) total across all masks (amortized) | O(1) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 136 | [ ] Single Number | Easy | https://leetcode.com/problems/single-number/ |
| 137 | [ ] Single Number II | Medium | https://leetcode.com/problems/single-number-ii/ |
| 191 | [ ] Number of 1 Bits | Easy | https://leetcode.com/problems/number-of-1-bits/ |
| 231 | [ ] Power of Two | Easy | https://leetcode.com/problems/power-of-two/ |
| 338 | [ ] Counting Bits | Easy | https://leetcode.com/problems/counting-bits/ |
| 78 | [ ] Subsets | Medium | https://leetcode.com/problems/subsets/ |
| 371 | [ ] Sum of Two Integers | Medium | https://leetcode.com/problems/sum-of-two-integers/ |
| 190 | [ ] Reverse Bits | Easy | https://leetcode.com/problems/reverse-bits/ |
| 260 | [ ] Single Number III | Medium | https://leetcode.com/problems/single-number-iii/ |
| 1318 | [ ] Minimum Flips to Make a OR b Equal to c | Medium | https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/ |

## Common Pitfalls
- Right-shifting negative numbers in C++ is implementation-defined/arithmetic shift — be careful with signed ints; prefer `unsigned` for bit tricks when sign shouldn't matter.
- `1 << 31` overflows a signed 32-bit int — use `1LL << 31` or `unsigned` for large shifts.
- XOR-based "single number" tricks only work when non-unique elements appear an even number of times; verify problem constraints match.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
