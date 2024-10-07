#include <iostream>
#include <climits>
using namespace std;

template <typename T>
struct ListNode
{
    struct Node
    {
        T data;
        Node *next;
        Node(T Data)
        {
            data = Data;
            next = NULL;
        }
    };

    Node *Head;
    ListNode()
    {
        Head = NULL;
    }

    void Insert(T Data)
    {
        Node *NewNode = new Node(Data);
        if (Head == NULL)
        {
            Head = NewNode;
        }
        else
        {
            Node *Temp = Head;
            while (Temp->next != NULL)
            {
                Temp = Temp->next;
            }
            Temp->next = NewNode;
        }
    }

    void Remove(T Data)
    {
        if (Head == NULL)
        {
            return;
        }
        else
        {
            if (Head->data == Data)
            {
                Node *Temp = Head;
                Head = Head->next;
                delete Temp;
            }
            else
            {
                Node *Temp = Head;
                Node *Prev = NULL;
                while (Temp != NULL && Temp->data != Data)
                {
                    Prev = Temp;
                    Temp = Temp->next;
                }
                if (Temp != NULL)
                {
                    Prev->next = Temp->next;
                    delete Temp;
                }
            }
        }
    }

    void Print()
    {
        if (Head != NULL)
        {
            Node *Temp = Head;
            while (Temp != NULL)
            {
                cout << Temp->data.Weight << " ";
                Temp = Temp->next;
            }
            cout << "\n";
        }
    }

    int Size()
    {
        if (Head == NULL)
            return 0;
        int count = 0;
        Node *Temp = Head;
        while (Temp != NULL)
        {
            count++;
            Temp = Temp->next;
        }
        return count;
    }

    struct Iterator
    {
        Node *current;
        Iterator(Node *node)
        {
            current = node;
        }

        T &operator*()
        {
            return current->data;
        }

        Iterator &operator++()
        {
            if (current != NULL)
            {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }
    };

    Iterator begin()
    {
        return Iterator(Head);
    }

    Iterator end()
    {
        return Iterator(NULL);
    }
};

struct Pair
{
    int Vertex;
    int Weight;
};

struct PriorityQueue
{
    Pair *heap;
    int capacity;
    int size;

    PriorityQueue(int cap = 1000)
    {
        capacity = cap;
        size = 0;
        heap = new Pair[capacity];
    }

    ~PriorityQueue()
    {
        delete[] heap;
    }

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index].Weight > heap[parent].Weight)
            {
                Pair temp = heap[index];
                heap[index] = heap[parent];
                heap[parent] = temp;
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    void heapifyDown(int index)
    {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < size && heap[leftChild].Weight > heap[largest].Weight)
        {
            largest = leftChild;
        }

        if (rightChild < size && heap[rightChild].Weight > heap[largest].Weight)
        {
            largest = rightChild;
        }

        if (largest != index)
        {
            Pair temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;
            heapifyDown(largest);
        }
    }

    void push(Pair value)
    {
        if (size == capacity)
        {
            cout << "Priority Queue is full!\n";
            return;
        }
        heap[size] = value;
        heapifyUp(size);
        size++;
    }

    void pop()
    {
        if (size == 0)
        {
            cout << "Priority Queue is empty!\n";
            return;
        }
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
    }

    Pair top()
    {
        if (size > 0)
        {
            return heap[0];
        }
        else
        {
            cerr << "Priority Queue is empty!\n";
            Pair Node;
            Node.Vertex = INT_MAX;
            Node.Weight = INT_MAX;
            return Node;
        }
    }

    bool empty()
    {
        return size == 0;
    }

    int getSize()
    {
        return size;
    }
};

template <typename T>
void AddEdge(ListNode<T> Adj[], int v, int u, int Weight)
{
    Pair Vnode, Unode;
    Vnode.Vertex = v;
    Unode.Vertex = u;
    Unode.Weight = Vnode.Weight = Weight;
    Adj[v].Insert(Unode);
    Adj[u].Insert(Vnode);
}

template <typename T>
void Print(ListNode<T> Adj[], int v)
{
    for (int i = 0; i < v; i++)
    {
        for (auto u : Adj[i])
        {
            cout << " " << i << " " << u.Vertex << " " << u.Weight << "\n";
        }
        cout << "\n";
    }
}

