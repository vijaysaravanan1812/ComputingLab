class Solution {
public:
    string removeDigit(string number, char digit) {
        int n = number.size();
        int last = -1;

        for(int i = 0; i < n; i++){
            if(number[i] == digit){
                last = i;
                if(i + 1 < n && number[i+1] > number[i]){
                    return number.substr(0, i) + number.substr(i+1);
                }
            }
        }

        // If no better spot found, remove last occurrence
        return number.substr(0, last) + number.substr(last + 1);
    }
};
