class Solution {
public:

    int maxProfit(vector<int>& prices) {
        
        //find Minimum 
        int MinIndex = 0, MinimumNumber = INT_MAX; 
        int MaxProfit = 0, currentPrice = 0; 
        int Profit = 0;
        for(int i = 0; i < prices.size() ; i++){
            currentPrice  = prices[i];
            if(MinimumNumber > prices[i]){
                MinimumNumber = prices[i];
                MinIndex = i;
            }
            Profit = currentPrice - MinimumNumber;
            if(MaxProfit < Profit){
                MaxProfit = Profit;
            } 
        }
        return MaxProfit;
    }
};