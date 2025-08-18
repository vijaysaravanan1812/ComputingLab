//https://leetcode.com/problems/diameter-of-binary-tree/
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
    int diameter = INT_MIN;
    int f(TreeNode* root){
        if(root == NULL)
            return 0;
        int leftSubTree = f(root->left);
        int rightSubTree = f(root->right);
        diameter = max(diameter , leftSubTree + rightSubTree);
        return 1 + max(leftSubTree , rightSubTree);
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
         f(root);
        return diameter;
    }
};