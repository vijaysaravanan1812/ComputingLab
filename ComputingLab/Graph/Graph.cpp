#include <iostream>

using namespace std;

struct ListNode
{
    struct Node
    {
        int Data;
        Node *next;
    };
    Node *Head;

    ListNode()
    {
        Head = nullptr;
    }

    void Insert(int Data)
    {
        Node *NewNode = new Node();
        NewNode->Data = Data;
        NewNode->next = nullptr;
        if (Head == nullptr)
        {
            Head = NewNode;
        }
        else
        {
            Node *Temp = Head;
            while (Temp->next != nullptr)
            {
                Temp = Temp->next;
            }
            Temp->next = NewNode;
        }
    }

    int Delete(int Data)
    {
        Node *Temp = Head;
        if (Temp == nullptr)
        {
            return 0;
        }
        else
        {
            Node *Prev = nullptr;
            while (Temp != nullptr && Temp->Data != Data)
            {
                Prev = Temp;
                Temp = Temp->next;
            }
            if (Head == Temp)
            {
                Head = Temp->next;
                delete Temp;
                return 1;
            }
            if (Temp == nullptr)
                return 0;
            else
            {
                Prev->next = Temp->next;
                delete Temp;
                return 1;
            }
        }
    }

    int size()
    {
        Node *Temp = Head;
        if (Head == NULL)
            return 0;
        else
        {
            int i = 0;
            while (Temp != NULL)
            {
                i++;
                Temp = Temp->next;
            }
            return i;
        }
    }

    int &operator[](int index)
    {
        Node *Temp = ListNode::Head;
        for (int i = 0; i < index && Temp != nullptr; ++i)
        {
            Temp = Temp->next;
        }
        if (Temp != nullptr)
        {
            return Temp->Data;
        }
        else
        {
            throw out_of_range("Index out of range");
        }
    }
    // Iterator class to support range-based for loops
    struct Iterator
    {
        Node *current;

        // Constructor for the iterator
        Iterator(Node *node)
        {
            current = node;
        }

        // Overload dereference operator
        int &operator*()
        {
            return current->Data;
        }

        // Overload the prefix increment operator
        Iterator &operator++()
        {
            if (current != nullptr)
            {
                current = current->next;
            }
            return *this;
        }

        // Overload the inequality operator
        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }
    };

    // Begin function for range-based for loop
    Iterator begin()
    {
        return Iterator(Head);
    }

    // End function for range-based for loop
    Iterator end()
    {
        return Iterator(nullptr);
    }
};


