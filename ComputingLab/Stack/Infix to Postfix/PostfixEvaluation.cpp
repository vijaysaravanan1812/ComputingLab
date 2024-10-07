

#include<iostream>
#include<bits/stdc++.h>
#include"MultiChar.cpp"
#include <cstring>

using namespace std;

struct IntegerStack{ 
    int Data;
    IntegerStack * Next;
};

typedef struct IntegerStack StackNode;
StackNode * Top1 = NULL;

StackNode* Allocate1(StackNode*  Temp, int Data){
    Temp =  (StackNode *)malloc(sizeof(StackNode));
    Temp -> Data = Data;
    Temp -> Next = NULL;
    return Temp;
}

void Push1(int Data){
    StackNode * Temp = Allocate1(Temp , Data);
    if(Top1 == NULL){
        Top1 = Temp;
    }else{
        Temp->Next = Top1;
        Top1 = Temp;
    }
}

void Pop1(){
    if(Top1 == NULL)
        return;
    else{
        if(Top1->Next == NULL){
            free(Top1);
            Top1 = NULL;
        }else{
            StackNode * Temp = Top1;
            Top1 = Top1->Next;
            free(Temp);

        }
    }
}

int Peek1(){
    if(Top1 == NULL){
        return INT_MAX;
    }else{
        return Top1->Data;
    }
}

int PerformOperation(char Operation, int Operand1 , int Operand2){
        if (Operation == '+')
            return Operand1 + Operand2;
        else if (Operation == '-')
            return Operand1 - Operand2;
        else if (Operation == '*')
            return Operand1 * Operand2;
        else if (Operation == '/')
        {
            if(Operand2 != 0){
                return Operand1 / Operand2;
            }else{
                return 0;
            }
        }
        else if(Operation == '^')
        {
            int Product = 1;
            for(int i = 1 ; i <= Operand2; i++){
                Product = Product * Operand1;
            }
            return Product;
        }else{
            return INT_MAX;
        }
}

int EvaluatePostfix(char *Postfix){
    
    for(int i = 0 ; i < strlen(Postfix); i++){
        if(Postfix[i] == ' '){
            continue;
        }
        else if(IsOperand(Postfix[i])){
            char Operand[20];
            int j = 0;
            while(i < strlen(Postfix) && IsOperand(Postfix[i])){
                Operand[j++] = Postfix[i++]; 
            }
            i--;
            Operand[j] = '\0';
            int IntegerOperand = atoi(Operand);
            Push1(IntegerOperand);
        }
        else if(IsOperator(Postfix[i])){
            int Operand2 = Peek1();
            Pop1();
            int Operand1 = Peek1();
            Pop1();
            int res = PerformOperation(Postfix[i] , Operand1, Operand2);
            Push1(res);

        }
    }
    if(Top1 != NULL)
        return Peek1();
    else    
        return -1;
}

int main(){

    const int MAX_LEN = 100;
    char infix1[] = "94+254";
    char postfix1[MAX_LEN];

    InfixToPostfix(infix1, postfix1);
    cout << "Infix Expression: " << infix1 << endl;
    cout << "Postfix Expression: " << postfix1 << endl;
    int res = EvaluatePostfix(postfix1);
    cout << "Postfix Expression: " << postfix1 << endl;
    cout << "Postfix Expression Result: " << res << endl;
    cout<<"---------------\n";

    char infix2[] = "(2234+335)-23";
    char postfix2[MAX_LEN];

    InfixToPostfix(infix2, postfix2);
    cout << "Infix Expression: " << infix2 << endl;
    cout << "Postfix Expression: " << postfix2 << endl;
     res = EvaluatePostfix(postfix2);
    cout << "Postfix Expression: " << postfix2 << endl;
    cout << "Postfix Expression Result: " << res << endl;

    cout<<"---------------\n";
    char infix3[] = "AA+BA-OP";
    char postfix3[MAX_LEN];

    InfixToPostfix(infix3, postfix3);
    cout << "Infix Expression: " << infix3 << endl;
    cout << "Postfix Expression: " << postfix3 << endl;
    res = EvaluatePostfix(postfix3);
    cout << "Postfix Expression: " << postfix3 << endl;
    cout << "Postfix Expression Result: " << res << endl;

    return 0;
}