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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        stack<TreeNode *> Stack1;
        stack<TreeNode *> Stack2;
        vector<vector<int> > Result;

        if(root == NULL)
        {
            return {};
        }


        Stack1.push(root);



        while(!Stack1.empty() || !Stack2.empty()){
            vector<int> level;
            while(!Stack1.empty()){
                TreeNode * Node = Stack1.top();
                level.push_back(Node->val);
                Stack1.pop();
                if(Node->left){
                    Stack2.push(Node->left);
                }
                if(Node->right){
                    Stack2.push(Node->right);
                }
                if(Stack1.empty()){
                  
                    Result.push_back(level);
                    level.clear();
                }
            }

            while(!Stack2.empty()){
                TreeNode* Node = Stack2.top();
                level.push_back(Node->val);
                Stack2.pop();
                if(Node->right){
                    Stack1.push(Node->right);
                }
                if(Node->left){
                    Stack1.push(Node->left);
                }
                if(Stack2.empty()){
                    
                    Result.push_back(level);
                    level.clear();
                }
            }
        }

        return Result;
        
    }
};