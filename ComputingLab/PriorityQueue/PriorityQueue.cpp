#include <iostream>
using namespace std;

class PriorityQueue {
private:
    int *heap; 
    int capacity; 
    int size;

   
    int parent(int i) { return (i - 1) / 2; }

  
    int leftChild(int i) { return (2 * i) + 1; }


    int rightChild(int i) { return (2 * i) + 2; }

    void heapifyDown(int i) {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);

    
        if (left < size && heap[left] > heap[largest])
            largest = left;


        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }


    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    
    PriorityQueue(int cap) {
        capacity = cap;
        size = 0;
        heap = new int[capacity];
    }


    ~PriorityQueue() {
        delete[] heap;
    }

  
    void push(int value) {
        if (size == capacity) {
            cout << "Priority Queue is full\n";
            return;
        }
     
        heap[size] = value;
        size++;
        heapifyUp(size - 1);
    }

  
    int pop() {
        if (size <= 0) {
            cout << "Priority Queue is empty\n";
            return -1;
        }
        if (size == 1) {
            size--;
            return heap[0];
        }
        
      
        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        
      
        heapifyDown(0);
        return root;
    }

 
    int top() {
        if (size <= 0) {
            cout << "Priority Queue is empty\n";
            return -1;
        }
        return heap[0];
    }

 
    bool isEmpty() {
        return size == 0;
    }
    
   
    int getSize() {
        return size;
    }
};

int main() {
    PriorityQueue pq(10);

    pq.push(15);
    pq.push(10);
    pq.push(30);
    pq.push(5);
    
    cout << "Top element is " << pq.top() << endl; // Should output 30
    
    cout << "Popped element is " << pq.pop() << endl; // Should output 30
    cout << "Top element is " << pq.top() << endl; // Should output 15
    
    pq.push(20);
    cout << "Top element is " << pq.top() << endl; // Should output 20
    
    while (!pq.isEmpty()) {
        cout << "Popped element is " << pq.pop() << endl;
    }
    
    return 0;
}
