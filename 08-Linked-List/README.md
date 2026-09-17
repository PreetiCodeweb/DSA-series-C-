# Linked List — C++ DSA Notes

## Overview
Linked lists test pointer manipulation discipline. Master dummy nodes, fast/slow pointers, and
in-place reversal — nearly every linked-list problem is a variant of these three tricks.

## How to Recognize This Pattern
- "Reverse / reorder a list" -> iterative pointer reversal
- "Detect cycle / find middle" -> fast & slow pointers
- "Merge k sorted lists" -> heap or divide & conquer
- "Remove Nth node / dedupe" -> dummy head + two pointers

## Core Templates (C++)
### Node Definition
```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

### Reverse a Linked List (Iterative)
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        ListNode* nxt = head->next;
        head->next = prev;
        prev = head;
        head = nxt;
    }
    return prev;
}
```

### Dummy Node Pattern (Remove Nth From End)
```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0); dummy.next = head;
    ListNode *fast = &dummy, *slow = &dummy;
    for (int i = 0; i < n; i++) fast = fast->next;
    while (fast->next) { fast = fast->next; slow = slow->next; }
    ListNode* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;
    return dummy.next;
}
```

### Merge Two Sorted Lists
```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0); ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }
        else { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}
```

### Find Middle (Fast/Slow)
```cpp
ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    return slow;
}
```

## Time & Space Complexity
| Operation | Time | Space |
|---|---|---|
| Traversal | O(n) | O(1) |
| Reverse | O(n) | O(1) |
| Merge two sorted lists (size m, n) | O(m + n) | O(1) |
| Merge k sorted lists (heap) | O(N log k) | O(k) |
| Cycle detection (Floyd's) | O(n) | O(1) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 206 | [ ] Reverse Linked List | Easy | https://leetcode.com/problems/reverse-linked-list/ |
| 21 | [ ] Merge Two Sorted Lists | Easy | https://leetcode.com/problems/merge-two-sorted-lists/ |
| 141 | [ ] Linked List Cycle | Easy | https://leetcode.com/problems/linked-list-cycle/ |
| 19 | [ ] Remove Nth Node From End of List | Medium | https://leetcode.com/problems/remove-nth-node-from-end-of-list/ |
| 23 | [ ] Merge k Sorted Lists | Hard | https://leetcode.com/problems/merge-k-sorted-lists/ |
| 2 | [ ] Add Two Numbers | Medium | https://leetcode.com/problems/add-two-numbers/ |
| 25 | [ ] Reverse Nodes in k-Group | Hard | https://leetcode.com/problems/reverse-nodes-in-k-group/ |
| 138 | [ ] Copy List with Random Pointer | Medium | https://leetcode.com/problems/copy-list-with-random-pointer/ |
| 143 | [ ] Reorder List | Medium | https://leetcode.com/problems/reorder-list/ |
| 160 | [ ] Intersection of Two Linked Lists | Easy | https://leetcode.com/problems/intersection-of-two-linked-lists/ |

## Common Pitfalls
- Always use a dummy head when the list's head itself might change (avoids special-casing).
- Null-check `->next` before dereferencing — the #1 crash source.
- Memory leaks: `delete` removed nodes if not using smart pointers (LeetCode doesn't enforce this, but good C++ habit).
- Losing the `next` pointer before rewiring it — save it in a temp variable first.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
