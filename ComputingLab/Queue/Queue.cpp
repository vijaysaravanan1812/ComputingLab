
struct QueueNode {
    int Data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;

    Queue(){
        this->front = nullptr;
        this->rear = nullptr;
    }

    void enqueue(int Data) {
        QueueNode* temp = new QueueNode();
        temp->Data = Data;
        temp->next = nullptr;

        if (rear == nullptr) {
            front = rear = temp;
            return;
        }

        rear->next = temp;
        rear = temp;
    }

    void dequeue() {
        if (front == nullptr)
            return;

        QueueNode* temp = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        delete temp;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    int frontNode() {
        return front->Data;
    }
};
