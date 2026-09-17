# Stack & Queue — C++ DSA Notes

## Overview
Stacks (LIFO) and Queues (FIFO) model "most recent first" vs "first in, first out" processing.
Monotonic stacks/queues are a critical advanced pattern for "next greater/smaller element" problems.

## How to Recognize This Pattern
- "Matching brackets / valid parentheses" -> stack
- "Next greater/smaller element" -> monotonic stack
- "Evaluate expression (RPN, infix)" -> stack
- "BFS / level order traversal" -> queue
- "Sliding window max" -> monotonic deque

## Core Templates (C++)
### Valid Parentheses
```cpp
bool isValid(string s) {
    stack<char> st;
    unordered_map<char,char> pairs = {{')','('},{']','['},{'}','{'}};
    for (char c : s) {
        if (pairs.count(c)) {
            if (st.empty() || st.top() != pairs[c]) return false;
            st.pop();
        } else st.push(c);
    }
    return st.empty();
}
```

### Monotonic Stack (Next Greater Element)
```cpp
vector<int> nextGreater(vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1);
    stack<int> st; // indices, decreasing values
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            res[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }
    return res;
}
```

### Queue via Two Stacks
```cpp
class MyQueue {
    stack<int> in, out;
public:
    void push(int x) { in.push(x); }
    int pop() {
        if (out.empty()) while (!in.empty()) { out.push(in.top()); in.pop(); }
        int v = out.top(); out.pop(); return v;
    }
};
```

### Min Stack
```cpp
class MinStack {
    stack<pair<int,int>> st; // {value, min-so-far}
public:
    void push(int x) {
        int m = st.empty() ? x : min(x, st.top().second);
        st.push({x, m});
    }
    void pop() { st.pop(); }
    int top() { return st.top().first; }
    int getMin() { return st.top().second; }
};
```

## Time & Space Complexity
| Operation | Time | Space |
|---|---|---|
| Push/Pop/Top (stack or queue) | O(1) | O(1) |
| Monotonic stack over n elements | O(n) amortized | O(n) |
| BFS with queue | O(V + E) | O(V) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 20 | [ ] Valid Parentheses | Easy | https://leetcode.com/problems/valid-parentheses/ |
| 155 | [ ] Min Stack | Medium | https://leetcode.com/problems/min-stack/ |
| 739 | [ ] Daily Temperatures | Medium | https://leetcode.com/problems/daily-temperatures/ |
| 84 | [ ] Largest Rectangle in Histogram | Hard | https://leetcode.com/problems/largest-rectangle-in-histogram/ |
| 150 | [ ] Evaluate Reverse Polish Notation | Medium | https://leetcode.com/problems/evaluate-reverse-polish-notation/ |
| 232 | [ ] Implement Queue using Stacks | Easy | https://leetcode.com/problems/implement-queue-using-stacks/ |
| 394 | [ ] Decode String | Medium | https://leetcode.com/problems/decode-string/ |
| 496 | [ ] Next Greater Element I | Easy | https://leetcode.com/problems/next-greater-element-i/ |
| 901 | [ ] Online Stock Span | Medium | https://leetcode.com/problems/online-stock-span/ |
| 42 | [ ] Trapping Rain Water | Hard | https://leetcode.com/problems/trapping-rain-water/ |

## Common Pitfalls
- Always check `!st.empty()` before `top()`/`pop()` — UB otherwise.
- For monotonic stack, decide direction (increasing vs decreasing) based on whether you want next-greater or next-smaller.
- Two-stack queue amortized O(1) only holds if you don't repeatedly interleave push/pop worst-case adversarially per op — still true amortized, but understand why.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
