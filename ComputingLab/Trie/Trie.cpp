

#include <bits/stdc++.h>

using namespace std;

struct Trie
{
    struct Node
    {
        Node *child[26];
        bool isEnd;
        Node()
        {
            isEnd = false;
            for (int i = 0; i < 26; i++)
            {
                this->child[i] = NULL;
            }
        }
    };
    Node * Root;
    Trie(){
        Root = new Node();
    }

    bool Search(char *str, int len)
    {
        Node *Current = Root;
        for (int i = 0; i < len; i++)
        {
            int index = str[i] - 'a';
            if(Current->child[index ] == NULL){
                return false;
            }
            Current = Current->child[index];
        }
        return Current->isEnd;
    }


    void Insert(char *str, int len)
    {
        Node *Current = Root;
        for (int i = 0; i < len; i++)
        {
            int index = str[i] - 'a';
            if(Current->child[index ] == NULL){
                Current->child[index] = new Node();
            }
            Current = Current->child[index];
        }
        Current->isEnd = true;
    }

    Node* Delete(Node * root, char * str, int i, int len){
        if(root == NULL)
            return NULL;
        if(i == len){
            root->isEnd = false;
            if(isEmpty(root) == true){
                delete root;
                root = NULL;
            }
            return root;
        }  
        int index = str[i] - 'a';
        root->child[index] = Delete(root->child[index], str, i + 1, len);
        if(isEmpty(root) == true && root->isEnd == false){
            delete root;
            root = NULL;
        }
        return root;
    }

    bool isEmpty(Node * root){
        for (int i = 0; i < 26; i++)
        {
            if(root->child[i] != NULL){
                return false;
            }
        }
        return true;
        
    }
};
// Function to generate a random string of given length
void generateRandomString(char *str, int length)
{
    for (int i = 0; i < length; ++i)
    {
        str[i] = 'a' + rand() % 26;
    }
    str[length] = '\0'; // Null-terminate the string
}

int main()
{
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    Trie trie;
    const int numWords = 10;
    const int wordLength = 5;

    char word[wordLength + 1]; // +1 for the null terminator

    // Insert 1000 random words into the Trie
    for (int i = 0; i < numWords; ++i)
    {
        generateRandomString(word, wordLength);
        trie.Insert(word, wordLength);
        cout << "Inserted: " << word << endl;
    }

    // Search for each inserted word to verify
    cout << "Searching for inserted words:\n";
    for (int i = 0; i < numWords; ++i)
    {
        generateRandomString(word, wordLength);
        bool found = trie.Search(word, wordLength);
        cout << "Searching for '" << word << "': " << (found ? "Found" : "Not Found") << endl;
    }

    return 0;
}