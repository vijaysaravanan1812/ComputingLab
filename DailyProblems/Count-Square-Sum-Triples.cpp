1class Solution {
2public:
3    int countTriples(int n) {
4        int count = 0;
5        for(int a = 1 ; a <= n; a++){
6            for(int b = 1; b <= n; b++){
7                int sum = a * a + b * b;
8                int c = sqrt(sum);
9                if(c * c == sum && c <= n){
10                    count++;
11                } 
12            }
13        }
14        return count;
15    }
16};