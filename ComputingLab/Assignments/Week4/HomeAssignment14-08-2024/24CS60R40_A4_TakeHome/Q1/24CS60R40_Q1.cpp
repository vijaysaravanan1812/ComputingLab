

// gcc -o output base_code.c
// ./output "input.txt"

#include <bits/stdc++.h>

using namespace std;

// Node structure
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

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
    }
    else
    {
        QNode->Next = Start;
        Start = QNode;
    }
}

void Pop()
{
    if (Start == NULL && Last == NULL)
    {
        return;
    }
    else
    {
        if (Start == Last)
        {
            Queue *Temp = Start;
            free(Temp);
            Start = Last = NULL;
        }
        else
        {
            Queue *Temp = Start;
            while (Temp->Next != Last)
            {
                Temp = Temp->Next;
            }
            free(Last);
            Last = Temp;
        }
    }
}

Node *Peek(){
    if(Start){
        return Start->Data;
    }
    return NULL;
}


// Create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *InOrderSuccessor(Node *Temp)
{
    Node *current = Temp;
    while (current && current->left != NULL)
        current = current->left;
    return current;
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

int Balance(int LeftTreeHeight , int RightTreeHeight){
    return LeftTreeHeight - RightTreeHeight;
}

Node *LL(Node *Y) {
    Node *X = Y->left;
    Node *Temp = X->right;

    // Rotation
    X->right = Y;
    Y->left = Temp;

    return X;
}

Node *RR(Node *Y) {
    Node *X = Y->right;
    Node *Temp = X->left;

    // Rotation
    X->left = Y;
    Y->right = Temp;

    return X;
}

Node *LR(Node *Y) {
    Y->left = RR(Y->left);
    return LL(Y);
}

Node *RL(Node *Y) {
    Y->right = LL(Y->right);
    return RR(Y);
}

Node *DeleteNode(Node *Temp, int Data) {
    if (Temp == NULL) {
        return NULL;
    } else if (Data < Temp->data) {
        Temp->left = DeleteNode(Temp->left, Data);
    } else if (Data > Temp->data) {
        Temp->right = DeleteNode(Temp->right, Data);
    } else {
        if (Temp->left == NULL || Temp->right == NULL) {
            Node *temp = Temp->left ? Temp->left : Temp->right;

            if (temp == NULL) { // No child case
                temp = Temp;
                Temp = NULL;
            } else { // One child case
                *Temp = *temp;
            }

            free(temp);
        } else {
            Node *temp = InOrderSuccessor(Temp->right);

            Temp->data = temp->data;

            Temp->right = DeleteNode(Temp->right, temp->data);
        }
    }

    if (Temp == NULL)
        return Temp;

    int LeftTreeHeight = Height(Temp->left);
    int RightTreeHeight = Height(Temp->right);

    if (Balance(LeftTreeHeight, RightTreeHeight) == 2) {
        if (Height(Temp->left->left) >= Height(Temp->left->right)) {
            Temp = LL(Temp);
        } else {
            Temp = LR(Temp);
        }
    } else if (Balance(LeftTreeHeight, RightTreeHeight) == -2) {
        if (Height(Temp->right->right) >= Height(Temp->right->left)) {
            Temp = RR(Temp);
        } else {
            Temp = RL(Temp);
        }
    }

    return Temp;
}

Node *InsertNode(Node *Temp, int Data) {
    if (Temp == NULL) {
        return createNode(Data);
    }

    if (Data < Temp->data) {
        Temp->left = InsertNode(Temp->left, Data);
    } else if (Data > Temp->data) {
        Temp->right = InsertNode(Temp->right, Data);
    }

    int LeftTreeHeight = Height(Temp->left);
    int RightTreeHeight = Height(Temp->right);

    if (Balance(LeftTreeHeight, RightTreeHeight) == 2) {
        if (Height(Temp->left->left) >= Height(Temp->left->right)) {
            Temp = LL(Temp);
        } else {
            Temp = LR(Temp);
        }
    } else if (Balance(LeftTreeHeight, RightTreeHeight) == -2) {
        if (Height(Temp->right->right) >= Height(Temp->right->left)) {
            Temp = RR(Temp);
        } else {
            Temp = RL(Temp);
        }
    }

    return Temp;
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
}

// Check if a tree is within the given range
bool IsWithinRange(Node* Temp, int Low, int High) {
    if (Temp == NULL)
        return true;

    if (Temp->data < Low || Temp->data > High)
        return false;

    return IsWithinRange(Temp->left, Low, High) && IsWithinRange(Temp->right, Low, High);
}

// Count the number of subtrees within the given range
int CountSubtreesWithinRange(Node* Temp, int Low, int High) {
    if (Temp == NULL)
        return 0;

    int count = 0;
    if (IsWithinRange(Temp, Low, High))
        count = 1;

    count += CountSubtreesWithinRange(Temp->left, Low, High);
    count += CountSubtreesWithinRange(Temp->right, Low, High);

    return count;
}

int main(int argc, char *argv[])
{

    Node *Temp = NULL;
    int LowerLimit , UpperLimit;
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
            
            
            if (Temp != NULL)
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
            fprintf( OutputFile , "Zig Zag Traversal\n");
            break;
        case 10:
            fscanf(file, "%d %d" , &LowerLimit , &UpperLimit);
             cout<< CountSubtreesWithinRange(root , LowerLimit , UpperLimit)<<"\n";
            fprintf(OutputFile , "Number of subtrees within range %d \n" , CountSubtreesWithinRange(root , LowerLimit , UpperLimit));


            break;

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

