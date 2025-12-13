1class Solution {
2    bool isValidCode(string& s) {
3        if (s == "") {
4            return false;
5        }
6        for (auto c : s) {
7            if (!(isalnum(c) || c == '_')) {
8                return false;
9            }
10        }
11        return true;
12    }
13
14    static bool compare(pair<int, string>& a, pair<int, string>& b) {
15        if (a.first == b.first) {
16            return a.second < b.second;
17        }
18        return a.first < b.first;
19    }
20
21public:
22    vector<string> validateCoupons(vector<string>& code,
23                                   vector<string>& businessLine,
24                                   vector<bool>& isActive) {
25        vector<pair<int, string>> ValidCoupon;
26        int numberOfCoupons = code.size();
27        unordered_map<string, int> business = {{"electronics" , 0},
28                                               {"grocery" , 1},
29                                               {"pharmacy" , 2},
30                                               {"restaurant" , 3}
31                                            };
32        for (int i = 0; i < numberOfCoupons; i++) {
33            if (!( isValidCode(code[i]) == false ||
34                  business.find(businessLine[i]) == business.end() ||
35                  isActive[i] == false)) {
36                ValidCoupon.push_back({business[businessLine[i]], code[i]});
37            }
38        }
39        sort(ValidCoupon.begin(), ValidCoupon.end(), compare);
40        vector<string> res;
41        for (int i = 0; i < ValidCoupon.size(); i++) {
42            res.push_back(ValidCoupon[i].second);
43        }
44        return res;
45    }
46};