#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>

struct OperationData {
    int x;
    int y;
    double result;
    std::string operation;
};

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

int delay = 3;


int Add(int x, int y) {
    std::this_thread::sleep_for(std::chrono::seconds(delay + 1)); // Simulate 3-second delay
    return x + y;
}

int Sub(int x, int y) {
    std::this_thread::sleep_for(std::chrono::seconds(delay + 2)); // Simulate 4-second delay
    return x - y;
}

int Mul(int x, int y) {
    std::this_thread::sleep_for(std::chrono::seconds(delay + 3)); // Simulate 5-second delay
    return x * y;
}

double Div(double x, double y) {
    std::this_thread::sleep_for(std::chrono::seconds(delay)); // Simulate 6-second delay
    if (y == 0) {
        throw std::runtime_error("Division by zero");
    }
    return x / y;
}

int Pow(int x, int y) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate 7-second delay
    return std::pow(x, y);
}

void Addition(OperationData& data) {
    data.result = Add(data.x, data.y);
}

void Subbract(OperationData& data) {
    data.result = Sub(data.x, data.y);
}

void Multiply(OperationData& data) {
    data.result = Mul(data.x, data.y);
}

void Divide(OperationData& data) {
    try {
        data.result = Div(data.x, data.y);
    } catch (const std::exception& e) {
        std::cerr << "Error in operation " << data.operation << ": " << e.what() << std::endl;
    }
}

void Power(OperationData& data) {
    data.result = Pow(data.x, data.y);
}

void Test500Operations(int num_operations, double* times) {
    OperationData operations[num_operations];

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 100);
    std::uniform_int_distribution<int> operation_distribution(0, 4);
    
    for (int i = 0; i < num_operations; ++i) {
        operations[i].x = distribution(generator);
        operations[i].y = (i % 10 == 0) ? 0 : distribution(generator);

        int operation_type = operation_distribution(generator);
        std::thread t;

        auto start = std::chrono::high_resolution_clock::now();

        switch (operation_type) {
            case 0:
                std::cout<<"Addition - "<<i + 1<<" \n";
                t = std::thread(Addition, std::ref(operations[i]));
                break;
            case 1:
                std::cout<<"Subraction - "<<i + 1<<" \n";
                t = std::thread(Subbract, std::ref(operations[i]));
                break;
            case 2:
                std::cout<<"Multiply - "<<i + 1<<" \n";
                t = std::thread(Multiply, std::ref(operations[i]));
                break;
            case 3:
                std::cout<<"Divide - "<<i + 1<<" \n";
                t = std::thread(Divide, std::ref(operations[i]));
                break;
            case 4:
                std::cout<<"Power - "<<i + 1<<" \n";
                t = std::thread(Power, std::ref(operations[i]));
                break;
        }
        
        t.join();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        times[i] = elapsed.count(); // Record the time taken
    }
}

void PickRandomSamples(const double* times, int num_operations, double* sample_times) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, num_operations - 1);

    for (int i = 0; i < 5; ++i) {
        int random_index = distribution(generator);
        sample_times[i] = times[random_index];
        std::cout << "Sample " << i + 1 << ": " << sample_times[i] << " seconds\n";
    }
}

void CalculateStats(const double* times, int NumberOfSamples, int TotalTime) {
  
    double SortedTimes[NumberOfSamples];
    std::copy(times, times + NumberOfSamples, SortedTimes);
    MergeSort(SortedTimes, 0, NumberOfSamples - 1);
    
    double sum = 0;
    for (int i = 0; i < NumberOfSamples; ++i) {
        sum += SortedTimes[i];
    }
    double average = sum / NumberOfSamples;

    // Calculate standard deviation
    double SquaredDifferentSum = 0;
    for (int i = 0; i < NumberOfSamples; ++i) {
        SquaredDifferentSum += (SortedTimes[i] - average) * (SortedTimes[i] - average);
    }
    double StandardDeviation = std::sqrt(SquaredDifferentSum / NumberOfSamples);

    double median = (NumberOfSamples % 2 == 0) ? (SortedTimes[NumberOfSamples / 2 - 1] + SortedTimes[NumberOfSamples / 2]) / 2 : SortedTimes[NumberOfSamples / 2];
    double Percentile95 = SortedTimes[(int)(0.95 * NumberOfSamples)];
    double MaxTime = SortedTimes[NumberOfSamples - 1];

    // Report results
    std::ofstream report("24CS60R40_A9_part2.txt");
    report << std::fixed << std::setprecision(4);
    report << "Average time: " << average << " seconds\n";
    report << "Standard Deviation: " << StandardDeviation << " seconds\n";
    report << "Median time: " << median << " seconds\n";
    report << "Max time: " << MaxTime << " seconds\n";
    report << "95th Percentail " << Percentile95 << " seconds\n";
    report << "Total time of 500 Operation " <<TotalTime<< " seconds\n";
    report.close();
}

int main() {
    const int num_operations = 500;
    double times[num_operations]; // Array to store times for operations
    double sample_times[5]; // Array to store random samples

    Test500Operations(num_operations, times);
    
    //Picking 5 samples from 500 operation
    //Here I am don't considering the 500 operations as one sample
    //500 Operation take huge time
    PickRandomSamples(times, num_operations, sample_times);
    int TotalTime = 0;
    for (int i = 0; i < num_operations; ++i) {
        TotalTime += times[i];
    }
    
    CalculateStats(sample_times, 10, TotalTime);

    return 0;
}
