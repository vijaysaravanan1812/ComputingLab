// 307. Range Sum Query - Mutable

// Given an integer array nums, handle multiple queries of the following types:

// Update the value of an element in nums.
// Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
// Implement the NumArray class:

// NumArray(int[] nums) Initializes the object with the integer array nums.
// void update(int index, int val) Updates the value of nums[index] to be val.
// int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 

// Example 1:

// Input
// ["NumArray", "sumRange", "update", "sumRange"]
// [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
// Output
// [null, 9, null, 8]

// Explanation
// NumArray numArray = new NumArray([1, 3, 5]);
// numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
// numArray.update(1, 2);   // nums = [1, 2, 5]
// numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8
 

// Constraints:

// 1 <= nums.length <= 3 * 104
// -100 <= nums[i] <= 100
// 0 <= index < nums.length
// -100 <= val <= 100
// 0 <= left <= right < nums.length
// At most 3 * 104 calls will be made to update and sumRange.

class NumArray {
    vector<int> seg;
    int n; 
    void build(vector<int> &nums , int index , int l, int r){
        if(l == r){
            seg[index] = nums[l];
            return ;
        }
        int mid = (l +r)/2;
        build(nums, 2* index , l , mid);
        build(nums, 2 * index + 1, mid + 1 , r);
        seg[index ]  = seg[2 * index ] + seg[2 * index + 1];
    }
    int query(int index, int l , int r , int ql ,int qr){
        if(qr < l || ql > r)
            return 0;
        if(ql <= l && r <= qr)
            return seg[index];
        int mid = (l + r)/2;
        int leftSum  = query(2 * index , l , mid , ql , qr);
        int rightSum = query(2 * index + 1, mid + 1 , r ,ql, qr );
        return leftSum + rightSum;
    }
    void update(int index , int l , int r , int pos, int val){
        if(l == r){
            seg[index] = val;
            return;
        }
            
        int mid = (l + r)/2;
        if(pos <= mid)
            update(2* index , l , mid, pos , val);
        else
            update(2 * index + 1 , mid + 1, r , pos, val);

        seg[index] = seg[2 * index] + seg[2 * index + 1];
    }
public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        seg.resize(4 * n);
        build(nums, 1 , 0 , n -1);
    }
    
    void update(int index, int val) {
        update(1 , 0 , n -1 ,index ,val);
    }
    
    int sumRange(int left, int right) {
        return query(1 , 0 , n -1, left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */