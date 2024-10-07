

#include<iostream>

using namespace std;

struct Queue {
    int Data;
    Queue * Next;
};

typedef struct Queue Queue;
Queue * Rear = NULL;
Queue * Front = NULL;

Queue * Allocate(Queue *Node , int Data){
    Node =  (Queue *)malloc(sizeof(Queue));
    Node->Data = Data;
    Node->Next = NULL;
    return Node;
}

void Enqueue(int Data){
    Queue * Node = Allocate(Node , Data);
    if(Rear == NULL && Front == NULL ){  
        Front = Rear = Node;
        Front->Next = Rear;
        Rear->Next = Front;
    }else{
        if(Front == Rear) {
            Front->Next = Node;
            Rear = Node;
            Rear->Next = Front;
        }else{
            Queue * Temp = Front;
            while(Temp->Next != Front){
                Temp = Temp->Next;
            }
            Node->Next = Front;
            Temp->Next = Node;
            Rear = Temp;
        }
    }
}

void Dequeue(){
    if(Front == NULL && Rear == NULL){
        cout<<"Queue Have Not Created\n";
    }else{
        if(Front == Rear){
            Queue * Temp = Front;
            free(Temp);
            Front = Rear = NULL;
        }else{
            Queue * Temp  = Front;
            while(Temp ->Next != Front){
                Temp = Temp->Next;
            }
            Temp->Next = Front ->Next;
            Rear = Temp;
            Temp = Front;
            Front = Front->Next;
            free(Temp);
        }
    }
}

void Print(){
    if(Rear == NULL &&  Front == NULL)
        cout<<"There is No Queue\n";
    else{
        if(Rear == Front){
            cout<<Rear->Data<<" \n";
        }else{
            Queue * Temp = Front;
            while(Temp->Next != Front){
                cout<<Temp->Data<<" ";
                Temp = Temp->Next;
            }
            cout<<Temp->Data<<" \n";
        }
    }

}

int Peek(){
    if(Front == NULL)
        return -13494393;
    return Front->Data;
}

int Size(){
    if(Front == NULL && Rear == NULL)
        return -1;
    else{
        if(Front == Rear)
            return 1;
        else{
            Queue * Temp = Front;
            int size = 1;
            while(Temp->Next != Front){
                Temp = Temp->Next;
                size++;
            }
                return size;
        }
    }

}


int main(){

    int Choice = 0;
    cout<<"--------------\n";
    cout<<"Enter Your Choice\n";
    cout<<" Queue Menu :\n1. Enqueue\nDequeue\n3. Peek\n4. Size\n5. Print\n6. Exit\n";

    cout<<"\n--------------\n";
    while(Choice != 6){
          int Value = 0;
        
        cin>>Choice;
        switch(Choice){
        case 1 : 
          
            cout<<"Enter the Value\n";
            cin>>Value; cout<<"Inserted Value"<< Value<<"\n";
            Enqueue(Value);
            break;
        case 2 : 
        
            cout<<"Enter the Value\n";
            cin>>Value; cout<<"Inserted Value"<< Value<<"\n";
            Dequeue();
            break;
        case 3:

            cout<<"Enter the Value\n";
            cin>>Value; cout<<"Inserted Value"<< Value<<"\n";
            cout<<"Peek :" <<Peek()<<"\n";
            break;
          case 4:
            
            cout<<"Enter the Value\n";
            cin>>Value; cout<<"Inserted Value"<< Value<<"\n";
            cout<<"Size :" <<Size()<<"\n";
            break;
          case 5:
        
            cout<<"Enter the Value\n";
            cin>>Value;cout<<"Inserted Value"<< Value<<"\n";
            cout<<"Queue : \n";
            Print();

            break;
        case 6:
        
            cout<<"Enter the Value\n";
            cin>>Value; cout<<"Inserted Value"<< Value<<"\n";
            Choice = 6;
            break;

        }

    }
    
    

    return 0;

}

