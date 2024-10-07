#include <iostream>
#include <cstdlib>
#include<bits/stdc++.h>

using namespace std;

// Node structure with parent pointer
struct Node
{
    int data;
    Node *left;
    Node *right;
    Node *parent;
    Node(int val){
        this->data = val;
        this->left = NULL;
        this->parent = NULL;
        this->right = NULL;
    }
};


struct QueueNode {
    Node* node;
    int HorizontalDistance;  // horizontal distance
    QueueNode* next;
};

struct ListNode{
    int Data;
    ListNode * next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;

    Queue(){
        this->front = nullptr;
        this->rear = nullptr;
    }

    void enqueue(Node* node, int HorizontalDistance) {
        QueueNode* temp = new QueueNode();
        temp->node = node;
        temp->HorizontalDistance = HorizontalDistance;
        temp->next = nullptr;

        if (rear == nullptr) {
            front = rear = temp;
            return;
        }

        rear->next = temp;
        rear = temp;
    }

    void dequeue() {
        if (front == nullptr)
            return;

        QueueNode* temp = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        delete temp;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    Node* frontNode() {
        return front->node;
    }

    int frontHorizontalDistance() {
        return front->HorizontalDistance;
    }
};

void InsertToColumn(ListNode *& Head , int Data){
    ListNode * NewNode = (ListNode *)malloc(sizeof(ListNode));
    NewNode->Data = Data;
    NewNode->next = NULL;
    if(Head == NULL){
        Head = NewNode;
    }else{
        ListNode* Temp = Head;
        while (Temp->next != NULL)
        {
            Temp = Temp->next;
        }
        Temp->next = NewNode;
        
    }
}

void PrintColumn(ListNode * Head, FILE * Output){
    ListNode * Temp = Head;
    while (Temp != NULL)
    {
        
        fprintf(Output , " %d ", Temp->Data);
        Temp = Temp->next;
    }
    
}

// Function to insert a node in the BST
Node *InsertNode(Node *root, int data)
{
    if (root == NULL)
    {
        return new Node(data);
    }
    if (data < root->data)
    {
        Node *LeftChild = InsertNode(root->left, data);
        root->left = LeftChild;
        LeftChild->parent = root;
    }
    else
    {
        Node *RightChild = InsertNode(root->right, data);
        root->right = RightChild;
        RightChild->parent = root;
    }
    return root;
}

// Function to find the minimum value node in the tree
Node *findMin(Node *root)
{
    while (root && root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the BST
Node *DeleteNode(Node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->data)
    {
        root->left = DeleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = DeleteNode(root->right, key);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            if (temp != NULL)
                temp->parent = root->parent;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            if (temp != NULL)
                temp->parent = root->parent;
            delete root;
            return temp;
        }

        Node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = DeleteNode(root->right, temp->data);
    }
    return root;
}

void InOrder(Node *Temp, FILE *file)
{
    if (Temp == NULL)
        return;

    InOrder(Temp->left, file);
    fprintf(file, " %d ", Temp->data);
    InOrder(Temp->right, file);
}

void PreOrder(Node *Temp, FILE *file)
{
    if (Temp == NULL)
        return;

    fprintf(file, " %d ", Temp->data);
    PreOrder(Temp->left, file);

    PreOrder(Temp->right, file);
}

void PostOrder(Node *Temp, FILE *file)
{
    if (Temp == NULL)
        return;

    PostOrder(Temp->left, file);

    PostOrder(Temp->right, file);
    fprintf(file, " %d ", Temp->data);
}


// Function to perform vertical order traversal
void VerticalOrder(Node* root, FILE * Output) {
    if (!root) return;

    Queue q;
    q.enqueue(root, 0);

    int minCol = INT_MAX, maxCol = INT_MIN;
    ListNode * columns[2000]; 

    for (int i = 0; i < 2000; ++i)
        columns[i] = NULL; 

    while (!q.isEmpty()) {
        Node* node = q.frontNode();
        int col = q.frontHorizontalDistance();
        q.dequeue();
        InsertToColumn(columns[col + 1000], node->data);
        
        if (col < minCol) minCol = col;
        if (col > maxCol) maxCol = col;

        if (node->left)
            q.enqueue(node->left, col - 1);
        if (node->right)
            q.enqueue(node->right, col + 1);
    }

    for (int i = minCol + 1000; i <= maxCol + 1000; ++i) {
        if (columns[i] != NULL){
            PrintColumn(columns[i], Output);
            fprintf(Output , "\n");
        }
            
    }
    fprintf(Output, "\n");
}

// Function to compute the right view
void RightView(Node* root, FILE * Output) {
    if (!root) return;

    Queue q;
    q.enqueue(root, 0);

    while (!q.isEmpty()) {
        int n = 0;
        for (QueueNode* temp = q.front; temp != nullptr; temp = temp->next) 
            n++;

        for (int i = 0; i < n; i++) {
            Node* curr = q.frontNode();
            q.dequeue();

            if (i == n - 1){
                fprintf(Output, "%d ", curr->data);
            }

            if (curr->left)
                q.enqueue(curr->left, 0);
            if (curr->right)
                q.enqueue(curr->right, 0);
        }
    }
    cout << endl;
}


// Function to compute the right view
void LeftView(Node* root, FILE * Output) {
    if (!root) return;

    Queue q;
    q.enqueue(root, 0);

    while (!q.isEmpty()) {
        int n = 0;
        for (QueueNode* temp = q.front; temp != nullptr; temp = temp->next)
            n++;

        for (int i = 0; i < n; i++) {
            Node* curr = q.frontNode();
            q.dequeue();

            if (i == 0){
                fprintf(Output, "%d ", curr->data);
            }

            if (curr->left)
                q.enqueue(curr->left, 0);
            if (curr->right)
                q.enqueue(curr->right, 0);
        }
    }
    fprintf(Output, "\n");
}

// Function to compute the top view
void TopView(Node* root, FILE * Output) {
    if (!root) return;

    Queue q;
    q.enqueue(root, 0);

    int topViewMap[2000];
    for (int i = 0; i < 2000; ++i)
        topViewMap[i] = -1; 

    while (!q.isEmpty()) {
        Node* node = q.frontNode();
        int col = q.frontHorizontalDistance();
        q.dequeue();

        if (topViewMap[col + 1000] == -1)
            topViewMap[col + 1000] = node->data;

        if (node->left)
            q.enqueue(node->left, col - 1);
        if (node->right)
            q.enqueue(node->right, col + 1);
    }

    for (int i = 0; i < 2000; ++i) {
        if (topViewMap[i] != -1){
            fprintf(Output, " %d ", topViewMap[i]);
        }
    }
    fprintf(Output, "\n");
}

// Function to compute the bottom view
void bottomView(Node* root, FILE * Output) {
    if (!root) return;

    Queue q;
    q.enqueue(root, 0);

    int bottomViewMap[2000];
    for (int i = 0; i < 2000; ++i)
        bottomViewMap[i] = -1; 

    while (!q.isEmpty()) {
        Node* node = q.frontNode();
        int col = q.frontHorizontalDistance();
        q.dequeue();

        bottomViewMap[col + 1000] = node->data;

        if (node->left)
            q.enqueue(node->left, col - 1);
        if (node->right)
            q.enqueue(node->right, col + 1);
    }

    for (int i = 0; i < 2000; ++i) {
        if (bottomViewMap[i] != -1){
            fprintf(Output, " %d ", bottomViewMap[i]);
        }
        
    }
    fprintf(Output , "\n");
}

// Function to compute the boundary view
void leftBoundary(Node* root, ListNode *& res) {
    if (!root) return;
    if (root->left || root->right)
        InsertToColumn(res,root->data);
    if (root->left)
        leftBoundary(root->left, res);
    else if (root->right)
        leftBoundary(root->right, res);
}

void rightBoundary(Node* root,  ListNode *& res) {
    if (!root) return;
    if (root->right)
        rightBoundary(root->right, res);
    else if (root->left)
        rightBoundary(root->left, res);
    if (root->left || root->right)
        InsertToColumn(res,root->data);
}

void leaves(Node* root,  ListNode *& res) {
    if (!root) return;
    if (!root->left && !root->right)
        InsertToColumn(res,root->data);
    leaves(root->left, res);
    leaves(root->right, res);
}

void boundaryView(Node* root, FILE * Output) {
    if (!root) return;

    ListNode* res = nullptr;
    InsertToColumn(res,root->data);

    leftBoundary(root->left, res);
    leaves(root->left, res);
    leaves(root->right, res);
    rightBoundary(root->right, res);

    PrintColumn(res, Output);
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

Node *SearchNode(Node *Temp, int Data)
{
    if (Temp == NULL)
    {
        return NULL;
    }
    else if (Data < Temp->data)
    {
        return SearchNode(Temp->left, Data);
    }
    else if (Data > Temp->data)
    {
        return SearchNode(Temp->right, Data);
    }
    else
    {
        return Temp;
    }
}


int main(int argc, char *argv[])
{

    Node *Temp;
    struct Node *root = NULL;
    int choice, data;
    if (argc < 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r"); // Open the input file provided as a command-line argument

    FILE *OutputFile = fopen("output.txt", "w");
    fclose(OutputFile);
    OutputFile = fopen("output.txt", "a");

    if (file == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }
    while (fscanf(file, "%d", &choice) != EOF)
    { // Read the choice from file
        switch (choice)
        {
        case 1:
            fscanf(file, "%d", &data); // Read data to insert
            root = InsertNode(root, data);
            break;
        case 2:
            fscanf(file, "%d", &data); // Read data to delete
            Temp =  DeleteNode(root, data);
            break;
        case 3:
            fscanf(file, "%d", &data); // Read data to search
            Temp = SearchNode(root, data);
            if (Temp)
            {
                fprintf(OutputFile, "Search ELement : %d \n", Temp->data);
               
            }

            break;
        case 4:
            fprintf(OutputFile, "Height of tree: %d \n ", Height(root));
            break;
        case 5:
            fprintf(OutputFile, "In-Order Traversal: ");
            InOrder(root, OutputFile);
            break;
        case 6:
            fprintf(OutputFile, "\nPre-Order Traversal: ");
            PreOrder(root, OutputFile);
            break;
        case 7:
            fprintf(OutputFile, "\nPost-Order Traversal: ");
            PostOrder(root, OutputFile);
            break;
        case 8:
            fprintf(OutputFile, "\nVertical-Order Traversal: \n");
            VerticalOrder(root, OutputFile);
            break;
        case 9:
            fprintf(OutputFile , "Right View : \n ");
            RightView(root , OutputFile);
            break;
        case 10:
            fprintf(OutputFile , "\nLeft View : \n ");
            LeftView(root , OutputFile);
            break;

        case 11:
            fprintf(OutputFile , "Boundary View : \n ");
            boundaryView(root , OutputFile);
            break;

        case 12:
            break;
      

        default:
            fprintf(OutputFile, "Invalid choice.\n");
            exit(0);
        }
    }
    fclose(OutputFile);
    fclose(file); // Close the file
    return 0;
}





