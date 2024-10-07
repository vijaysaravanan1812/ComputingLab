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

int Height(Node *Temp)
{
    if (Temp == NULL)
        return -1;
    else
    {
        int Left = Height(Temp->left);
        int Right = Height(Temp->right);
        return 1 + max(Left, Right);
    }
}

void PostOrder(Node *Temp, FILE *file)
{
    if (Temp == NULL)
        return;

    PostOrder(Temp->left, file);

    PostOrder(Temp->right, file);
    fprintf(file, " %d ", Temp->data);
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
    fprintf(Output , "Pre Order Traversal\n");
    PostOrder(root , Output);
    fprintf(Output , "Height of treee %d\n", Height(root));
    


    return 0;
}
