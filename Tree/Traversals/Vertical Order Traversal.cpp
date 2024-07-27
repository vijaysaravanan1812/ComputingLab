/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    void Vertical_Traversal(map<int, map<int, vector<int>>> &VerticalTraversal ,TreeNode *root, int col , int row){

        if(!root){
            return;
        }

        VerticalTraversal[col][row].push_back(root->val);

        Vertical_Traversal(VerticalTraversal , root->left , col - 1 , row + 1);
        Vertical_Traversal(VerticalTraversal , root->right , col + 1 , row + 1);
    }

public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int, map<int, vector<int>>> VerticalTraversal;
        Vertical_Traversal(VerticalTraversal , root , 0 , 0 );
        vector<vector<int>> Ans;
        for(auto m1 : VerticalTraversal){
            vector<int> Level;
            for(auto m2 : m1.second){
                sort(m2.second.begin(), m2.second.end()); 
                for(auto element : m2.second){
                    
                    Level.push_back(element);
                }
            }
            Ans.push_back(Level);
        }

        return Ans;
    }

};