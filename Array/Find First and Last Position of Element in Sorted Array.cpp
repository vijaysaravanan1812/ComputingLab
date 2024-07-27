#include <vector>

using namespace std;

class Solution {
public:
    int binarySearch(vector<int>& nums, int target, bool findFirst) {
        int left = 0;
        int right = nums.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                result = mid;
                if (findFirst)
                    right = mid - 1; // Continue searching on the left side
                else
                    left = mid + 1; // Continue searching on the right side
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftIndex = binarySearch(nums, target, true);
        int rightIndex = binarySearch(nums, target, false);
        
        return {leftIndex, rightIndex};
    }
};
