/*
PROBLEM STATEMENT - The Brute-Force Idea

A list of datas are provided (one array of datas).
Another data / array is there considered to be target.
sum of the datas fetching from the list of datas and the target should be equal.
in the result , the indices of the values used in the data list will be shown, not the values. 
*/

#include <vector>    // LeetCode uses vector<int> to represent a dynamic array.
using namespace std;      // In C++, a normal array has fixed size. LeetCode gives you a vector<int> which is a resizable array.

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {     // vector<int>& nums -> the input array, passed by reference & for speed
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }

        return {};
    }
};


/*
How Good Is This Solution?

This is called the Brute Force approach.
Time Complexity: O(n²) - For n elements, you check roughly n * n / 2 pairs. If n=1000, you do ∼500k checks. It works but gets slow for large arrays.
Space Complexity: O(1) - You don't use any extra memory.

The optimal solution is O(n) using a Hash Map. Idea:
While looping, remember what numbers you've seen. For each number x, you need target - x. Have you seen it before?
*/