# Graphs — C++ DSA Notes

## Overview
Graphs generalize trees: nodes + edges, possibly cyclic, directed or undirected, weighted or not.
Core toolkit: BFS (shortest path, unweighted), DFS (connectivity, cycles, topological sort), Union-Find
(connectivity queries), Dijkstra (weighted shortest path), and topological sort (DAG ordering/dependencies).

## How to Recognize This Pattern
- "Shortest path, unweighted" -> BFS
- "Shortest path, weighted, non-negative" -> Dijkstra
- "Detect cycle / connected components" -> DFS or Union-Find
- "Course schedule / build order / dependency resolution" -> topological sort
- "Number of islands / connected regions on grid" -> BFS/DFS/Union-Find on grid

## Core Templates (C++)
### Adjacency List
```cpp
vector<vector<int>> adj(n); // adj[u] = list of neighbors
adj[u].push_back(v); adj[v].push_back(u); // undirected
```

### BFS Shortest Path (Unweighted)
```cpp
vector<int> bfs(int src, vector<vector<int>>& adj, int n) {
    vector<int> dist(n, -1);
    queue<int> q; q.push(src); dist[src] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); }
    }
    return dist;
}
```

### DFS (Recursive) + Cycle Detection (Directed)
```cpp
bool dfs(int u, vector<vector<int>>& adj, vector<int>& state) { // 0=unvisited,1=in-stack,2=done
    state[u] = 1;
    for (int v : adj[u]) {
        if (state[v] == 1) return true;             // back edge -> cycle
        if (state[v] == 0 && dfs(v, adj, state)) return true;
    }
    state[u] = 2;
    return false;
}
```

### Union-Find (Disjoint Set Union)
```cpp
struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }
};
```

### Topological Sort (Kahn's Algorithm, BFS)
```cpp
vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++) for (int v : adj[u]) indeg[v]++;
    queue<int> q;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }
    return order; // size < n means cycle exists
}
```

### Dijkstra's Algorithm
```cpp
vector<long long> dijkstra(int src, int n, vector<vector<pair<int,int>>>& adj) { // adj[u] = {v, weight}
    vector<long long> dist(n, LLONG_MAX);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    dist[src] = 0; pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

## Time & Space Complexity
| Algorithm | Time | Space |
|---|---|---|
| BFS/DFS | O(V + E) | O(V) |
| Union-Find (path compression + rank) | ~O(alpha(n)) per op | O(V) |
| Topological Sort (Kahn's) | O(V + E) | O(V) |
| Dijkstra (binary heap) | O((V + E) log V) | O(V) |
| Bellman-Ford (negative weights) | O(V * E) | O(V) |
| Floyd-Warshall (all pairs) | O(V^3) | O(V^2) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 200 | [ ] Number of Islands | Medium | https://leetcode.com/problems/number-of-islands/ |
| 133 | [ ] Clone Graph | Medium | https://leetcode.com/problems/clone-graph/ |
| 207 | [ ] Course Schedule | Medium | https://leetcode.com/problems/course-schedule/ |
| 210 | [ ] Course Schedule II | Medium | https://leetcode.com/problems/course-schedule-ii/ |
| 994 | [ ] Rotting Oranges | Medium | https://leetcode.com/problems/rotting-oranges/ |
| 684 | [ ] Redundant Connection | Medium | https://leetcode.com/problems/redundant-connection/ |
| 743 | [ ] Network Delay Time | Medium | https://leetcode.com/problems/network-delay-time/ |
| 127 | [ ] Word Ladder | Hard | https://leetcode.com/problems/word-ladder/ |
| 785 | [ ] Is Graph Bipartite? | Medium | https://leetcode.com/problems/is-graph-bipartite/ |
| 1584 | [ ] Min Cost to Connect All Points | Medium | https://leetcode.com/problems/min-cost-to-connect-all-points/ |
| 323 | [ ] Number of Connected Components in an Undirected Graph | Medium | https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/ |

## Common Pitfalls
- Forgetting to mark nodes visited before enqueuing (not after dequeuing) in BFS causes duplicate enqueues.
- Directed-graph cycle detection needs a 3-state (unvisited/in-stack/done) check, not just a 2-state visited array.
- Union-Find without path compression + union by rank degrades to O(n) per operation.
- Dijkstra fails with negative edge weights — use Bellman-Ford instead.
- On grids, encode `(row, col)` as `row * cols + col` for adjacency-list-style indexing, or just work directly with pairs.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
