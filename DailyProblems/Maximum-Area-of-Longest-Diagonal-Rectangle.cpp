class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        unordered_map<float , vector<vector<int>>> Diagonal;
        for(int i = 0 ; i < dimensions.size(); i++){
            int length = dimensions[i][0];
            int width = dimensions[i][1];
            float diagonal = sqrt(length * length + width * width );
            Diagonal[diagonal].push_back({dimensions[i][0] , dimensions[i][1]});
        }
        float Maxi = 0;
        for(auto x : Diagonal){
            cout<<"Key :"<<x.first;
            Maxi = max(Maxi , x.first);
            for(auto e : x.second){
                cout<<" "<<e[0]<<" "<<e[1]<<" \n";
            }
        }

        int MaximumArea = 0;
        if(Diagonal[Maxi].size()> 1){
            for(int i = 0 ; i< Diagonal[Maxi].size(); i++ ){
                MaximumArea  = max( MaximumArea ,Diagonal[Maxi][i][0]  * Diagonal[Maxi][i][1] );
            }
            return MaximumArea;
        }
        return Diagonal[Maxi][0][0] * Diagonal[Maxi][0][1];
    }
};