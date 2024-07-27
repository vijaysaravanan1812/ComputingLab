
#include<iostream>

using namespace std;

void InsertionSort(int Array[], int Size){
    for(int i = 1 ; i < Size; i++){
        int Hole = i;
        int Value = Array[i];
        while(Hole > 0 && Array[Hole - 1]  > Value){
            Array[Hole] = Array[Hole - 1];
            Hole = Hole - 1; 
        }
        Array[Hole] = Value;
    }

}

int main(){
    int Array[] = {12, 35, 24, 11, 47, 26, 38};

    int Size = sizeof(Array)/sizeof(Array[0]);
    InsertionSort(Array, Size);
    for(int i = 0 ; i < Size; i++){
        cout<<Array[i]<<" ";
    }
    cout<<"\n";

}