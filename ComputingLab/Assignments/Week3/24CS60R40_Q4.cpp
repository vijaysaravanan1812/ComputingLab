

#include<iostream>

using namespace std;

long long MOD = 1000000007;

struct Node{
    int data; 
    struct Node* next;
};

typedef struct Node Node;


void insertAtBeginning(struct Node** head, int data)
{
    // create a new Node using dynamic memory allocation
    struct Node* newNode
        = (struct Node*)malloc(sizeof(struct Node));
    // store the data in the new Node
    newNode->data = data;
    // the next pointer of new Node will be on current head
    newNode->next = *head;
    // the current head will the new Node
    *head = newNode;
}

// Function to Insert the Node in the end
void insertAtEnd(struct Node** head, int data)
{
    struct Node* newNode
        = (struct Node*)malloc(sizeof(struct Node));
    // store the data in the new Node
    newNode->data = data;
    // Since the node will be last its next will be NULL
    newNode->next = NULL;
    // in case this is the first node make the newNode as
    // the head of the LinkedList
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    // Create a pointer to iterate till the last node
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    // make the next of the tail to the new Node
    current->next = newNode;
}
 
// Function to Print the Linked List
void printList(struct Node* head)
{
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}


long long GetNum(Node* Head) {
    long long Number = 0;

    Node* Current = Head;
    while (Current != nullptr) {
        Number = Number * 10 + Current->data;
        Current = Current->next;
    }

    return Number;
}


long long Multiply(Node* L1, Node* L2) {

    long long Num1 = GetNum(L1);
    long long Num2 = GetNum(L2);
    
    long long Result = (Num1 % MOD * Num2 % MOD) % MOD;

    return Result;
}



int main()
{
    // Create the Linked List by taking user input
    Node* head1 = NULL;
    Node* head2 = NULL;
    int n;
    // pass head by reference so that it can be modified
    printf("Enter the size of linked list 1\n");
    scanf("%d",&n);
    printf("Enter the numbers in linked list 1\n");
    for(int i=0;i<n;i++){
        int x;
        printf("Enter element %d: \n",i+1);
        scanf("%d",&x);
        if(head1==NULL)insertAtBeginning(&head1,x);
        else insertAtEnd(&head1,x);
    }
    
 
  

    // pass head by reference so that it can be modified
    printf("Enter the size of linked list 2\n");
    scanf("%d",&n);
    printf("Enter the numbers in linked list 2\n");
    for(int i=0;i<n;i++){
        int x;
        printf("Enter element %d: \n",i+1);
        scanf("%d",&x);
        if(head2==NULL)insertAtBeginning(&head2,x);
        else insertAtEnd(&head2,x);
    }
      // Print the Linked List
    printf("Linked List: 1 ");
    printList(head1);
 
    // Print the Linked List
    printf("Linked List: 2 ");
    printList(head2);

    cout<<"Modulo Operation :"<<Multiply(head1 , head2)<<"\n";


 
    return 0;
}