template <typename T>
int PrimsAlgorithm(ListNode<T> Adj[], int NumberOfVertex, FILE *output)
{
    bool visited[NumberOfVertex];
    int MinWeight[NumberOfVertex];
    fill(visited, visited + NumberOfVertex, false);
    fill(MinWeight, MinWeight + NumberOfVertex, INT_MAX);

    PriorityQueue MinHeap(NumberOfVertex);
    Pair Temp;
    Temp.Vertex= 0;
    Temp.Weight= 0;
    MinHeap.push(Temp);
   
    int Parent[NumberOfVertex];
    fill(Parent, Parent + NumberOfVertex, -1);


    int sum = 0;

    while (!MinHeap.empty())
    {
        Pair Node = MinHeap.top();
        MinHeap.pop();
        int Weight = Node.Weight;
        int Vertex = Node.Vertex;

        if (visited[Vertex])
            continue;

        visited[Vertex] = true;
        sum += Weight;

        
        
        for (auto u : Adj[Vertex])
        {
           
            int AdjacentVertex = u.Vertex;
            int AdjacentNodeWeight = u.Weight;
            if (!visited[AdjacentVertex] && AdjacentNodeWeight < MinWeight[AdjacentVertex])
            {
                Parent[AdjacentVertex] = Vertex;
                MinWeight[AdjacentVertex] = AdjacentNodeWeight;
                MinHeap.push({AdjacentVertex, AdjacentNodeWeight});
            }
        }
    }

    fprintf(output, "Weight of the MST: %d \n", sum);

    for (int i = 1; i < NumberOfVertex; ++i)
        fprintf(output, "%d %d %d \n", MinWeight[i], Parent[i], i);

    return sum;
}

template <typename T>
void Dijkstra(ListNode<T> Adj[], int v, bool Visited[], int Dist[], Pair Source, int Ways[])
{
    fill(Visited, Visited + v, false);
    fill(Dist, Dist + v, INT_MAX);
    Dist[Source.Vertex] = 0;

    PriorityQueue queue;

    queue.push(Source);
    Ways[Source.Vertex] = 1;
    while (!queue.empty())
    {
        Pair Node = queue.top();
        queue.pop();
        int Weight = Node.Weight;
        int Vertex = Node.Vertex;

        if (Visited[Vertex])
            continue;

        Visited[Vertex] = true;
        for (auto u : Adj[Vertex])
        {
            int AdjacentVertex = u.Vertex;
            int AdjaceWeight = u.Weight;
            if (Dist[AdjacentVertex] > Dist[Vertex] + AdjaceWeight)
            {
                Ways[u.Vertex] =  Ways[Vertex];
                Dist[AdjacentVertex] = Dist[Vertex] + AdjaceWeight;
                queue.push({AdjacentVertex, Dist[AdjacentVertex]});
            }else if(Dist[AdjacentVertex] == Dist[Vertex] + AdjaceWeight){
                 Ways[u.Vertex] +=  Ways[Vertex];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    FILE *output = fopen("output.txt", "w");


    int NumberOfVertices;
    fscanf(input, "%d", &NumberOfVertices);

    ListNode<Pair> *Adj = new ListNode<Pair>[NumberOfVertices];

    int V, U, Weight;
    while (fscanf(input, "%d %d %d", &V, &U, &Weight) != EOF)
    {
        AddEdge(Adj, V, U, Weight);
    }

    Print(Adj, NumberOfVertices);

    bool Visited[NumberOfVertices];
    int Distance[NumberOfVertices];
    int Ways[NumberOfVertices];
    Pair Source = {0, 0};
    PrimsAlgorithm(Adj, NumberOfVertices, output);
    Dijkstra(Adj, NumberOfVertices, Visited, Distance, Source, Ways);

    fprintf(output, "The shortest amount of time it takes to go from intersection 0 to intersection %d is %d minutes.\n", NumberOfVertices - 1, Distance[NumberOfVertices - 1]);
    fprintf(output, "#Possible Shortest Paths: %d",Ways[NumberOfVertices - 1]);

    fclose(input);
    fclose(output);

    return 0;
}
