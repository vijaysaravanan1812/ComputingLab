1class Solution {
2public:
3    bool search(vector<int>& nums, int target) {
4        int low =0 ;
5        int high = nums.size() - 1;
6        while(low <= high){
7            int mid = low + (high  - low)/2;
8            if(nums[mid] == target){
9                return true;
10            } 
11            if(nums[low] == nums[mid] && nums[mid] == nums[high]){
12                low++;
13                high--;
14                continue;
15            }
16
17            //Identify sorted portion
18            if(nums[low] <= nums[mid]){
19                if(nums[low] <= target && target <= nums[mid]){
20                    high = mid - 1;
21                }else{
22                    low = mid + 1;
23                }
24            }else{
25                if(nums[mid] <= target && target <= nums[high] ){
26                    low = mid + 1;
27                }else{
28                    high = mid - 1;
29                }
30            }
31        }
32
33        return false;
34    }
35};