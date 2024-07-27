#include <iostream>
#include <cstdlib>  // For malloc and free

using namespace std;

struct QueueNode {
    int Data;
    QueueNode* Next;
};

typedef struct QueueNode Node;
Node* StartNode = NULL;
Node* LastNode = NULL;

Node* AllocateNode(int Data) {
    Node* Temp = (Node*)malloc(sizeof(Node));
    Temp->Data = Data;
    Temp->Next = NULL;
    return Temp;
}

void EnQueue(int Data) {
    Node* NewNode = AllocateNode(Data);
    if (LastNode == NULL) {
        StartNode = LastNode = NewNode;
    } else {
        LastNode->Next = NewNode;
        LastNode = NewNode;
    }
}

int DeQueue() {
    if (StartNode == NULL) {
        return 0;  // Queue is empty
    } else {
        Node* Temp = StartNode;
        StartNode = StartNode->Next;
        if (StartNode == NULL) {
            LastNode = NULL;
        }
        free(Temp);
        return 1;  // Successfully dequeued
    }
}

int Delete(int Data) {
    if (StartNode == NULL && LastNode == NULL) {
        return 0;  // Queue is empty
    } else {
        Node* Temp = StartNode;
        Node* PreviousNode = NULL;

        while (Temp != NULL && Temp->Data != Data) {
            PreviousNode = Temp;
            Temp = Temp->Next;
        }

        if (Temp == NULL) {
            return 0;  // Data not found
        }
        if (PreviousNode == NULL) {
            StartNode = Temp->Next;
            if (StartNode == NULL) {
                LastNode = NULL;
            }
        } else {
            PreviousNode->Next = Temp->Next;
            if (PreviousNode->Next == NULL) {
                LastNode = PreviousNode;
            }
        }
        free(Temp);
        return 1;  // Successfully deleted
    }
}

void Insert(int Position, int Data) {
    Node* NewNode = AllocateNode(Data);
    if (Position == 1) {
        NewNode->Next = StartNode;
        StartNode = NewNode;
        if (LastNode == NULL) {
            LastNode = NewNode;
        }
    } else {
        Node* Temp = StartNode;
        int i = 1;
        while (Temp != NULL && i < Position - 1) {
            Temp = Temp->Next;
            i++;
        }
        if (Temp == NULL) {
            // Position is greater than the length of the list, add to the end
            if (LastNode != NULL) {
                LastNode->Next = NewNode;
                LastNode = NewNode;
            } else {
                StartNode = LastNode = NewNode;
            }
        } else {
            NewNode->Next = Temp->Next;
            Temp->Next = NewNode;
            if (NewNode->Next == NULL) {
                LastNode = NewNode;
            }
        }
    }
}

void Display() {
    Node* Temp = StartNode;
    while (Temp != NULL) {
        cout << " " << Temp->Data << " ";
        Temp = Temp->Next;
    }
    cout << "\n";
}

int main() {
    EnQueue(1);
    Display();

    EnQueue(2);
    Display();

    DeQueue();  // Removes 1
    Display();

    DeQueue();  // Removes 2
    Display();

    EnQueue(5);
    Display();

    EnQueue(13);
    DeQueue();  // Removes 5
    Display();

    return 0;
}
