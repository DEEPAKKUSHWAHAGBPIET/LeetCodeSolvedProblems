/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
bool isAnagrams(char *str1, char *str2){
    int arr[256] = 0;
    for(int i=0; i<str1[i]!='\0'; i++){
        arr[str1[i]]++;
    }
    for(int i=0; i<str2[i]!='\0'; i++){
        arr[str2[i]]--;
        if(arr[str2[i]]<=0) return false;
    }
    return true;
}


struct Node {
    char key[50];
    int value;
    struct Node *next;
};

struct Node* hashTable[TABLE_SIZE];

void init(){
     for(int i=0; i<TABLE_SIZE; i++){
          hashTable[i] = NULL;
     }
}

//hash function
unsigned int hash(const char *key)
{
    unsigned int hashValue = 0;

    while (*key)
    {
        hashValue = (hashValue * 31) + *key++;
    }
    return hashValue % TABLE_SIZE;
}

//insert
void insert(const char *key, int value)
{
    unsigned int index = hash(key);

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;

    if(hashTable[index] == NULL)
    {
        hashTable[index] = newNode;
    }
    else
    {
        struct Node *temp = hashTable[index];
        while(temp->next != NULL)
        {
            if(strcmp(temp->key, key) == 0)
            {
                temp->value = value;
                free(newNode);
            }
            temp = temp->next;
        }
    
        if(strcmp(temp->key, key) == 0)
        {
            temp->value = value;
            free(newNode);
            return;
        }
        temp->next = newNode;
    }  
    printf("(%s, %d) is successfully inserted at the index %u \n", key, value, index); 
}

//search
int search(const char *key)
{
    unsigned int index = hash(key);
    struct Node *temp = hashTable[index];

    while (temp != NULL)
    {
        if(strcmp(temp->key, key) == 0)
        {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;
}
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    
}