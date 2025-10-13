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
    int Preorder(TreeNode * root , int maxVal){
        if(root == NULL){
            return 0;
        }
        int res ;
        if(root ->val >= maxVal){
            res = 1;
        }else{
            res = 0;
        }
        maxVal = max(root->val, maxVal);
        res += Preorder(root->left, maxVal);
        res += Preorder(root->right , maxVal);
        return res; 
    }
public:
    int goodNodes(TreeNode* root) {
        return Preorder(root , INT_MIN);
    }
};