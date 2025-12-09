1/**
2 * Definition for a binary tree node.
3 * struct TreeNode {
4 *     int val;
5 *     TreeNode *left;
6 *     TreeNode *right;
7 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
8 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
9 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
10 * };
11 */
12class Solution {
13    bool Symmetric(TreeNode *left , TreeNode * right){
14        if(left == NULL && right == NULL){
15            return true;
16        }
17        if(left == NULL || right == NULL){
18            return false;
19        }
20        if(left->val != right->val){
21            return false;
22        }
23
24        return Symmetric(left->left, right->right) && Symmetric(left->right , right->left);
25    }
26public:
27    bool isSymmetric(TreeNode* root) {
28        if(root == NULL){
29            return true;
30        }
31        return Symmetric(root->left , root->right);
32    }
33
34
35};