#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> st(nums.begin(), nums.end());
    int longest = 0;

    for (int num : st) {
        // Start only if it's the beginning of a sequence
        if (st.find(num - 1) == st.end()) {
            int currentNum = num;
            int count = 1;

            while (st.find(currentNum + 1) != st.end()) {
                currentNum++;
                count++;
            }

            longest = max(longest, count);
        }
    }

    return longest;
}

int main() {
    vector<int> nums = {100, 4, 200, 1, 3, 2};

    cout << "Longest Consecutive Sequence Length: "
         << longestConsecutive(nums) << endl;

    return 0;
}
