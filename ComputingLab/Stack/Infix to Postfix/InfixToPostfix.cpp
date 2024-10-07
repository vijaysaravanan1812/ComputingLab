
#include<iostream>
#include <cstring>
#include"Utils.cpp"

using namespace std;

struct StackNode {
    char Data;
    StackNode * Next;
};

typedef struct StackNode Node;

Node * Top = NULL;

Node * Allocate(Node * Temp, char Data){
    Temp =  (Node *)malloc(sizeof(Node));
    Temp->Data = Data;
    Temp->Next = NULL;
    return Temp;
}


void Push(char Data){
    Node * NewNode = Allocate(NewNode , Data);
    if(Top == NULL){
        Top = NewNode;
    }else{
        NewNode->Next = Top;
        Top = NewNode;
    }
}

int Pop(){
    if(Top == NULL){
        return -1;
    }else{
        if(Top-> Next == NULL){
            Node * Temp = Top ;
            free(Temp);
            Top= NULL;
        }else{
            Node * Temp = Top;
            Top = Top ->Next;
            free(Temp);
        }
        return 1;
    }
}

char Peek(){
    if(Top != NULL ){
        return Top->Data;
    }else{
        return '0';
    }
}

void InfixToPostfix(char * Infix, char * Postfix){
    int j = 0;
    for(int i = 0 ; i < strlen(Infix) ; i++){
        if(IsOperand(Infix[i]))
            Postfix[j++] = Infix[i];
        else if(Infix[i] == '(')
            Push(Infix[i]);
        else if(Infix[i] == ')'){
            while(Top != NULL && Peek() != '('){
                Postfix[j++] = Peek();
                Pop();
            }
            Pop();
        }
        else if(IsOperator(Infix[i])){
            while(Top != NULL && GetPrecedence(Peek()) >= GetPrecedence(Infix[i])){
                Postfix[j++] = Peek();
                Pop();
            }
            Push(Infix[i]);
        }
    }

    while(Top != NULL){
        Postfix[j++] = Peek();
        Pop();
    }
    
    Postfix[j] = '\0';
}


int main() {
    char infix[] = "a+b*(c^d-e)^(f+g*h)-i";
    char postfix[100]; // To hold the postfix expression

    InfixToPostfix(infix, postfix);

    cout << "Infix Expression: " << infix << endl;
    cout << "Postfix Expression: " << postfix << endl;

    return 0;
}
