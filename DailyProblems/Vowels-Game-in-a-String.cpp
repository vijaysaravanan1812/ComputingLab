class Solution {
public:
    bool doesAliceWin(string s) {
        vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int vowel_count = 0;

        for(auto x : s){
            for(auto character : vowels){
                if(character == x){
                    vowel_count++;
                    break;
                }
            }
        }
        if(vowel_count == 0)
            return false;
        else
            return true;
    }
};