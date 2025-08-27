#define TABLE_SIZE 256

struct Node {
    char key;
    int value;
    struct Node *next;
};

struct Node* hashTable[TABLE_SIZE];

void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}


//hash function
unsigned int hash(const char key)
{

    return (unsigned char)key;
}

//insert
void insert( char key)
{
    unsigned int index = hash(key);

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = 0;
    newNode->next = NULL;
    if(hashTable[index]==NULL){
        newNode->value += 1;
        hashTable[index] = newNode;
    }else{
        hashTable[index]->value += 1;
    }
}

//search

int firstUniqChar(char* s) {
    // int arr[256] = {0};
    initHashTable();
    for(int i=0; s[i]!='\0'; i++){
        char ch = s[i];
        insert(ch);
    }
    for(int i=0; s[i]!='\0'; i++){
        char ch = s[i];
        unsigned int index = hash(ch);
        int freq = hashTable[index]->value;
        printf("%d ", freq);
        if(freq==1){
            return i;
        }
    }
    return -1;
}