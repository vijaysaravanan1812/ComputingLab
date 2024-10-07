// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
using namespace std;
void foo() 
{
  // do stuff...
  cout<<"I am vijay\n";
}

void bar(int x, int y)
{
  // do stuff...
  cout<<"Hi "<<x<<" "<<y<<"\n";
}

int main() 
{
  std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (bar,0, 1);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}