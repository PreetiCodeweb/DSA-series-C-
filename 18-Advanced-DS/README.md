# Advanced Data Structures (Segment Tree, Fenwick Tree, DSU) — C++ DSA Notes

## Overview
Once comfortable with the core patterns, these structures unlock range-query and range-update
problems in O(log n): Fenwick Tree (Binary Indexed Tree) for prefix sums, Segment Tree for general range
queries (sum/min/max) with point or range updates, and DSU (revisited) for dynamic connectivity.

## How to Recognize This Pattern
- "Range sum/min/max query with point updates" -> Segment Tree or Fenwick Tree
- "Count inversions online / prefix sum with updates" -> Fenwick Tree
- "Range update + range query" -> Segment Tree with lazy propagation
- "Dynamic connectivity / Kruskal's MST" -> DSU (Union-Find)

## Core Templates (C++)
### Fenwick Tree (Binary Indexed Tree) — Point Update, Prefix Sum Query
```cpp
struct Fenwick {
    vector<long long> tree;
    int n;
    Fenwick(int n) : n(n), tree(n + 1, 0) {}
    void update(int i, long long delta) {       // 1-indexed
        for (; i <= n; i += i & (-i)) tree[i] += delta;
    }
    long long query(int i) {                    // prefix sum [1..i]
        long long s = 0;
        for (; i > 0; i -= i & (-i)) s += tree[i];
        return s;
    }
    long long rangeQuery(int l, int r) { return query(r) - query(l - 1); }
};
```

### Segment Tree — Range Sum, Point Update
```cpp
struct SegTree {
    int n;
    vector<long long> tree;
    SegTree(int n) : n(n), tree(4 * n, 0) {}

    void build(vector<int>& a, int node, int l, int r) {
        if (l == r) { tree[node] = a[l]; return; }
        int mid = (l + r) / 2;
        build(a, 2*node, l, mid);
        build(a, 2*node+1, mid+1, r);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) { tree[node] = val; return; }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2*node, l, mid, idx, val);
        else update(2*node+1, mid+1, r, idx, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return query(2*node, l, mid, ql, qr) + query(2*node+1, mid+1, r, ql, qr);
    }
};
```

### DSU with Path Compression + Union by Rank (see also Graphs topic)
```cpp
struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
    }
};
```

## Time & Space Complexity
| Structure | Build | Point Update | Range Query | Space |
|---|---|---|---|---|
| Fenwick Tree | O(n log n) | O(log n) | O(log n) | O(n) |
| Segment Tree | O(n) | O(log n) | O(log n) | O(4n) |
| Segment Tree + Lazy Propagation | O(n) | O(log n) range update | O(log n) | O(4n) |
| DSU (path compression + rank) | O(n) | ~O(alpha(n)) per union/find | - | O(n) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 307 | [ ] Range Sum Query - Mutable | Medium | https://leetcode.com/problems/range-sum-query-mutable/ |
| 315 | [ ] Count of Smaller Numbers After Self | Hard | https://leetcode.com/problems/count-of-smaller-numbers-after-self/ |
| 218 | [ ] The Skyline Problem | Hard | https://leetcode.com/problems/the-skyline-problem/ |
| 732 | [ ] My Calendar III | Hard | https://leetcode.com/problems/my-calendar-iii/ |
| 1584 | [ ] Min Cost to Connect All Points | Medium | https://leetcode.com/problems/min-cost-to-connect-all-points/ |
| 1697 | [ ] Checking Existence of Edge Length Limited Paths | Hard | https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/ |
| 327 | [ ] Count of Range Sum | Hard | https://leetcode.com/problems/count-of-range-sum/ |

## Common Pitfalls
- Segment tree array size must be at least `4 * n` to be safe for all tree shapes.
- Fenwick Tree is 1-indexed by convention — off-by-one errors are common when mapping 0-indexed input arrays.
- Lazy propagation logic is easy to get subtly wrong — always push down pending updates before recursing into children.
- DSU without both path compression AND union by rank/size still works but loses the near-O(1) amortized guarantee.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
