class Solution {
public:
    string sortVowels(string s) {
        vector<char> vowel;
        for(int i = 0 ; i< s.length(); i++){
            if((s[i] == 'a' ||  s[i] == 'e'  || s[i] == 'i'  || s[i] == 'o' || s[i] == 'u' ) || 
            (s[i] == 'A' ||  s[i] == 'E'  || s[i] == 'I'  || s[i] == 'O' || s[i] == 'U' )){
                vowel.push_back(s[i]);
            }
        }
        sort(vowel.begin() ,  vowel.end());
        reverse(vowel.begin(), vowel.end());
        int LastIndex = vowel.size() -1;
          for(int i = 0 ; i< s.length(); i++){
            if((s[i] == 'a' ||  s[i] == 'e'  || s[i] == 'i'  || s[i] == 'o' || s[i] == 'u' ) || 
            (s[i] == 'A' ||  s[i] == 'E'  || s[i] == 'I'  || s[i] == 'O' || s[i] == 'U' )){
                s[i] = vowel[LastIndex];
                LastIndex--;
            }
        }
        return s;
    }
};