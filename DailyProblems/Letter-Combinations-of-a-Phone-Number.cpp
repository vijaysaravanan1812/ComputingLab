class Solution {
    void backtrack(int i , string &digits , vector<string>& res , vector<string>&mapping, string &path ){       
        if(i == digits.length()){
            res.push_back(path);
            return ;
        }
        string letter = mapping[digits[i] - '0'];
        for(auto c : letter ){
            path.push_back(c);
            backtrack(i + 1, digits, res , mapping, path);
            path.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if(digits == "")
            return {};
        vector<string> mappings = {
            "", "", "abc", "def","ghi",
            "jkl", "mno", "pqrs", "tuv",
            "wxyz"
        };
        string path ="";
        vector<string> res = {};
        backtrack(0 , digits, res , mappings, path);
        return res;
    }
};