#include <iostream>
#include <cstdlib>

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

// Custom Queue implementation
struct Queue
{
    Node *Data;
    Queue *Next;
};

Queue *Last = NULL;
Queue *Start = NULL;



Queue *Allocate(Node *Data, Queue *QNode)
{
    QNode = (Queue *)malloc(sizeof(Queue));
    QNode->Data = Data;
    QNode->Next = NULL;
    return QNode;
}

void Push(Node *Data)
{
    Queue *QNode = Allocate(Data, QNode);
    if (Start == NULL)
    {
        Start = QNode;
        Last = QNode;
    }
    else
    {
        Last->Next = QNode;
        Last = QNode;
    }
}

void Pop()
{
    if (Start == NULL)
    {
        return;
    }
    Queue *Temp = Start;
    Start = Start->Next;
    if (Start == NULL)
    {
        Last = NULL;
    }
    free(Temp);
}

Node *Peek()
{
    if (Start)
    {
        return Start->Data;
    }
    return NULL;
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

void LevelOrder(Node * Temp, FILE * file){
    if(Temp){
        Push(Temp);
        while (Start != NULL) {
            Node * Tmp = Peek();
            fprintf(file , " %d", Tmp->data);
            Pop();
            if(Tmp->left)
                Push(Tmp->left);
            if(Tmp->right)
                Push(Tmp->right);
        }
    }
    Start = NULL;
    Last = NULL;
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

int minCameras = 0;

int dfs(Node *root)
{
    if (root == NULL)
        return 1;

    int left = dfs(root->left);
    int right = dfs(root->right);

    if (left == 0 || right == 0)
    {
        minCameras++;
        return 2;
    }

    if (left == 2 || right == 2)
    {
        return 1;
    }

    return 0;
}

int minCameraCover(Node *root)
{
    if (dfs(root) == 0)
    {
        minCameras++;
    }
    return minCameras;
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
            fprintf(OutputFile, "Pre-Order Traversal: ");
            PreOrder(root, OutputFile);
            break;
        case 7:
            fprintf(OutputFile, "Post-Order Traversal: ");
            PostOrder(root, OutputFile);
            break;
        case 8:
            fprintf(OutputFile, "Level-Order Traversal: ");
            LevelOrder(root, OutputFile);
            break;
        case 9:
            break;
        case 10:
            {
                fprintf(OutputFile , "Find Minimum Camera \n");
                fprintf(OutputFile , " %d" , minCameraCover(root));
            }
      

        default:
            fprintf(OutputFile, "Invalid choice.\n");
            // fclose(file);
            exit(0);
        }
    }
    fclose(OutputFile);
    fclose(file); // Close the file
    return 0;
}
