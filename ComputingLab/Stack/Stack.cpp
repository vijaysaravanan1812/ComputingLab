
#include<iostream>

using namespace std;

struct StackNode{
    int Data;
    StackNode *Next;
};

typedef struct StackNode Node;

Node* Top = NULL;

Node * Allocate(Node * Temp , int Data){
    Temp =  (Node *)malloc(sizeof(Node));
    Temp->Data = Data;
    Temp->Next = NULL;
    return Temp;
}

void Push(int Data){
    Node * NewNode = Allocate(NewNode , Data);

    if(Top== NULL){
        Top = NewNode;
    }else{
        NewNode->Next = Top;
        Top = NewNode;
    }
}

int Peek(){
    if(Top != NULL)
        return Top->Data;
    else 
        return -1;
}

int Pop(){
    if(Top == NULL){
        return -1;
    }else{
        if(Top->Next == NULL){
            Node * Temp = Top;
            free(Temp);
            Top= NULL;
        }else{
            Node * Temp = Top;
            Top = Top->Next;
            free(Temp);
        }
        return 1;
    }
    
}

int main(){
    Push(4);
    Push(8);
    Push(24);
    cout<<"Peek :"<<Peek()<<"\n";
    Pop(); // 24
    Pop();  // 8
    cout<<"Peek :"<<Peek()<<"\n";
    Push(43); 
    Push(1);  
    cout<<"Peek :"<<Peek()<<"\n";
    Pop(); // 1
    Pop();  // 43
    cout<<"Peek :"<<Peek()<<"\n";
    cout<<Pop()<<"\n";
    cout<<Pop()<<"\n";

    return 0;
}