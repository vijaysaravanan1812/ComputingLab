
#include<stdio.h>
struct Node{
    int data;
    
    struct Node* next;
};

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

int main()
{
    // Create the Linked List by taking user input
    struct Node* head = NULL;
    int n;
    // pass head by reference so that it can be modified
    printf("Enter the size of linked list\n");
    scanf("%d",&n);
    printf("Enter the numbers in linked list\n");
    for(int i=0;i<n;i++){
        int x;
        printf("Enter element %d: \n",i+1);
        scanf("%d",&x);
        if(head==NULL)insertAtBeginning(&head,x);
        else insertAtEnd(&head,x);
    }
    
 
    // Print the Linked List
    printf("Linked List: ");
    printList(head);
 
    return 0;
}