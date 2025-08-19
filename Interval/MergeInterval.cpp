
// 
class Solution {
public:
    static bool compareInterval(vector<int> a , vector<int>b){
        return a[0] < b[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() == 0)
            return {};
        sort(intervals.begin(), intervals.end(), compareInterval);
        vector<vector<int>> Res;
        Res.push_back(intervals[0]);
        for(int i =  1 ; i < intervals.size()  ; i++){
            vector<int>& last  = Res.back();
            if(intervals[i][0] <= last[1] )
                last[1] = max(last[1] , intervals[i][1]);
            else
                Res.push_back(intervals[i]);
        }
        return Res;

    }
};