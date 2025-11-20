class Solution {
    static bool compare(vector<int> &a , vector<int>&b){
        if (a[1] != b[1]) 
            return a[1] < b[1];
        return a[0] > b[0];
    }
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin() , intervals.end(), compare);
        int p1 = -1;
        int p2 = -1;
        int res = 0;

        for (const auto& it : intervals) {
            int left = it[0];
            int right = it[1];

            if (p2 < left) {
                // need two new points
                res += 2;
                p1 = right - 1;
                p2 = right;
            } else if (p1 < left) {
                // need one new point
                res += 1;
                p1 = p2;
                p2 = right;
            }
            // otherwise current [left,right] already contains p1 and p2
        }

        return res;

    }
};