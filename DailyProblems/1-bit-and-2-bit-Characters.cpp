class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int i = 0;
        while (i < bits.size() - 1) { // stop before the last bit
            if (bits[i] == 1) {
                i += 2; // 2-bit character
            } else {
                i += 1; // 1-bit character
            }
        }
        return i == bits.size() - 1;
    }
};