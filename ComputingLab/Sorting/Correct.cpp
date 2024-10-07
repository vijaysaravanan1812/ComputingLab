
#include<iostream>

using namespace std;

int Run= 4;

void Merge(int Array[] , int Left , int Middle, int Right){

    int Size1 = Middle - Left + 1;
    int Size2 = Right - Middle;
    int Array1[Size1] , Array2[Size2];
    for(int i = 0; i < Size1; i++){
        Array1[i] = Array[Left + i];
    }
    for(int i = 0 ; i < Size2; i++){
        Array2[i] = Array[Middle + 1 + i];
    }

    int i = 0, j = 0 , k;
    k = Left;
    while(i < Size1 && j < Size2){
        if(Array1[i] <= Array2[j]){
            Array[k++] = Array1[i++];
        }else{
            Array[k++] = Array2[j++];
        }
    }

    while( i < Size1){
        Array[k++] = Array1[i++];
    }

    while(j < Size2){
        Array[k++] = Array2[j++];
    }
}

void InsertionSort(int Array[] , int Left , int Right){
    for(int i = Left + 1 ; i <= Right ; i++ ){
        int Value = Array[i];
        int Hole = i;
        while(Hole > Left && Array[Hole - 1] > Value){
            Array[Hole] = Array[Hole - 1];
            Hole = Hole - 1;
        }
        Array[Hole] = Value;
    }
}

void TimSort(int Array[], int Size){
    for(int i = 0 ; i < Size; i += Run)
        InsertionSort(Array, i , min((i + Run - 1) , (Size - 1)));


    for(int i = Run; i < Size; i = 2 * i){
        for(int Left = 0 ; Left < Size; Left += 2 * i){
            int Middle = Left + i - 1;
            int Right = min((Left + 2 * i - 1) , (Size - 1));
            if(Middle < Right){
                Merge(Array , Left , Middle , Right );
            }
        }
    }

    
}


int main() {
    int Array[] = {12, 35, 24, 11, 47, 26, 38, -3, 4, 6, -8, 0, 5, 3, 11, 56, 34, 2, 8, 25};
    int Size = sizeof(Array) / sizeof(Array[0]);

    TimSort(Array, Size);

    for (int i = 0; i < Size; i++) {
        cout << Array[i] << " ";
    }
    cout << endl;

    return 0;
}

