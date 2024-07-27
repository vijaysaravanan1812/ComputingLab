
#include<iostream>

using namespace std;

struct LinkedListNode {
    int Data;
    LinkedListNode * Next;
};

typedef struct LinkedListNode Node;
Node * LastNode = NULL;
Node * StartNode = NULL;

Node *AllocateNode(Node* NewNode, int data){
    NewNode =   (Node *)malloc(sizeof(Node));
    NewNode->Data = data;
    NewNode->Next = NULL;
    return NewNode;
}

int Delete(int data){
    //Check if list is empty
    if(StartNode == NULL){
        return 0;
    }else{
        Node * temp = StartNode;
        Node * PreviousNode = NULL;
        while(temp != NULL && temp->Data != data){
            PreviousNode = temp;
            temp = temp->Next;
        }

        //Check if Number is present
         if(temp == NULL){
            return 0;
         }

        //Check number is matching with first node
        if(PreviousNode == NULL){

            //Check temp->next is NULL
            StartNode = temp->Next;
            if(StartNode == NULL ){
                StartNode = LastNode = NULL;
            }
            free(temp);
            return 1;
        }else{
            PreviousNode->Next = temp->Next;
            if(temp->Next == NULL){
                LastNode = PreviousNode;
            }
            free(temp);
            return 1;
        }

    }
}

Node* Insert(int pos, int data){
    
    Node* NewNode = AllocateNode(NewNode, data);

    //Check if list is empty
    if(StartNode == NULL && LastNode == NULL){
        StartNode = LastNode = NewNode;
    }else{
        //Check if position of insertion is first
        if(pos ==1){
            NewNode->Next = StartNode;
            StartNode = NewNode;
        }else{
            int i = 1;
            Node *temp = StartNode;
            while(temp != NULL && i < pos - 1){
                temp = temp->Next;
                i++;
            }
        
            //Check if need to insert node at last
            if(temp == NULL){
                LastNode->Next = NewNode;
                LastNode = NewNode; 
            }else{
                //Insert Node in Middle 
                NewNode->Next = temp->Next;
                temp->Next  = NewNode;
                //Check if NewNode is Last Node and if update LastNode
                if(NewNode->Next == NULL){
                    LastNode = NewNode;
                }
            }
        }

    }

    return StartNode;

}

void Display(){
    Node *temp = StartNode;
    while(temp != NULL){
        cout<<" "<<temp->Data<<" ";
        temp = temp->Next;
    }
    cout<<"\n";

}

int main(){

    Insert(1, 10);
    Display();
    Insert(2, 23);
    Display();
    Insert(6, 37);
    Display();
    Insert(1, 82);
    Insert(2, 13);
    Display();
    Delete(12);
    Display();
    Delete(13);
    Delete(82);
    Display();

    return 1;
}

