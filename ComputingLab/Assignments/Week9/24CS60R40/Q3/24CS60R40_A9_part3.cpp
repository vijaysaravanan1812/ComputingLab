#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <cstdlib> 
#include <ctime>    
#include <complex>

// JobNode structure to hold function pointers and their arguments
struct JobNode {
    void (*job)(int, int); 
    int arg1, arg2;         
    JobNode* next;

    JobNode(void (*j)(int, int), int a1, int a2) {
        job = j;
        arg1 = a1;
        arg2 = a2;
        next = nullptr;
    }
};

// JobQueue class for managing the queue of jobs
class JobQueue {
private:
    JobNode* head;
    JobNode* tail;
    std::mutex queueMutex; 

public:
    JobQueue() {
        head = nullptr;
        tail = nullptr;
    }

    // Enqueue a job with arguments (blocking with mutex)
    void enqueue(void (*job)(int, int), int arg1, int arg2) {
        std::lock_guard<std::mutex> lock(queueMutex); 
        JobNode* newNode = new JobNode(job, arg1, arg2); 
        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode; 
        }
        tail = newNode;
    }

    // Dequeue a job and return its function and arguments (blocking with mutex)
    bool dequeue(void (*&job)(int, int), int& arg1, int& arg2) {
        std::lock_guard<std::mutex> lock(queueMutex); 
        if (head == nullptr) return false;  

        job = head->job;  
        arg1 = head->arg1;  
        arg2 = head->arg2;
        JobNode* oldHead = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete oldHead;
        return true;
    }
};

// ThreadPool class to manage a pool of worker threads
class ThreadPool {
private:
    int maxThreads; 
    std::thread* workers;  
    JobQueue jobQueue;
    std::atomic<bool> running; 
    std::atomic<int> activeJobs;  

    // Worker function that runs in each thread
    void workerThread() {
        while (running) {
            void (*job)(int, int);  
            int arg1, arg2;
            if (jobQueue.dequeue(job, arg1, arg2)) {
                try {
                    job(arg1, arg2);
                } catch (const std::exception& e) {
                    std::cerr << "Exception in job: " << e.what() << "\n";
                }
                activeJobs--;
            } else {
                std::this_thread::yield();
            }
        }
    }

public:
    // Constructor to initialize pool with a fixed number of threads
    ThreadPool(int numThreads) {
        maxThreads = numThreads;
        running = true;
        activeJobs = 0;
        workers = new std::thread[maxThreads];  
        for (int i = 0; i < maxThreads; ++i) {
            workers[i] = std::thread(&ThreadPool::workerThread, this);
        }
    }

    // Destructor to clean up threads
    ~ThreadPool() {
        running = false; 
        for (int i = 0; i < maxThreads; ++i) {
            if (workers[i].joinable()) {
                workers[i].join();
            }
        }
        delete[] workers; 
    }

    // Submit a job to the pool
    void submit(void (*job)(int, int), int arg1, int arg2) {
        jobQueue.enqueue(job, arg1, arg2); 
        activeJobs++;
    }

    // Wait for all jobs to complete
    void waitForAllJobs() {
        while (activeJobs.load() > 0) {
            std::this_thread::yield();
        }
    }
};


void add(int a, int b) {
    int res = a + b;
    std::cout << "Addition result: " << res << "\n";
}

void subtract(int a, int b) {
    int res = a - b;
    std::cout << "Subtraction result: " << res << "\n";
}

void multiply(int a, int b) {
    int res = a * b;
    std::cout << "Multiplication result: " << res << "\n";
}

void divide(int a, int b) {
    if (b == 0) {
        std::cerr << "Division by zero error\n";
        return;
    }
    double res = static_cast<double>(a) / b;
    std::cout << "Division result: " << res << "\n";
}

void power(int a, int b) {
    if (b < 0) {
        std::cerr << "Negative exponent not supported\n";
        return;
    }
    int res = static_cast<int>(std::pow(a, b));
    std::cout << "Power result: " << res << "\n";
}

// Randomly selects one of the mathematical operations
void randomOperation(ThreadPool& pool) {
    void (*operations[])(int, int) = { add, subtract, multiply, divide, power };
    int numOperations = sizeof(operations) / sizeof(operations[0]);
    
   
    int index = rand() % numOperations;
    int arg1 = rand() % 100;  
    int arg2 = rand() % 10 + 1; 

   
    pool.submit(operations[index], arg1, arg2);
}

// Test function to demonstrate thread pool usage
void testThreadPool() {
    srand(static_cast<unsigned int>(time(0))); 

    ThreadPool pool(50); 

 
    for (int i = 0; i < 50; ++i) {
        randomOperation(pool);
    }

    
    pool.waitForAllJobs();
}

int main() {
    std::cout << "Starting thread pool test with 50 threads...\n";
     auto start = std::chrono::high_resolution_clock::now();
    try {
        testThreadPool();  
    } catch (const std::exception& e) {
        std::cerr << "Exception in main: " << e.what() << "\n";
    }
    auto End = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = End - start;

    double time = elapsed.count(); // Record the time taken
    std::cout << "Test completed in "<<time<< " Seconds .\n";
    return 0;
}
