# Trie (Prefix Tree) — C++ DSA Notes

## Overview
A trie stores strings as paths in a tree, sharing common prefixes. Ideal for prefix search,
autocomplete, and word-dictionary problems requiring fast prefix lookups.

## How to Recognize This Pattern
- "Implement autocomplete / prefix search" -> Trie
- "Word search with wildcards" -> Trie + DFS
- "Longest common prefix of many strings" -> Trie or simple string scan
- "Word Break / word dictionary lookups at scale" -> Trie for O(word length) lookups

## Core Templates (C++)
### Trie Implementation
```cpp
struct TrieNode {
    TrieNode* children[26] = {};
    bool isEnd = false;
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i]) node->children[i] = new TrieNode();
            node = node->children[i];
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        TrieNode* node = find(word);
        return node && node->isEnd;
    }

    bool startsWith(const string& prefix) {
        return find(prefix) != nullptr;
    }

private:
    TrieNode* find(const string& s) {
        TrieNode* node = root;
        for (char c : s) {
            int i = c - 'a';
            if (!node->children[i]) return nullptr;
            node = node->children[i];
        }
        return node;
    }
};
```

### Word Search II style DFS-on-Trie (Board + Trie pruning)
```cpp
void dfs(vector<vector<char>>& board, int r, int c, TrieNode* node, string& path, vector<string>& result) {
    char ch = board[r][c];
    if (ch == '#' || !node->children[ch - 'a']) return;
    node = node->children[ch - 'a'];
    path.push_back(ch);
    if (node->isEnd) { result.push_back(path); node->isEnd = false; } // avoid dup
    board[r][c] = '#';
    int dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0};
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr >= 0 && nr < board.size() && nc >= 0 && nc < board[0].size())
            dfs(board, nr, nc, node, path, result);
    }
    board[r][c] = ch;
    path.pop_back();
}
```

## Time & Space Complexity
| Operation | Time | Space |
|---|---|---|
| Insert word (length L) | O(L) | O(L * 26) worst |
| Search / startsWith | O(L) | O(1) |
| Total space for N words, avg length L | - | O(N * L) worst (less with shared prefixes) |

## LeetCode Problem Checklist
| # | Problem | Difficulty | Link |
|---|---------|------------|------|
| 208 | [ ] Implement Trie (Prefix Tree) | Medium | https://leetcode.com/problems/implement-trie-prefix-tree/ |
| 211 | [ ] Design Add and Search Words Data Structure | Medium | https://leetcode.com/problems/design-add-and-search-words-data-structure/ |
| 212 | [ ] Word Search II | Hard | https://leetcode.com/problems/word-search-ii/ |
| 14 | [ ] Longest Common Prefix | Easy | https://leetcode.com/problems/longest-common-prefix/ |
| 648 | [ ] Replace Words | Medium | https://leetcode.com/problems/replace-words/ |
| 676 | [ ] Implement Magic Dictionary | Medium | https://leetcode.com/problems/implement-magic-dictionary/ |
| 1268 | [ ] Search Suggestions System | Medium | https://leetcode.com/problems/search-suggestions-system/ |

## Common Pitfalls
- Fixed-size `children[26]` array assumes lowercase-only alphabet — use a hashmap of children for wider character sets.
- Remember to free/manage trie node memory in production code (not required on LeetCode, but good C++ hygiene).
- Marking `isEnd = false` after found in Word Search II avoids duplicate results but mutates shared trie — fine within a single call, dangerous if trie is reused elsewhere.

## My Solutions
Add your solved `.cpp` files in this folder as you go, named after the problem, e.g. `two-sum.cpp`.
