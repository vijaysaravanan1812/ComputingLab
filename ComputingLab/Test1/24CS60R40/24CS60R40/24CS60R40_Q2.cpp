

#include<iostream>

using namespace std;


void Merge(int Array[] , int Left , int Middle, int Right){
    
    
    int SizeOfTempArray1 = Middle - Left + 1;
    int SizeOfTempArray2 = Right - Middle;
    int TempArray1[SizeOfTempArray1], TempArray2[SizeOfTempArray2];
    int i = 0 , j = 0 , k = Left;

    while(i < SizeOfTempArray1 && j < SizeOfTempArray2){
        if(TempArray1[i] <= TempArray2[j]){
            Array[k] = TempArray1[i];
            i++;
            k++;
        }else{
            Array[k] = TempArray2[j];
            j++;
            k++;
        }
    }

    while(i < SizeOfTempArray1){
        Array[k] = TempArray1[i];
        i++;
        k++;
    }

    while(j < SizeOfTempArray2){
        Array[k] = TempArray2[j];
        j++;
        k++;
    }

}

void MergeSort(int Array[] , int Left , int Right){


    int Middle = Left + (Right - Left)/2;
    if(Left < Right){
        MergeSort(Array, Left, Middle  );
        MergeSort(Array , Middle + 1 , Right);

        Merge(Array, Left, Middle , Right);
    }
}


int main(){

    int Array[] = {5, 2, 1,6 ,4};
    int size = sizeof(Array)/sizeof(Array[0]);
    if(size < 5){
        cout<<"Not Able to pick up Number\n";
    }
    MergeSort(Array , 0 , size - 1);


    cout<<"Maximum Product\n";
    int Product = 1;
    for(int i = 0 ; i < 5; i++){
        Product = Product * Array[i];
    }cout<<"\n";
    cout<<"Product : "<<Product<<"\n";


  
    return 0;
}