/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
    Node *flatten_rec(Node *head){
        Node * cur = head, *tail = head;
        while(cur){
            Node* child = cur->child;
            Node* next = cur->next;
            if(child){
                Node *_tail = flatten_rec(child);
                _tail->next = next;
                if(next) next->prev = _tail;

                cur-> next = child;
                child->prev = cur;
                cur->child = NULL; 
                cur = tail;
            }
            else{
                cur = next;
            }
            if(cur) tail = cur;
        }
        return tail;
    }
public:
    Node* flatten(Node* head) {
        if(head) 
            flatten_rec(head);
        return head;
    }
};