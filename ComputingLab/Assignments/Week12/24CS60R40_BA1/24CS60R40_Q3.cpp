

#include <iostream>

using namespace std;

template <typename T>
struct ListNode{
    struct Node {
        T data;
        Node *next;
    };

    Node * Head;
    ListNode(){
        Head = NULL;
    }

    void Insert(T Data){
        Node * NewNode =    (Node *)malloc(sizeof(Node));
        NewNode->data = Data;
        NewNode->next = NULL;
        if(Head == NULL){
            Head = NewNode;
        }else{
            Node * Temp = Head;
            while(Temp->next != NULL){
                Temp = Temp ->next;
            }
            Temp->next = NewNode;
        }
    }

    void Remove(T Data){
        if(Head == NULL){
            return ;
        }else{
            if(Head->data == Data){
                Node * Temp  =  Head;
                Head = Head -> next;
                free(Temp);
            }else{
                Node * Temp = Head;
                Node * Prev = NULL;
                while(Temp != NULL && Temp->data != Data){
                    Prev = Temp;
                    Temp = Temp -> next;
                }
                Prev->next = Temp->next;
                free(Temp);

            }
        }
    }

    void Print(){
        if(Head != NULL){
            Node * Temp = Head;
            while (Temp != NULL)
            {
                // cout<<Temp->data.Vertex<<" ";
                cout<<Temp->data.Weight<<" ";
                Temp = Temp ->next; 
            }
            cout<<"\n";
            
        }
    }

    int Size(){
        if(Head == NULL)
            return 0;
        int count = 0;
        Node * Temp = Head;
        while(Temp != NULL){
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
            if (current != nullptr)
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
        return Iterator(nullptr);
    }


};

struct Pair{
    int Vertex;
    int Weight;
};


template <typename T>
void AddEdge(ListNode<T> Adj[], int v , int u, int Weight){
    Pair Vnode, Unode;
    Vnode.Vertex = v;
    Unode.Vertex = u;
    Unode.Weight = Vnode.Weight = Weight; 

    Adj[v].Insert(Unode);


}
template <typename T>
int* FindShortestPath(ListNode<T> Adj[], int NumberOfCities, int NumberOfStops, int NumberOfRoutes, int Source, int Destination)
{
    int* Distance = (int *)malloc(sizeof(int) * NumberOfCities);
    cout<<"Source: "<<Source<<"\n";
    cout<<"Destination "<<Destination<<"\n";
    cout<<"Number of cities "<<NumberOfCities<<"\n";
    if ((Source >= 0 && Source < NumberOfCities) && (Destination >= 0 && Destination < NumberOfCities ))
    {
        for (int i = 0; i < NumberOfCities; i++)
        {
            Distance[i] = 1e9;
        }
        Distance[Source] = 0;

        for (int i = 0; i < NumberOfStops; i++)
        {
            for (int j = 0; j < NumberOfRoutes; j++)
            {
                int Vertex = j;
                for (auto u : Adj[Vertex])
                {
                    int AdjacentVertex = u.Vertex;
                    int AdjaceWeight = u.Weight;
                    if (Distance[Vertex] != 1e9 &&  Distance[AdjacentVertex] > Distance[Vertex] + AdjaceWeight)
                    {
                        Distance[AdjacentVertex] = Distance[Vertex] + AdjaceWeight;
                    }
                }
            }
        }
        cout<<"Distance \t";
        for (int i = 0; i < NumberOfCities; i++)
        {
            cout<<Distance[i]<<"\t";
        }
        cout<<"\n";
        
        return Distance;
    }else{
        return NULL;
    }
}

template <typename T>
void Print(ListNode<T> Adj[], int v){
    for (int i = 0; i < v; i++)
    { 
        for (auto u : Adj[i])
        {
            cout<<" "<<i <<" "<<u.Vertex<<" "<<u.Weight<<"\n";
        
        }
       
    }
    
}
int main(int argc , char *argv[])
{
    int NumberOfCities = 4;
   
    // if (argc < 2)
    // {
    //     printf("Usage: %s <input_file>\n", argv[0]);
    //     return 1;
    // }
    // FILE * input = fopen("input.txt" , "r");

    int src = 0, dst = 3, k = 3;
    // fscanf(input , "%d ", &NumberOfCities);
    // fscanf(input , "%d ", &src);
    // fscanf(input , "%d ", &dst);
    // fscanf(input ,  "%d " , &k);
    //     int V, U, Weight;
    // while (fscanf(input , "%d %d %d" , &V, &U, &Weight ) != EOF)
    // {
    //     AddEdge(Adj , V , U , Weight);
    // }

    int flights[][3] = {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
    int NumberOfRoutes = sizeof(flights) / sizeof(flights[0]);

    
       ListNode<Pair> *Adj =  (ListNode<Pair> *) malloc(sizeof(ListNode<Pair> ) * NumberOfCities); 
    for (int i = 0; i < NumberOfRoutes; i++)
    {
        AddEdge(Adj , flights[i][0] , flights[i][1] , flights[i][2]);
    }    



    Print(Adj, NumberOfCities);
    

 
    int * distance = FindShortestPath(Adj , NumberOfCities , k, NumberOfRoutes , src, dst);
    if(distance){
        cout<<"Cost from "<<src<<" to "<<dst<< " is "<<distance[dst]<<"\n";
    }
    else{
        cout<<"Error\n";
    }
    return 0;
}
