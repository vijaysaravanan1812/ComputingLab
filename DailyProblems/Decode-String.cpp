class Solution {
public:
    string decodeString(string s) {
        int k = 0;
        stack<string> st;
        for (auto c : s) {
            if (c != ']') {
                string temp(1, c);
                st.push(temp);
            } else {
                string substr = "";
                while (!st.empty() && st.top() !=  "[") {
                    substr = st.top() + substr;
                    st.pop();
                }
                st.pop();
                string k_str = "";
                while (!st.empty() && isdigit(st.top()[0])) {
                    k_str = st.top() + k_str;
                    st.pop();
                }
                int k = 0;
                if (!k_str.empty()) {
                    k = std::stoi(k_str);
                }
                std::string repeated_substr = "";
                for (int i = 0; i < k; ++i) {
                    repeated_substr += substr;
                }
                st.push(repeated_substr);
            }
        }
          std::string result = "";
        while (!st.empty()) {
            result = st.top() + result;
            st.pop();
        }
        return result;
    }
};