#include <iostream>

struct PriorityQueue {
    int* heap;
    int capacity;
    int size;

    PriorityQueue(int cap) {
        capacity = cap;
        heap = new int[capacity];
        size = 0;
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                int temp = heap[index];
                heap[index] = heap[parent];
                heap[parent] = temp;
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < size && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }

        if (rightChild < size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        if (largest != index) {
            int temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;
            heapifyDown(largest);
        }
    }

    void push(int value) {
        if (size == capacity) {
            std::cout << "Priority Queue is full!\n";
            return;
        }
        heap[size] = value;
        heapifyUp(size);
        size++;
    }

    void pop() {
        if (size == 0) {
            std::cout << "Priority Queue is empty!\n";
            return;
        }
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
    }

    int top() {
        if (size > 0) {
            return heap[0];
        } else {
            std::cerr << "Priority Queue is empty!\n";
            return -1;
        }
    }

    bool empty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }
};

int main() {
    PriorityQueue pq(10);  // Initialize with a capacity of 10

    pq.push(10);
    pq.push(20);
    pq.push(5);
    pq.push(30);

    std::cout << "Top element: " << pq.top() << std::endl; // Should output 30

    pq.pop();
    std::cout << "Top element after pop: " << pq.top() << std::endl; // Should output 20

    pq.pop();
    std::cout << "Top element after another pop: " << pq.top() << std::endl; // Should output 10

    return 0;
}
