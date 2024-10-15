#include <iostream>
#include <pthread.h>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string.h>


using namespace std;

void Merge(double Array[], int Left, int Right, int Middle){
    int n1 = Middle - Left + 1;
    int n2 = Right - Middle;
    double LeftArray[n1] , RightArray[n2];
    for(int i = 0 ; i < n1 ; i++){
        LeftArray[i] = Array[Left + i];
    }
    for(int i = 0 ; i < n2; i++){
        RightArray[i] = Array[Middle + 1 + i];
    }
    int i = 0 , j = 0 , k = Left;
    while(i != n1 && j != n2){
        if(LeftArray[i] < RightArray[j]){
            Array[k++] = LeftArray[i++];
        }else{
            Array[k++] = RightArray[j++];
        }
    }
    while (i != n1)
    {
        Array[k++] = LeftArray[i++];
    }
    while(j != n2){
        Array[k++] = RightArray[j++];
    }
    

}

void MergeSort(double Array[], int Left, int Right){
    int Middle = Left + (Right - Left)/2;
    if(Left < Right){
        MergeSort(Array, Left, Middle );
        MergeSort(Array, Middle + 1 , Right);

        Merge(Array ,Left , Right, Middle);
    } 
}

struct Data {
    int Operator1;
    int Operator2;
    double Result;
    char Operation[100];
};

int Add(int Op1, int Op2) {
    return Op1 + Op2;
}

int Sub(int Op1, int Op2) {
    return Op1 - Op2;
}

int Mul(int Op1, int Op2) {
    return Op1 * Op2;
}

double Div(double Op1, double Op2) {
    return Op1 / Op2;
}

int Pow(int Op1, int Op2) {
    return pow(Op1, Op2);
}

void* Addition(void* param) {
    Data* data = (Data*)param;
    data->Result = Add(data->Operator1, data->Operator2);
    return NULL;
}

void* Subtraction(void* param) {
    Data* data = (Data*)param;
    data->Result = Sub(data->Operator1, data->Operator2);
    return NULL;
}

void* Multiply(void* param) {
    Data* data = (Data*)param;
    data->Result = Mul(data->Operator1, data->Operator2);
    return NULL;
}

void* Division(void* param) {
    Data* data = (Data*)param;
    data->Result = Div(data->Operator1, data->Operator2);
    return NULL;
}

void* Power(void* param) {
    Data* data = (Data*)param;
    data->Result = Pow(data->Operator1, data->Operator2);
    return NULL;
}

void Test500Operations(double times[], int index) {
    srand(time(nullptr));

    const int num_operations = 500;
    pthread_t threads[num_operations];
    Data operations[num_operations];
     auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_operations; ++i) {
        operations[i].Operator1 = rand() % 100 + 1;
        operations[i].Operator2 = rand() % 100 + 1;

        int operation_type = rand() % 5;
        switch (operation_type) {
            case 0:
                pthread_create(&threads[i], nullptr, Addition, &operations[i]);
                strcpy(operations[i].Operation, "Addition");
                break;
            case 1:
                pthread_create(&threads[i], nullptr, Subtraction, &operations[i]);
                strcpy(operations[i].Operation, "Subtraction");
                break;
            case 2:
                pthread_create(&threads[i], nullptr, Multiply, &operations[i]);
                strcpy(operations[i].Operation, "Multiplication");
                break;
            case 3:
                pthread_create(&threads[i], nullptr, Division, &operations[i]);
                strcpy(operations[i].Operation, "Division");
                break;
            case 4:
                pthread_create(&threads[i], nullptr, Power, &operations[i]);
                strcpy(operations[i].Operation, "Power");
                break;
        }
    }

    for (int i = 0; i < num_operations; ++i) {
        pthread_join(threads[i], nullptr);
    }

   
   

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    times[index] = duration.count();
}

void CalculateStats(double times[], int size, FILE * Output) {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += times[i];
    }
    double Average = sum / size;

    double SumSquaredDifference = 0.0;
    for (int i = 0; i < size; ++i) {
        SumSquaredDifference += (times[i] - Average) * (times[i] - Average);
    }
    double StandardDeviation = sqrt(SumSquaredDifference / size);

    double SortedTimes[size];
    memcpy(SortedTimes, times, sizeof(SortedTimes));
    
   
    MergeSort(SortedTimes , 0 , size - 1);
    double Median = SortedTimes[size / 2];
    double MaxTime = SortedTimes[size - 1];
    
 
    double Percentile95 = SortedTimes[(int)(0.95 * size)];

   
    fprintf(Output, "Statistics for 500 operations:\n");
    fprintf(Output, "Average time: %f seconds\n",Average );
    fprintf(Output , "Standard Deviation: %f seconds\n", StandardDeviation);
    fprintf(Output, "Median: %f seconds\n", Median);
    fprintf(Output, "95th Percentile: %f seconds\n", Percentile95);
    fprintf(Output , "Max time: %f seconds\n", MaxTime);
    fprintf(Output , "Total 500 Operation time %f seconds\n", times[0]);
}

int main() {
    FILE * Output = fopen("24CS60R40_A9_part1.txt", "w");
    pthread_t Threads[5];
    Data Operations[5] = {
        {3, 4, 0, "Addition"},
        {4, 2, 0, "Subtraction"},
        {3, 4, 0, "Multiplication"},
        {4, 4, 0, "Division"},
        {3, 4, 0, "Power"}
    };

    pthread_create(&Threads[0], NULL, Addition, &Operations[0]);
    pthread_create(&Threads[1], NULL, Subtraction, &Operations[1]);
    pthread_create(&Threads[2], NULL, Multiply, &Operations[2]);
    pthread_create(&Threads[3], NULL, Division, &Operations[3]);
    pthread_create(&Threads[4], NULL, Power, &Operations[4]);

    for (int i = 0; i < 5; ++i) {
        pthread_join(Threads[i], nullptr);
    }

    // Display results
    for (int i = 0; i < 5; ++i) {
        std::cout << Operations[i].Operation << ": " 
                  << Operations[i].Operator1 << " " << Operations[i].Operator2 
                  << " = " << Operations[i].Result << std::endl;
    }

    
    const int test_runs = 5;
    double times[test_runs];
    
    //Picking 5 samples 
    //Here I am considering the 500 operations as one sample
    for (int i = 0; i < test_runs; ++i) {
        Test500Operations(times, i);
    }
    
    CalculateStats(times, test_runs, Output);
    fclose(Output);

    return 0;
}
