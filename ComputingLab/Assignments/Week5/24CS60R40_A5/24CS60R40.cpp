
#include <bits/stdc++.h>

using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of words and maximum word length
#define MAX_WORDS 50000
#define MAX_WORD_LEN 100



// Structure for Trie node (Hint)
struct TrieNode
{
    struct TrieNode *children[256]; // Each node can have 26 children (for each letter of the alphabet)
    int isEndOfWord;               // Flag to indicate if the node represents the end of a word
    int rank;
    
};

typedef struct TrieNode TrieNode; // Defining the TrieNode structure

TrieNode *root;


bool isEmptyroot(TrieNode *root);
// Function prototypes with descriptions
void Add(TrieNode *root, char *w, int Length);
// Adds the word `w` to the Trie and sets its initial rank to 1.

void Delete(TrieNode *root, char *w);
// Deletes the word `w` from the Trie, ensuring the rank is removed appropriately.

int SpellCheck(TrieNode *root, char *w);
// Checks if the word `w` is spelled correctly in the Trie. Returns 1 if correct, otherwise 0.

void Autocomplete(TrieNode *root, char *prefix, FILE *outputFile);
// Finds and prints all words in the Trie that start with the prefix `prefix`, sorted by rank and lexicographically.

void Autocorrect(TrieNode *root, char *w, int maxCost, FILE *outputFile);
// Finds the closest word in the Trie to `w` using Levenshtein distance and updates the rank.

int CheckConcatenation(TrieNode *root, char *w, FILE *outputFile);
// Checks if `w` can be formed by concatenating two or more words in the Trie. Returns 1 if possible, otherwise 0.

