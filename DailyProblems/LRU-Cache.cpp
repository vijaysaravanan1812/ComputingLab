class Node{
    public: 
        int key , value;
        Node* next ;
        Node * prev;

        Node() {
            key = -1;
            value = -1;
            prev = next = NULL;
        }
        Node(int key , int value){
            this->key = key;
            this->value = value; 
        }
};

class LRUCache {
    unordered_map<int , Node*> map;
    int capacity;
    Node * head , *tail;

    void deleteNode(Node * node, bool NoShallowDel){
        if(NoShallowDel){
            Node *PrevNode = node->prev;
            Node *NextNode = node->next;

            PrevNode->next = NextNode;
            NextNode->prev = PrevNode;
            delete node;
        }else{
            Node *PrevNode = node->prev;
            Node *NextNode = node->next;

            PrevNode->next = NextNode;
            NextNode->prev = PrevNode;
        }
    }
    void insertAfterHead(Node * node){
        Node * nextNode = head->next;
        head->next = node;
        nextNode->prev = node;
        node->prev = head;
        node->next = nextNode;
    }
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        map.clear();
        head = new Node();
        tail = new Node();
        head -> next = tail;
        tail -> prev = head;
    }
    
    int get(int key) {
        if(map.find(key) == map.end()){
            return -1;
        }
        Node * node = map[key];
        int val = node->value;
        deleteNode(node, false);
        insertAfterHead(node);
        return val;
    }
    
    void put(int key, int value) {
        if(map.find(key) != map.end()){
            Node* node = map[key];
            node->value = value;
            deleteNode(node , false);
            insertAfterHead(node);
            return;
        }
        if (map.size() == capacity){
            Node * node = tail->prev;
            map.erase(node->key);
            deleteNode(node, true);
        }
        Node *NewNode  = new Node(key, value);
        map[key] = NewNode;
        insertAfterHead(NewNode);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */