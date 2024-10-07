
#include<iostream>

using namespace std;

bool IsOperator(char C){
    return (C == '+' || C == '-' || C == '*' || C == '/' || C == '^');
}

bool IsOperand(char C){
    return ((C >= '0' && C <= '9') || (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z'));
}

int GetPrecedence(char Ch){
    switch(Ch){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}