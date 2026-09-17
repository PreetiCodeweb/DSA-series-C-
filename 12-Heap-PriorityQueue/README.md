# Heap / Priority Queue — C++ DSA Notes

## Overview
Heaps give O(log n) insert and O(1) access to the min/max element — ideal for "top K", "Kth largest",
"merge k sorted", and scheduling problems. C++'s `priority_queue` is a max-heap by default.

## How to Recognize This Pattern
- "Kth largest/smallest", "top K frequent" -> heap of size K
- "Merge K sorted lists/arrays" -> min-heap of current heads
- "Median of a stream" -> two heaps (max-heap for lower half, min-heap for upper half)
- "Task scheduling by priority" -> priority_queue directly

## Core Templates (C++)
### Min-Heap / Max-Heap Declaration
```cpp
priority_queue<int> maxHeap;                                   // max-heap (default)
priority_queue<int, vector<int>, greater<int>> minHeap;         // min-heap
```

### Top K Frequent Elements
```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> freq;
    for (int n : nums) freq[n]++;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap; // {freq, val}
    for (auto& [val, f] : freq) {
        minHeap.push({f, val});
        if (minHeap.size() > k) minHeap.pop();
    }
    vector<int> res;
    while (!minHeap.empty()) { res.push_back(minHeap.top().second); minHeap.pop(); }
    return res;
}
```

### Merge K Sorted Lists (Min-Heap)
```cpp
ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
    for (auto l : lists) if (l) pq.push(l);
    ListNode dummy(0); ListNode* tail = &dummy;
    while (!pq.empty()) {
        ListNode* n = pq.top(); pq.pop();
        tail->next = n; tail = n;
        if (n->next) pq.push(n->next);
    }
    return dummy.next;
}
```

### Median of a Data Stream (Two Heaps)
```cpp
class MedianFinder {
    priority_queue<int> lo;                              // max-heap, lower half
    priority_queue<int, vector<int>, greater<int>> hi;   // min-heap, upper half
public:
    void addNum(int num) {
        lo.push(num);
        hi.push(lo.top()); lo.pop();
        if (hi.size() > lo.size()) { lo.push(hi.top()); hi.pop(); }
    }
    double findMedian() {
        if (lo.size() > hi.size()) return lo.top();
        return (lo.top() + hi.top()) / 2.0;
    }
};
```

## Time & Space Complexity
| Operation | Time | Space |
|---|---|---|
| Push/Pop | O(log n) | O(1) |
| Peek top | O(1) | - |
| Build heap from n elements | O(n) | O(n) |
| Top-K via size-K heap | O(n log k) | O(k) |
| K-way merge (N total elements) | O(N log k) | O(k) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 215 | [ ] Kth Largest Element in an Array | Medium | https://leetcode.com/problems/kth-largest-element-in-an-array/ |
| 347 | [ ] Top K Frequent Elements | Medium | https://leetcode.com/problems/top-k-frequent-elements/ |
| 23 | [ ] Merge k Sorted Lists | Hard | https://leetcode.com/problems/merge-k-sorted-lists/ |
| 295 | [ ] Find Median from Data Stream | Hard | https://leetcode.com/problems/find-median-from-data-stream/ |
| 373 | [ ] Find K Pairs with Smallest Sums | Medium | https://leetcode.com/problems/find-k-pairs-with-smallest-sums/ |
| 692 | [ ] Top K Frequent Words | Medium | https://leetcode.com/problems/top-k-frequent-words/ |
| 1046 | [ ] Last Stone Weight | Easy | https://leetcode.com/problems/last-stone-weight/ |
| 767 | [ ] Reorganize String | Medium | https://leetcode.com/problems/reorganize-string/ |
| 703 | [ ] Kth Largest Element in a Stream | Easy | https://leetcode.com/problems/kth-largest-element-in-a-stream/ |

## Common Pitfalls
- `priority_queue` is max-heap by default — remember `greater<int>` for min-heap.
- Custom comparator lambdas need `decltype(cmp)` and passing `cmp` to the constructor.
- For "Kth largest", a size-K min-heap (keep smallest K popped) is more efficient than a full max-heap.
- Heap doesn't support O(log n) arbitrary deletion/decrease-key natively — needs lazy deletion or indexed heap for Dijkstra-style updates.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