int main(int argc, char *argv[])
{
    root = NULL;
    cout<<"--------\n";
    FILE *file = fopen("dict.bin", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (!outputFile)
    {
        printf("Could not open output file output.txt\n");
        return 1;
    }
    fclose(outputFile);
    outputFile = fopen("output.txt", "a");

    cout<<"--------\n";
    char word[MAX_WORD_LEN];

    // TODO : Replace NULL with actual Trie initialization code

    while (fgets(word, MAX_WORD_LEN, file) != NULL)
    {
        word[strcspn(word, "\n")] = '\0';
    
        int count = 0;
        int isValid = true;
        while (count < strlen(word))
        {
            if(!( 0 <= (int)word[count] &&  256 > (int)word[count] ) ) 
                isValid = false;
            count++;
        }
        int length = strlen(word);
        if(isValid == false)
            continue;
        // Add word to Trie
        Add(root, word, length);
    }

    // now read the query file
    file = fopen("input.txt", "r");

    int Q;

    fscanf(file, "%d", &Q);
    cout<<"Q = "<<Q<<"\n";

    // Reading the queries and processing them
    for (int i = 0; i < Q; i++)
    {

        int x;
        char w[MAX_WORD_LEN];
        fscanf(file, "%d %s", &x, w);

        int count = 0;
        while (w[count] != '\0')
        {
            count++;
        }
        int length = count;

        switch (x)
        {
        case 1:
            // Add word w to the Trie with rank 1
            Add(root, w, length);
            fprintf(outputFile, "Add function called with word: %s\n", w);
            break;
        case 2:
            // Delete word w from the Trie
            Delete(root, w);
            fprintf(outputFile ,  "Delete function called with word: %s\n", w);
            break;
        case 3:
            // Check if the word w is spelled correctly
            if (SpellCheck(root, w))
            {
                fprintf(outputFile, "1\n");
                fprintf(outputFile, "Spell-Check function: Word %s is correct\n", w);
            }
            else
            {
                fprintf(outputFile, "0\n");
                fprintf(outputFile, "Spell-Check function: Word %s is incorrect\n", w);
            }
            break;
        case 4:
            // Autocomplete based on prefix w
            Autocomplete(root, w, outputFile);
            printf("Autocomplete function called with prefix: %s\n", w);
            break;
        case 5:
            // Autocorrect word w to the closest word in the Trie
            Autocorrect(root, w, 3, outputFile);
            printf("Autocorrect function called with word: %s\n", w);
            break;
        case 6:
            // Check if the word w can be formed by concatenating two or more Trie words
            if (CheckConcatenation(root, w, outputFile))
            {
                fprintf(outputFile, "1\n");
                printf("Check_Concatenation function: Word %s can be formed by concatenation\n", w);
            }
            else
            {
                fprintf(outputFile, "0\n");
                printf("Check_Concatenation function: Word %s cannot be formed by concatenation\n", w);
            }
            break;
        default:
            printf("Unknown operation: %d\n", x);
            break;
        }
    }
    fclose(file);
    fclose(outputFile);
    return 0;
}

struct TrieNode* getNode() {
    struct TrieNode* node =
    (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    node->rank = 0;
    return node;
}

// Function to add a word to the Trie with rank 1
void Add(TrieNode *root, char *word, int Length)
{
    // Insert the word `w` into the Trie, creating nodes as necessary
    // Set the rank to 1 if this is the first time the word is added
   
    struct TrieNode *Current = root;
    if(Current == NULL){
        root = Current = getNode();
    }
    for (int i = 0; i < Length; i++)
    {
        int index = (int)word[i];
     
        if ( !Current->children[index])
        {
            Current->children[index] = getNode();
  
            
        }
    
        Current = Current->children[index];
    }
    Current->rank = 1;
    Current->isEndOfWord = true;
}

bool isEmptyroot(TrieNode *root)
{
    for (int i = 0; i < 26; i++)
    {
        if (root->children[i] != NULL)
            return false;
    }
    return true;
}

TrieNode *Delete(TrieNode *root, char *Word, int Length, int i)
{
    if (root == NULL)
        return NULL;

    if (i == Length)
    {
        root->isEndOfWord = 0;
        if (isEmptyroot(root))
        {
            delete root;
            root = NULL;
        }
        return root;
    }
    int index = (int)Word[i];
    root->children[index] = Delete(root->children[index], Word, Length, i + 1);
    if (isEmptyroot(root) == true && root->isEndOfWord == false)
    {
        delete root;
        root = NULL;
    }
    return root;
}

// Function to delete a word from the Trie
void Delete(TrieNode *root, char *w)
{
    // Remove the word `w` from the Trie, and adjust the rank and Trie structure
    int count = 0;
    while (w[count] != '\0')
    {
        count++;
    }
    Delete(root, w, count, 0);
}

// Function to check if a word is spelled correctly
int SpellCheck(TrieNode *root, char *word)
{
    int Length = 0; 
    while(word[Length] != '\0'){
        Length++;
    }
    struct TrieNode *Current = root;
    for (int i = 0; i < Length; i++)
    {
        int index = (int)word[i];
        if (!Current->children[index])
        {
            return 0;
        }
        Current = Current->children[index];
    }


    if ((Current != NULL && Current->isEndOfWord))
    {
        if (Current->rank < 5)
        {
            Current->rank += 1;
        }
    }
    // Traverse the Trie to see if the word `w` exists
    // Return 1 if it exists and is spelled correctly, otherwise return 0
    // Placeholder return value for testing
    return (Current != NULL && Current->isEndOfWord);
}

// Function to autocomplete based on prefix w
void Autocomplete(TrieNode *root, char *prefix, FILE *outputFile)
{
    // Traverse the Trie to find all words that start with `prefix`
    // Print top 5 in decreasing order of rank and lexicographical(when same rank) order to the output file
}

// Function to autocorrect word `w` to the closest word in the Trie
void Autocorrect(TrieNode *root, char *w, int maxCost, FILE *outputFile)
{
    // 1. Initialize the first row of the dynamic programming matrix (currentRow)
    //    to represent the distance between the empty prefix and each prefix of the target word `w`.

    // 2. Initialize a list or array to store the results (words within maxCost).

    // 3. Iterate over each child node of the root. For each child node:
    //    a. Call the recursive search helper function with the current node,
    //       the corresponding letter, the target word, the initialized currentRow,
    //       and the maximum allowed cost.

    // 4. The recursive helper function will:
    //    a. Create a new row in the dynamic programming matrix based on the previous row.
    //    b. For each letter in the target word, calculate the cost of inserting, deleting,
    //       or replacing a character to match the current Trie path with the target word.
    //    c. If the final cost in the row is within maxCost and the current Trie node is
    //       the end of a word, add the word to the results array.
    //    d. If further exploration is needed, recursively call the helper function for each
    //       child node of the current node.

    // 5. After the search is complete, output the results (words within maxCost) to the output file.
}

// Function to check if word w can be formed by concatenating two or more Trie words
int CheckConcatenation(TrieNode *root, char *w, FILE *outputFile)
{
    // Check if `w` can be formed by concatenating two or more words in the Trie
    // Return 1 if it can, otherwise return 0
    return 0; // Placeholder return value
}
