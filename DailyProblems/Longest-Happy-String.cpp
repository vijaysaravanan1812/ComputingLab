class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> Common;
        if(a > 0)
            Common.push({a , 'a'});
        if(b > 0)
            Common.push({b , 'b'});
        if(c > 0)
            Common.push({c , 'c'});
        string res = "";
        while(!Common.empty()){
            auto Node = Common.top();
            int count1 = Node.first;
            char char1 = Node.second;
            Common.pop();
            int n = res.size();
            if(n >= 2 && res[n - 2] == char1 && res[n - 1] == char1){
                if(Common.empty())
                    break;
                auto [count2 , char2] = Common.top();
                Common.pop();
                res.push_back(char2);
                count2--;
             
                if(count2 > 0)
                    Common.push({count2, char2});
                if(count1 > 0)
                    Common.push({count1 , char1});
            }else{
                res.push_back(char1);
                count1--;
                if(count1 > 0)
                    Common.push({count1, char1});
            }
        }
        return res;

    }
};