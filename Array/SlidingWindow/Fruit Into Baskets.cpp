// There is only one row of fruit trees on the farm, oriented left to right. An integer array called fruits represents the trees, where fruits[i] denotes the kind of fruit produced by the ith tree.



// The goal is to gather as much fruit as possible, adhering to the owner's stringent rules:



// 1) There are two baskets available, and each basket can only contain one kind of fruit. The quantity of fruit each basket can contain is unlimited.

// 2) Start at any tree, but as you proceed to the right, select exactly one fruit from each tree, including the starting tree. One of the baskets must hold the harvested fruits.

// 3) Once reaching a tree with fruit that cannot fit into any basket, stop.



// Return the maximum number of fruits that can be picked.


// Example 1

// Input : fruits = [1, 2, 1]

// Output : 3

// Explanation : We will start from first tree.

// The first tree produces the fruit of kind '1' and we will put that in the first basket.

// The second tree produces the fruit of kind '2' and we will put that in the second basket.

// The third tree produces the fruit of kind '1' and we have first basket that is already holding fruit of kind '1'. So we will put it in first basket.

// Hence we were able to collect total of 3 fruits.

// Example 2
–––––
// Input : fruits = [1, 2, 3, 2, 2]

// Output : 4

// Explanation : we will start from second tree.

// The first basket contains fruits from second , fourth and fifth.

// The second basket will contain fruit from third tree.

// Hence we collected total of 4 fruits.

// Example 3

// Input : fruits = [1, 2, 3, 4, 5]

// Output:

// 2
// Constraints

// 1 <= fruits.length <= 105
// 0 <= fruits[i] < fruits.length

class Solution{
  public:
    int totalFruits(vector<int>& fruits){
        //your code goes here
        int left = 0, right = 0;
        int size = fruits.size();
        unordered_map<int , int > Track;
        int currentMax = 0 , maximum = 0;
        while(right < size){
            Track[fruits[right]]++;
            if(Track.size() > 2){
                Track[fruits[left]]--;
                if(Track[fruits[left]] == 0){
                    Track.erase(fruits[left]);
                }
                left++;
            }
            currentMax = right - left + 1;
            maximum = max(currentMax , maximum);
            right++;
        }
        return maximum;
    }
};