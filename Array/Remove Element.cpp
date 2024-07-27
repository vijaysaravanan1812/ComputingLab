class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int j = 0; // Pointer to the next position to put a non-val element
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != val) {
                nums[j] = nums[i]; // Copy non-val element to position j
                j++; // Move pointer j forward
            }
        }

        return j; // j now represents the number of elements not equal to val
    }
};
