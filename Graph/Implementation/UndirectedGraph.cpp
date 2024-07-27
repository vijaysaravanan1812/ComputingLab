
#include<iostream>
#include<vector>

using namespace std;

void printGrapth(vector<int> adj[] , int v){
    for(int i = 0 ; i < v ; i++){
        cout<<" "<<i<<"-->";
        for(auto x : adj[i]){
            cout<<x<<"  "; 
        }
        cout<<"\n";
    }
    
}

void addEdge(vector<int> adj[], int v, int u){
    adj[v].push_back(u);
    adj[u].push_back(v);
}


int main(){
    int v = 4 ;

    vector<int> adj[v];
    addEdge(adj, 0 ,1);
    addEdge(adj , 0, 2);
    addEdge(adj, 1, 2);
    addEdge(adj, 1 , 3);
    printGrapth(adj, v);

    return 0;
}