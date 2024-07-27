// You are given the head of a singly linked-list. The list can be represented as:

// L0 → L1 → … → Ln - 1 → Ln
// Reorder the list to be on the following form:

// L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
// You may not modify the values in the list's nodes. Only nodes themselves may be changed.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        stack<ListNode*> Bucket;
        ListNode* temp = head, *fast = head, *slow = head;
        while(temp != NULL){
            Bucket.push(temp);
            temp = temp->next;
        }
        temp = NULL;

        while( fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode * Next;
        temp = head;
        Next = temp->next;
        while(temp != slow){
            temp->next = Bucket.top();
            Bucket.top()->next  = Next;
            temp = Next;
            Next = temp->next;
            Bucket.pop();
        }
        slow->next = NULL;
    }
};
