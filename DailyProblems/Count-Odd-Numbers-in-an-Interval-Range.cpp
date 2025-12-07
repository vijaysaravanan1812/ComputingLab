1class Solution {
2public:
3    int countOdds(int low, int high) {
4        int Size = high - low + 1;
5        if(Size % 2 == 0)
6            return Size/2;
7        else{
8            if((high % 2 == 0 && low % 2 == 0)){
9                return Size/2;
10            } else if(!(high % 2 == 0 && low % 2 == 0) ) {
11                return  Size/2 + 1;
12            }
13                
14        } 
15        return  Size/2;
16    }
17};