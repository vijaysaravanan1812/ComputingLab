#include<iostream>
#include <cstring>
#include"Utils.cpp" // Assuming Utils.cpp contains IsOperand, IsOperator, and GetPrecedence

using namespace std;

struct StackNode1 {
    char Data;
    StackNode1 * Next;
};

typedef struct StackNode1 Node;

Node * Top = NULL;

Node * Allocate(Node * Temp, char Data){
    Temp =  new Node;
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
        Node * Temp = Top;
        Top = Top ->Next;
        delete Temp;
        return 1;
    }
}

char Peek(){
    if(Top != NULL ){
        return Top->Data;
    }else{
        return '\0';
    }
}

void InfixToPostfix(char * Infix, char * Postfix){
    int j = 0;
    for(int i = 0 ; i < strlen(Infix) ; i++){

        //Append the operand to postfix express
        if(IsOperand(Infix[i])){
            while (i < strlen(Infix) && IsOperand(Infix[i])) {
                Postfix[j++] = Infix[i++];
            }
            Postfix[j++] = ' ';
            i--; // To reprocess the current character in the next iteration
        }
        else if(Infix[i] == '(')
            Push(Infix[i]);
        else if(Infix[i] == ')'){
            while(Top != NULL && Peek() != '('){
                Postfix[j++] = Peek();
                Postfix[j++] = ' ';
                Pop();
            }
            Pop(); // Pop the '('
        }
        else if(IsOperator(Infix[i])){
            while(Top != NULL && GetPrecedence(Peek()) >= GetPrecedence(Infix[i])){
                Postfix[j++] = Peek();
                Postfix[j++] = ' ';
                Pop();
            }
            Push(Infix[i]);
        }
    }

    while(Top != NULL){
        Postfix[j++] = Peek();
        Postfix[j++] = ' ';
        Pop();
    }

    if (j > 0 && Postfix[j - 1] == ' ') {
        j--; // Remove trailing space if any
    }
    
    Postfix[j] = '\0';
}

// int main() {
//    const int MAX_LEN = 100;
//     char infix1[] = "94+254";
//     char postfix1[MAX_LEN];

//     InfixToPostfix(infix1, postfix1);
//     cout << "Infix Expression: " << infix1 << endl;
//     cout << "Postfix Expression: " << postfix1 << endl;

//     char infix2[] = "(2234+335)-23";
//     char postfix2[MAX_LEN];

//     InfixToPostfix(infix2, postfix2);
//     cout << "Infix Expression: " << infix2 << endl;
//     cout << "Postfix Expression: " << postfix2 << endl;

//     char infix3[] = "AA+BA-OP";
//     char postfix3[MAX_LEN];

//     InfixToPostfix(infix3, postfix3);
//     cout << "Infix Expression: " << infix3 << endl;
//     cout << "Postfix Expression: " << postfix3 << endl;

//     return 0;
// }
