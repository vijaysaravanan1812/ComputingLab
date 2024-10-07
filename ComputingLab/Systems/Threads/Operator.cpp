// example for thread::operator=
#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
using namespace std;
 
void pause_thread(int n) 
{
  std::this_thread::sleep_for (std::chrono::seconds(n));
  std::cout << "\npause of " << n << " seconds ended\n";
}

void Test(int Num){
    this_thread::sleep_for(std::chrono::seconds(Num));
    cout<<"\nTest of "<<Num<<"\n";
}

int main() 
{
  std::thread threads[10];                         // default-constructed threads

  std::cout << "Spawning 5 threads...\n";
  for (int i=0; i<5; ++i){
    threads[i] = std::thread(Test,i+1);   // move-assign threads
    threads[i + 5] = std::thread(pause_thread,i+1); 
  }
  std::cout << "Done spawning threads. Now waiting for them to join:\n";
  for (int i=0; i<5; ++i){
    threads[i].join();
    threads[i + 5].join();
  }
    

  std::cout << "All threads joined!\n";

  return 0;
}