

#include<iostream>

using namespace std;


void Merge(int Array[] , int Left, int Middle, int Right){
    int i , j , k;

    //Calculating temporary array sizes
    int n1 = Middle - Left + 1;
    int n2 = Right - Middle;
    int Temp1[n1];
    int Temp2[n2];
    for(int i = 0; i<n1; i++){
        Temp1[i] = Array[Left + i];
    }
    for(int j = 0; j < n2 ; j++){
        Temp2[j] = Array[Middle + 1 + j];
    }

    i = 0; j = 0;
    k = Left;
    while(i < n1 && j < n2){
        if(Temp1[i] <= Temp2[j]){
            Array[k] = Temp1[i];
            i++;
        }else{
            Array[k] = Temp2[j];
            j++;
        }
        k++;

    }

    while(i < n1){
        Array[k] = Temp1[i];
        i++;
        k++;
    }
    while(j < n2){
        Array[k] = Temp2[j];
        j++;
        k++;
    }
}

void MergeSort(int Array[], int Left, int Right){
    int Middle = Left + (Right - Left)/2;
    if(Left < Right){
        MergeSort(Array , Left, Middle );
        MergeSort(Array , Middle + 1 , Right);

        Merge(Array , Left , Middle, Right);
    }
}

int main(){
    int Array[] = {12, 3, -24, 34, -20, 11, 35, -2};
    int Size = sizeof(Array)/sizeof(Array[0]);

    MergeSort(Array , 0 , Size - 1);

    for(int i = 0 ; i < Size; i++){
        cout<<Array[i]<<" ";
    }
    cout<<"\n";

    return 0;
}