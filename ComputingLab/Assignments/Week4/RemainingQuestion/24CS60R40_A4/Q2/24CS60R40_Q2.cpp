

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


Node * LL(Node * Y){
    Node *X = Y->left;
    Node *Temp = Y->right;

    //Rotation
    X->right = Y;
    Y->left = Temp;

    
 
    return X;
}

Node *RR(Node * Y){

        Node *X = Y->right;
    Node *Temp = Y->left;

    //Rotation
    X->left = Y;
    Y->right = Temp;

    return X;
}


Node * LR(Node * Y){
    Node * X = Y->left;
    Y->left = X->right;
    Node * Temp  = Y->left->left;
  
    X->right = Temp;
    Y->left->left = X;
    Y = LL(Y);
    return Y;
}

Node *RL(Node *Y){
    Node * X = Y->right;
    Y->right = X->left;
    Node * Temp  = Y->right->right;
   
    X->left = Temp;
    Y->right->right = X;
    Y = LL(Y);
    return Y;
}

Node * DeleteNode(Node *Temp, int Data)
{
    if (Temp == NULL)
    {
        return NULL;
    }
    else if (Data < Temp->data)
    {
        Temp->left = DeleteNode(Temp->left, Data);
             
        int LeftTreeHeight = Height(Temp->left);
        int RightTreeHeight = Height(Temp->right);
        
        if(Balance(LeftTreeHeight , RightTreeHeight) == 2){
            if(Height(Temp->left->left) > Height(Temp->left->right)){
                Temp = LL(Temp);
            }else if(Height(Temp->left->right) > Height(Temp->left->left)){
                Temp = LR(Temp);
            }
        }
        return Temp;
    }
    else if (Data > Temp->data)
    {
        Temp->right = DeleteNode(Temp->right, Data);
        int LeftTreeHeight = Height(Temp->left);
        int RightTreeHeight = Height(Temp->right);
        if(Balance(LeftTreeHeight , RightTreeHeight) == -2){
            if(Height(Temp->right->right) > Height(Temp->right->left)){
                Temp = RR(Temp);
            }else if(Height(Temp->right->left) > Height(Temp->right->right)){
                Temp = RL(Temp);
            }
        }
        return Temp;
    }
    else
    {
        if (Temp->left && Temp->right)
        {
            Node *Tmp = InOrderSuccessor(Temp->right);
            Temp->data = Tmp->data;
            free(Tmp);
        }
        else if (Temp->left && Temp->right == NULL)
        {
            Temp->data = Temp->left->data;
            Node *tmp = Temp->left;
            Temp->left = NULL;
            free(tmp);
        }
        else if (Temp->left == NULL && Temp->right)
        {
            // cout << "Old :" << Temp->data << "\n";
            // cout << "New :" << Temp->right->data << "\n";
            Temp->data = Temp->right->data;
            Node *tmp = Temp->right;
            Temp->right = NULL;
            free(tmp);
        }
        else
        {
            free(Temp);
            Temp = NULL;
        }
        return Temp;
    }
}



Node *InsertNode(Node *Temp, int Data)
{
    if (Temp == NULL)
    {
        Node *NewNode = createNode(Data);
        Temp = NewNode;
    }
    else if (Data < Temp->data)
    {
        Temp->left = InsertNode(Temp->left, Data);
       
        int LeftTreeHeight = Height(Temp->left);
        int RightTreeHeight = Height(Temp->right);
        if(Balance(LeftTreeHeight , RightTreeHeight) == 2){
            if(Height(Temp->left->left) > Height(Temp->left->right)){
                Temp = LL(Temp);
            }else if(Height(Temp->left->right) > Height(Temp->left->left)){
                Temp = LR(Temp);
            }
        }
    }
    else if (Data > Temp->data)
    {
        Temp->right = InsertNode(Temp->right, Data);
        int LeftTreeHeight = Height(Temp->left);
        int RightTreeHeight = Height(Temp->right);
        if(Balance(LeftTreeHeight , RightTreeHeight) == -2){
            if(Height(Temp->right->right) > Height(Temp->right->left)){
                Temp = RR(Temp);
            }else if(Height(Temp->right->left) > Height(Temp->right->right)){
                Temp = RL(Temp);
            }
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

bool CheckTree(Node* Temp) {
    if (!Temp) return true;
    if (!Temp->left && !Temp->right) return true;

    int sum = 0;
    if (Temp->left) sum += Temp->left->data;
    if (Temp->right) sum += Temp->right->data;

    if (Temp->data * 2 != sum) return false;

    return CheckTree(Temp->left) && CheckTree(Temp->right);
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
                // cout<<"Search ELement :"<<Temp->data<<"\n";
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
            fprintf(OutputFile ,"Checking node’s value is exactly half of the sum of its child nodes %d" , CheckTree(root));
            break;
        case 10:
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

