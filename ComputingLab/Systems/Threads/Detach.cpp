#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <mutex>          // std::mutex
using namespace std;
mutex file_mutex;  // Mutex to synchronize file writes

void pause_thread(int n, FILE * Output) 
{
    this_thread::sleep_for(chrono::seconds(n));
    
    // Lock the mutex before writing to the file to avoid data race
    lock_guard<mutex> lock(file_mutex);
    fprintf(Output, "Pause of %d seconds ended\n", n);
    
    // Output to console
    cout << " " << n << " seconds ended\n";
}

int main() 
{
    FILE * Output = fopen("output.txt", "w");
  

    if (Output == nullptr) {
        cerr << "Error opening file!" << std::endl;
        return 1;
    }

    cout << "Spawning and detaching 3 threads...\n";
    thread(pause_thread, 3, Output).detach();
    thread(pause_thread, 4, Output).detach();
    thread(pause_thread, 5, Output).detach();
    cout << "Done spawning threads.\n";
    
    cout << "(the main thread will now pause for 6 seconds)\n";
    
    // Let the main thread sleep for 6 seconds, allowing time for detached threads to finish
    this_thread::sleep_for(chrono::seconds(6));

    fclose(Output);  // Ensure the file is closed after all threads are done
    cout << "File closed and program finished.\n";
    
    return 0;
}
