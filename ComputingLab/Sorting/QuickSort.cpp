
//Quick Sort 
#include<iostream>

using namespace std;

int Partition(int Array[], int Left , int Right){
    int Pivot = Array[Right];
    int Pindex  = Left;
    for(int i = Left; i <= Right - 1; i++){
        if(Array[i] <= Pivot){
            int Temp = Array[Pindex];
            Array[Pindex] = Array[i];
            Array[i] = Temp;
            Pindex++;
        }
    }
    int Temp  = Array[Pindex];
    Array[Pindex] = Array[Right];
    Array[Right] = Temp;

    return Pindex; 
}

void QuickSort(int Array[], int Left , int Right){
    if(Left < Right){
        int Pindex = Partition(Array , Left , Right);

        QuickSort(Array, Left, Pindex - 1);
        QuickSort(Array , Pindex + 1, Right);
    }

}


int main(){
    int Array[] = {13, 4, 25, 27, 13, -3, 2, -2, 2};
    int Size = sizeof(Array)/sizeof(Array[0]);

    QuickSort(Array , 0 , Size - 1);

    for(int i = 0 ; i < Size; i++){
        cout<<Array[i]<<" ";
    }
    cout<<"\n";

    return 0;
}