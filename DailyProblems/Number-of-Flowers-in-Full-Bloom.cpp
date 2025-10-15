class Solution {
    static bool compare(vector<int> a, vector<int> b){
        if(a[0] < b[0]){
            return true;
        }
        return false;
    }
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        vector<vector<int>> indices;
        for(int i = 0 ; i < people.size() ; i++){
            indices.push_back({people[i] , i });
        }
        sort(indices.begin() , indices.end(), compare);

        priority_queue<int , vector<int> , greater<int>> startTime;
        priority_queue<int , vector<int > , greater<int>> endTime;
        for(int i = 0 ; i < flowers.size() ; i++){
            startTime.push(flowers[i][0]);
            endTime.push(flowers[i][1]);
        }
        int flowerCount = 0 ;
        vector<int> result(people.size(), 0);
        for(auto x : indices){
            int PeopleArival = x[0];
            int PeopleIndex = x[1];
            while(!startTime.empty() && startTime.top() <= PeopleArival){
                startTime.pop();
                flowerCount++;
            }
            while(!endTime.empty() &&  endTime.top() < PeopleArival){
                endTime.pop();
                flowerCount--;
            }
            result[PeopleIndex] = flowerCount;
        }
        return result;
     }
};