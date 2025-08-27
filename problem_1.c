/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int TABLE_SIZE;
struct Node {
    int key;
    int value;
    struct Node *next;
};

struct Node** hashTable;

//hash function
unsigned int hash( int key)
{
    return ((key % TABLE_SIZE) + TABLE_SIZE) % TABLE_SIZE;
}

//insert
void insert( int key, int value)
{
    unsigned int index = hash(key);

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
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
            if(temp->key==key)
            {
                temp->value = value;
                free(newNode);
                return;
            }
            temp = temp->next;
        }
    
        if(temp->key==key)
        {
            temp->value = value;
            free(newNode);
            return;
        }
        temp->next = newNode;
    }  
    //printf("(%s, %d) is successfully inserted at the index %u \n", key, value, index); 
}

//search
int search( int key)
{
    unsigned int index = hash(key);
    struct Node *temp = hashTable[index];

    while (temp != NULL)
    {
        if(temp->key==key)
        {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 0;
    int *ans = malloc(sizeof(int) * 2);

    // set TABLE_SIZE ≈ 2× numsSize to reduce collisions
    TABLE_SIZE = numsSize * 2 + 1;
    hashTable = calloc(TABLE_SIZE, sizeof(struct Node*));

    insert(nums[0], 0);
    for (int i = 1; i < numsSize; i++) {
        int complement = target - nums[i];
        int foundIndex = search(complement);
        if (foundIndex != -1) {
            ans[0] = foundIndex;
            ans[1] = i;
            *returnSize = 2;
            return ans;
        }
        insert(nums[i], i);
    }
    return ans; // no match found
}