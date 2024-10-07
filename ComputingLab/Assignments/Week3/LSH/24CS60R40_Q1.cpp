
#include <bits/stdc++.h>

using namespace std;

#define SHINGLE_SIZE 3
#define MAX_NUM_SHINGLES 100
#define MAX_SENTENCES 10
#define MAX_ARRAY_SIZE 500
#define SPARSE_VECTOR_SIZE 500
#define DENSE_VECTOR_SIZE 10

int Permutation[DENSE_VECTOR_SIZE][SPARSE_VECTOR_SIZE];

typedef struct Info
{
    int SentenceNumber;
    int SparseVector[MAX_ARRAY_SIZE];
    char *Shingles[MAX_ARRAY_SIZE];
    char *Sentence;
    int NumberOfSingles;
    int *DenseVector;
} Info;

bool isUnique(const char *Str, char *Array[], int Size)
{
    for (int i = 0; i < Size; ++i)
    {
        if (Array[i] != nullptr && strcmp(Str, Array[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

char **allocate2DArray(int numRows, int numCols)
{
    // Allocate memory for rows
    char **array = new char *[numRows];
    for (int i = 0; i < numRows; ++i)
    {
        // Allocate memory for columns
        array[i] = new char[numCols];
    }
    return array;
}

void deallocate2DArray(char **array, int numRows)
{
    for (int i = 0; i < numRows; ++i)
    {
        // Deallocate memory for row
        delete[] array[i];
    }
    // Deallocate memory for the columns
    delete[] array;
}

// Function to generate Shingles
void generateShingles(const char *Sentence, char **Shingles, int &numShingles)
{
    int sentenceLength = strlen(Sentence);

    numShingles = 0;

    for (int i = 0; i <= sentenceLength - SHINGLE_SIZE; i++)
    {
        for (int j = 0; j < SHINGLE_SIZE; j++)
        {
            char ch = Sentence[i + j];
            if (ch == ' ')
            {
                ch = '_';
            }
            else
            {
                ch = std::tolower(ch);
            }
            Shingles[numShingles][j] = ch;
        }

        Shingles[numShingles][SHINGLE_SIZE] = '\0';
        numShingles++;
    }
}

// Generate a random permutation of the range [0, SPARSE_VECTOR_SIZE]
void generateRandomPermutation(int permutation[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        permutation[i] = i;
    }
    for (int i = size - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        swap(permutation[i], permutation[j]);
    }
}

void CreatePermutationVectors(int SparseVectorSize, int DenseVectorSize)
{
    int permutation[SparseVectorSize];
    for (int j = 0; j < DenseVectorSize; ++j)
    {
        generateRandomPermutation(permutation, SparseVectorSize);
        for (int i = 0; i < SparseVectorSize; ++i)
        {
            Permutation[j][i] = permutation[i];
        }
    }
}

// Function to convert sparse vector to dense vector
int *sparseToDense(int sparseVector[], int sparseSize, int denseSize)
{
    int *Signature = new int[denseSize];
    memset(Signature, 0, sizeof(int) * denseSize);

    for (int j = 0; j < denseSize; ++j)
    {
        int minIndex = INT_MAX;

        for (int i = 0; i < sparseSize; ++i)
        {
            // Check if the sparse vector has a 1 and find the minimum index
            if (sparseVector[i] == 1 && Permutation[j][i] < minIndex)
            {
                minIndex = Permutation[j][i];
            }
        }

        if (minIndex < sparseSize)
        {
            Signature[j] = minIndex + 1;
        }
    }

    return Signature;
}

double CosineSimilarity(int L1[], int L2[], int size)
{
    int dotProduct = 0;
    int L1NormSquared = 0;
    int L2NormSquared = 0;

    // Compute dot product and squared norms
    for (int i = 0; i < size; ++i)
    {
        dotProduct += L1[i] * L2[i];
        L1NormSquared += L1[i] * L1[i];
        L2NormSquared += L2[i] * L2[i];
    }

    double L1Norm = sqrt(L1NormSquared);
    double L2Norm = sqrt(L2NormSquared);

    if (L1Norm == 0 || L2Norm == 0)
    {
        return 0;
    }

    return dotProduct / (L1Norm * L2Norm);
}

int editDistance(const char *str1, const char *str2)
{
    int m = strlen(str1);
    int n = strlen(str2);

    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; ++i)
    {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; ++j)
    {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {

                int insertOp = dp[i][j - 1] + 1;
                int deleteOp = dp[i - 1][j] + 1;
                int substituteOp = dp[i - 1][j - 1] + 1;
                dp[i][j] = (insertOp < deleteOp) ? (insertOp < substituteOp ? insertOp : substituteOp) : (deleteOp < substituteOp ? deleteOp : substituteOp);
            }
        }
    }

    return dp[m][n];
}

int main()
{
    char *Vocabulary[MAX_ARRAY_SIZE] = {nullptr};
    char sentences[MAX_SENTENCES][100];

    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile)
    {
        fprintf(stderr, "Unable to open input file!\n");
        return 1;
    }

    int sentenceCount = 0;
    while (sentenceCount < MAX_SENTENCES && fgets(sentences[sentenceCount], sizeof(sentences[sentenceCount]), inputFile))
    {
        sentences[sentenceCount][strcspn(sentences[sentenceCount], "\n")] = '\0'; // Remove newline character
        sentenceCount++;
    }
    fclose(inputFile);

    int numShingles;
    int k = 0;
    Info Information[MAX_SENTENCES];

    // Generate shingles for each sentence and insert into Array
    for (int i = 0; i < MAX_SENTENCES; ++i)
    {

        Information[i].SentenceNumber = i + 1;
        Information[i].Sentence = new char[strlen(sentences[i]) + 1];
        strcpy(Information[i].Sentence, sentences[i]);

        char **shingles = allocate2DArray(MAX_NUM_SHINGLES, SHINGLE_SIZE + 1);
        generateShingles(sentences[i], shingles, numShingles);

        Information[i].NumberOfSingles = numShingles;

        for (int j = 0; j < numShingles; ++j)
        {
            Information[i].Shingles[j] = new char[SHINGLE_SIZE + 1];
            strcpy(Information[i].Shingles[j], shingles[j]);

            if (isUnique(shingles[j], Vocabulary, k))
            {
                Vocabulary[k] = new char[SHINGLE_SIZE + 1];
                strcpy(Vocabulary[k], shingles[j]);
                k++;
            }
        }

        // Deallocate the 2D array of shingles
        deallocate2DArray(shingles, MAX_NUM_SHINGLES);
    }

    int UsedIndex = 0;
    for (int i = 0; i < k; i++)
    {
        if (Vocabulary[i] != nullptr)
        {
            UsedIndex++;
        }
    }

    // Initialize SparseVector
    for (int i = 0; i < MAX_SENTENCES; ++i)
    {

        memset(Information[i].SparseVector, 0, sizeof(Information[i].SparseVector));

        for (int j = 0; j < Information[i].NumberOfSingles; ++j)
        {
            int shingleIndex = -1;

            for (int k = 0; k < UsedIndex; ++k)
            {
                if (strcmp(Information[i].Shingles[j], Vocabulary[k]) == 0)
                {
                    shingleIndex = k;
                    break;
                }
            }

            if (shingleIndex != -1)
            {
                Information[i].SparseVector[shingleIndex] = 1;
            }
        }
    }

    if (remove("output.txt") == 0)
    {
        fprintf(stdout, "Output file deleted.\n");
    }
    else
    {
        fprintf(stdout, "Output file did not exist or could not be deleted.\n");
    }

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile)
    {
        fprintf(stderr, "Unable to open output file!\n");
        return 1;
    }

    CreatePermutationVectors(UsedIndex, 10);

    fprintf(outputFile, "Dense Vector\n");
    for (int i = 0; i < DENSE_VECTOR_SIZE; i++)
    {
        for (int j = 0; j < UsedIndex; j++)
        {

            fprintf(outputFile, "%d \t", Permutation[i][j]);
        }
        fprintf(outputFile, "\n");
    }
    fprintf(outputFile, "--------------------------------------------\n\n");

    for (int i = 0; i < MAX_SENTENCES; i++)
    {
        Information[i].DenseVector = (int *)malloc(sizeof(int) * DENSE_VECTOR_SIZE);
        Information[i].DenseVector = sparseToDense(Information[i].SparseVector, UsedIndex, 10);
    }

    for (int i = 0; i < MAX_SENTENCES; ++i)
    {
        fprintf(outputFile, "Sentence Number: %d \n", Information[i].SentenceNumber);
        fprintf(outputFile, "Sentence: %s \n", Information[i].Sentence);
        fprintf(outputFile, "Shingles: \n");
        for (int j = 0; j < Information[i].NumberOfSingles; ++j)
        {
            fprintf(outputFile, "%s \t", Information[i].Shingles[j]);
        }
        fprintf(outputFile, "\nSparse Vector: \n");
        for (int j = 0; j < UsedIndex; ++j)
        {
            fprintf(outputFile, "%d \t", Information[i].SparseVector[j]);
        }
        fprintf(outputFile, "\nSparse Vector used size: %d \n", UsedIndex);
        fprintf(outputFile, "Sparse Vector size: %zu\n", sizeof(Information[i].SparseVector) / sizeof(Information[i].SparseVector[0]));
        fprintf(outputFile, "Dense Vector: ");
        for (int j = 0; j < 10; j++)
        {
            fprintf(outputFile, " %d", Information[i].DenseVector[j]);
        }
        fprintf(outputFile, "\n\n");
    }

    for (int i = 0; i < MAX_SENTENCES; i++)
    {
        fprintf(outputFile, "\n-----------%d----------------\n", i + 1);
        for (int j = 0; j < MAX_SENTENCES; j++)
        {
            if (i != j)
            {
                fprintf(outputFile, "\n----------------------------------\n");
                fprintf(outputFile, "Cosine Similarity and edit distance between :\n"
                                    "%s\n"
                                    "%s\n",
                        Information[i].Sentence, Information[j].Sentence);
                fprintf(outputFile, "%f\n", CosineSimilarity(Information[i].DenseVector, Information[j].DenseVector, 10));
                fprintf(outputFile, "%d\n", editDistance(Information[i].Sentence, Information[j].Sentence));
                fprintf(outputFile, "\n----------------------------------\n");
            }
        }
        fprintf(outputFile, "----------------------------------\n");
    }

    return 0;
}
