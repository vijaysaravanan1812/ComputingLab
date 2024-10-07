#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// Tree Node Definition
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};

// Function to create a new tree node
TreeNode* createNode(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) {
        cerr << "Memory allocation failed" << endl;
        exit(1);
    }
    node->val = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// Function to build the tree
TreeNode* buildTree(int inorder[], int preorder[], int inStart, int inEnd, int& preIndex, int inOrderIndex[]) {
    if (inStart > inEnd) return nullptr;

    int rootValue = preorder[preIndex++];
    TreeNode* root = createNode(rootValue);

    // Find the index of the root in inorder array using the precomputed inOrderIndex
    int inIndex = inOrderIndex[rootValue];
    
    // Build left and right subtrees
    root->left = buildTree(inorder, preorder, inStart, inIndex - 1, preIndex, inOrderIndex);
    root->right = buildTree(inorder, preorder, inIndex + 1, inEnd, preIndex, inOrderIndex);
    
    return root;
}

// Function to calculate the height of the tree
int getHeight(TreeNode* node) {
    if (!node) return -1;  // Height of an empty tree is -1
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return max(leftHeight, rightHeight) + 1;
}

// Function to compute postorder traversal
void getPostorder(TreeNode* node, int postorder[], int& index) {
    if (!node) return;
    getPostorder(node->left, postorder, index);
    getPostorder(node->right, postorder, index);
    postorder[index++] = node->val;
}

// Function to delete the tree and free memory
void deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    // Open the input file
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    // Read the size of the arrays
    int size;
    inputFile >> size;

    // Read inorder and preorder arrays
    int inorder[size];
    int preorder[size];
    for (int i = 0; i < size; ++i) {
        inputFile >> inorder[i];
    }
    for (int i = 0; i < size; ++i) {
        inputFile >> preorder[i];
    }
    inputFile.close();

    // Create index map for inorder traversal
    int inOrderIndex[100]; // Adjust size if necessary
    for (int i = 0; i < size; ++i) {
        inOrderIndex[inorder[i]] = i;
    }

    int preIndex = 0;
    TreeNode* root = buildTree(inorder, preorder, 0, size - 1, preIndex, inOrderIndex);

    // Calculate height
    int height = getHeight(root);

    // Compute postorder traversal
    int postorder[size];
    int postIndex = 0;
    getPostorder(root, postorder, postIndex);

    // Open the output file
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    // Write the results to the output file
    outputFile << "Postorder: ";
    for (int i = 0; i < size; ++i) {
        outputFile << postorder[i] << " ";
    }
    outputFile << endl;

    outputFile << "Height: " << height << endl;
    outputFile.close();

    // Free memory
    deleteTree(root);

    return 0;
}
