#include <iostream>
#include <climits>
using namespace std;


struct Node {
    int data;
    Node* left;
    Node* right;
};


Node* CreateNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to find the index of a value in an array
int FindIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Function to build the binary tree from inorder and preorder arrays
Node* BuildTree(int InOrder[], int PreOrder[], int InStart, int InEnd, int &PreIndex) {
    if (InStart > InEnd) {
        return NULL;
    }

    Node* root = CreateNode(PreOrder[PreIndex++]);

    if (InStart == InEnd) {
        return root;
    }

    int InIndex = FindIndex(InOrder, InStart, InEnd, root->data);

    root->left = BuildTree(InOrder, PreOrder, InStart, InIndex - 1, PreIndex);
    root->right = BuildTree(InOrder, PreOrder, InIndex + 1, InEnd, PreIndex);

    return root;
}


struct Info {
    int size;    // Size of the subtree
    int max;     // Max value in the subtree
    int min;     // Min value in the subtree
    int ans;     // Size of the largest BST
    bool isBST;  // Is the subtree a BST
};

// Function to find the size of the largest BST subtree
Info LargestBST(Node* root) {
    if (!root) {
        return {0, INT_MIN, INT_MAX, 0, true};
    }

    if (!root->left && !root->right) {
        return {1, root->data, root->data, 1, true};
    }

    Info left = LargestBST(root->left);
    Info right = LargestBST(root->right);

    Info curr;
    curr.size = 1 + left.size + right.size;

    if (left.isBST && right.isBST && root->data > left.max && root->data < right.min) {
        curr.min = left.size ? left.min : root->data;
        curr.max = right.size ? right.max : root->data;

        curr.ans = curr.size;
        curr.isBST = true;
        return curr;
    }

    curr.ans = left.ans > right.ans ? left.ans : right.ans;
    curr.isBST = false;
    return curr;
}

int main() {
    
    FILE *file = fopen("input.txt", "r");
    FILE *Output = fopen("output.txt" , "w");
    fclose(Output);
    Output = fopen("output.txt" , "a");
    

    int n;
    fscanf(file, "%d", &n);

    int inorder[n];
    int preorder[n];

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &inorder[i]);
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &preorder[i]);
    }

    fclose(file);

    int preIndex = 0;
    Node* root = BuildTree(inorder, preorder, 0, n - 1, preIndex);

    Info result = LargestBST(root);

    fprintf(Output, "The size of the largest BST is %d \n" , result.ans);

    return 0;
}
