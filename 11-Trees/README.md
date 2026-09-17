# Trees (Binary Tree & BST) — C++ DSA Notes

## Overview
Tree problems are almost always recursive: solve for left subtree, solve for right subtree, combine.
BSTs add the ordering invariant (left < node < right) enabling O(log n) operations when balanced.

## How to Recognize This Pattern
- "Traverse / process every node" -> DFS (pre/in/post-order) or BFS (level order)
- "Validate / search in BST" -> exploit ordering invariant
- "Lowest common ancestor" -> recursive bottom-up search
- "Path sum / diameter / max depth" -> post-order DFS returning info upward

## Core Templates (C++)
### Node Definition
```cpp
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

### DFS Traversals
```cpp
void inorder(TreeNode* root, vector<int>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}
```

### BFS Level Order
```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        vector<int> level;
        for (int i = 0; i < sz; i++) {
            TreeNode* n = q.front(); q.pop();
            level.push_back(n->val);
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        res.push_back(level);
    }
    return res;
}
```

### Validate BST (pass bounds down)
```cpp
bool isValidBST(TreeNode* root, long lo = LONG_MIN, long hi = LONG_MAX) {
    if (!root) return true;
    if (root->val <= lo || root->val >= hi) return false;
    return isValidBST(root->left, lo, root->val) && isValidBST(root->right, root->val, hi);
}
```

### Lowest Common Ancestor
```cpp
TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* l = lca(root->left, p, q);
    TreeNode* r = lca(root->right, p, q);
    if (l && r) return root;
    return l ? l : r;
}
```

### Diameter (post-order returning height, updating global answer)
```cpp
int best = 0;
int height(TreeNode* root) {
    if (!root) return 0;
    int lh = height(root->left), rh = height(root->right);
    best = max(best, lh + rh);
    return 1 + max(lh, rh);
}
```

## Time & Space Complexity
| Operation | Balanced Tree | Skewed Tree |
|---|---|---|
| Search/Insert/Delete (BST) | O(log n) | O(n) |
| DFS/BFS traversal | O(n) | O(n) |
| Recursion stack space | O(log n) | O(n) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 104 | [ ] Maximum Depth of Binary Tree | Easy | https://leetcode.com/problems/maximum-depth-of-binary-tree/ |
| 226 | [ ] Invert Binary Tree | Easy | https://leetcode.com/problems/invert-binary-tree/ |
| 543 | [ ] Diameter of Binary Tree | Easy | https://leetcode.com/problems/diameter-of-binary-tree/ |
| 98 | [ ] Validate Binary Search Tree | Medium | https://leetcode.com/problems/validate-binary-search-tree/ |
| 102 | [ ] Binary Tree Level Order Traversal | Medium | https://leetcode.com/problems/binary-tree-level-order-traversal/ |
| 236 | [ ] Lowest Common Ancestor of a Binary Tree | Medium | https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/ |
| 105 | [ ] Construct Binary Tree from Preorder and Inorder Traversal | Medium | https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/ |
| 124 | [ ] Binary Tree Maximum Path Sum | Hard | https://leetcode.com/problems/binary-tree-maximum-path-sum/ |
| 297 | [ ] Serialize and Deserialize Binary Tree | Hard | https://leetcode.com/problems/serialize-and-deserialize-binary-tree/ |
| 230 | [ ] Kth Smallest Element in a BST | Medium | https://leetcode.com/problems/kth-smallest-element-in-a-bst/ |
| 108 | [ ] Convert Sorted Array to Binary Search Tree | Easy | https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/ |

## Common Pitfalls
- Always null-check before dereferencing `left`/`right`.
- BST validation must pass down min/max bounds, not just compare with immediate parent.
- Post-order (bottom-up) is the right choice whenever a node's answer depends on children's answers (height, diameter, sum).
- Deep/skewed trees can blow the recursion stack — consider iterative traversal with an explicit stack for huge inputs.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
