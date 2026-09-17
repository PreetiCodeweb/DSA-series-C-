/*
You are given an integer array nums. You can pick any subset of numbers from it [you can pick all, some, or none].
Return the maximum possible sum of the picked numbers such that the sum is divisible by 3.
If no such sum exists, return 0.

Example: nums = [3,6,5,1,8]
Total sum = 23, which is not divisible by 3. If we drop the smallest number that breaks divisibility, i.e. 5, we get 23-5 = 18, which is divisible by 3 and is the maximum possible.
*/

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int total = 0;
        vector<int> rem1, rem2;

        for (int x : nums) {
            total += x;
            if (x % 3 == 1) rem1.push_back(x);
            else if (x % 3 == 2) rem2.push_back(x);
        }

        sort(rem1.begin(), rem1.end());
        sort(rem2.begin(), rem2.end());

        int rem = total % 3;
        if (rem == 0) return total;

        int ans = 0;
        if (rem == 1) {
            int remove1 = rem1.size() >= 1? rem1[0] : INT_MAX;
            int remove2 = rem2.size() >= 2? rem2[0] + rem2[1] : INT_MAX;
            int toRemove = min(remove1, remove2);
            if (toRemove == INT_MAX) return 0; // nothing can be removed
            ans = total - toRemove;
        } else { // rem == 2
            int remove1 = rem2.size() >= 1? rem2[0] : INT_MAX;
            int remove2 = rem1.size() >= 2? rem1[0] + rem1[1] : INT_MAX;
            int toRemove = min(remove1, remove2);
            if (toRemove == INT_MAX) return 0;
            ans = total - toRemove;
        }
        return ans;
    }
};