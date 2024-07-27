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
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        queue<TreeNode *> Myqueue;
        if(root == NULL)
            return {};
        Myqueue.push(root);
        while(!Myqueue.empty()){
            int size = Myqueue.size();
            vector<int> level;
            for(int i = 0 ; i < size ; i++){
                TreeNode* node = Myqueue.front();
                Myqueue.pop();
                if(node->left != NULL) Myqueue.push(node->left);
                if(node->right != NULL) Myqueue.push(node->right);
                level.push_back(node->val);  
            }
            ans.push_back(level);
        }
        return ans;
    }
};