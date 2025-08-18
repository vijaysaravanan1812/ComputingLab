class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0; // Handle empty case

        int minPrice = INT_MAX;
        int maxProfit = 0;

        for (int i = 0; i < prices.size(); i++) {
            if (prices[i] < minPrice) {
                minPrice = prices[i]; // Update min price
            } 
            maxProfit = max(maxProfit, prices[i] - minPrice); // Calculate max profit
        }

        return maxProfit;
    }
};
