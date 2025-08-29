// typedef enum {red, black} Color;

// typedef struct Node{
//     long long value;
//     Color color;
//     int count;
//     int size;
//     struct Node *left, *right, *parent;
// }Node;

// Node* createNode(long long value){
//     Node *newNode = (Node *)malloc(sizeof(Node));
//     if(newNode==NULL) return NULL;

//     newNode->value = value;
//     newNode->count = 1;
//     newNode->size = 1;
//     newNode->color = red;
//     newNode->left = newNode->right = newNode->parent = NULL;

//     return newNode;
// }

// int getSize(Node *node){
//     return (node ? node->size : 0);
// }

// void updateSize(Node *node){
//     if(node==NULL) return;

//     node->size = getSize(node->left) + node->count + getSize(node->right);
// }

// //number of prefix sum less than value;
// long long getRank(Node *root, long long value){
//     Node *curr = root;
//     long long rank = 0;
//     if(curr==NULL) return 0;
//     while(curr){
//         if(curr->value > value){
//             curr = curr->left;
//         }
//         else{
//             rank += (long long)getSize(curr->left) + curr->count;
//             curr = curr->right;
//         }
//     }
//     return rank;
// }

// void leftRotate(Node **root, Node *x){
//     if(x==NULL || x->right==NULL) return;
//     Node *y = x->right;
//     x->right = y->left;
//     if(y->left!=NULL) y->left->parent = x;

//     if(y->left!=NULL){
//         y->left->parent = x;
//     }

//     y->parent = x->parent;
//     if(x->parent==NULL){
//         *root = y;
//     }
//     else if(x==x->parent->left){
//         x->parent->left = y;
//     }
//     else{
//         x->parent->right = y;
//     }

//     y->left = x;
//     x->parent = y;

//     updateSize(x);
//     updateSize(y);
// }

// void rightRotate(Node **root, Node *x){
//     if(x==NULL || x->left==NULL) return;
//     Node *y = x->left;
//     x->left = y->right;
//     if(y->right!=NULL) y->right->parent = x;

//     y->parent = x->parent;
//     if(x->parent==NULL){
//         *root = y;
//     }
//     else if(x==x->parent->left){
//         x->parent->left = y;
//     }
//     else{
//         x->parent->right = y;
//     }

//     y->right = x;
//     x->parent = y;

//     updateSize(x);
//     updateSize(y);
// }

// void fixInsert(Node **root, Node *z){
//     while(z!=*root && z->parent->color == red){
//         Node *parent = z->parent;
//         Node *grandParent = parent->parent;
//         if(grandParent && (parent == grandParent->left)){
//             Node *uncle = grandParent->right;
//             if(uncle && uncle->color==red){
//                 parent->color = black;
//                 uncle->color = black;
//                 grandParent->color = red;

//                 z = grandParent;
//             }
//             else{
//                 if(z == parent->right){
//                     z = parent;
//                     leftRotate(root, z);
//                 }
//                 else{
//                     z->parent->color = black;
//                     grandParent->color = red;
//                     rightRotate(root, grandParent);
//                 }
//             }
//         }
//         else{
//             Node *uncle = grandParent?grandParent->right:NULL;
//             if(uncle && uncle->color==red){
//                 parent->color = black;
//                 uncle->color = black;
//                 grandParent->color = red;

//                 z = grandParent;
//             }
//             else{
//                 if(z == parent->left){
//                     z = parent;
//                     rightRotate(root, z);
//                 }

//                 parent->color = black;
//                 if(grandParent!=NULL)
//                  grandParent->color = red;
//                 leftRotate(root, grandParent);
//             }
//         }
//     }
//     if(*root){
//         (*root)->color = black;
//     }
// }

// void insertValue(Node **root, long long val) {
//     Node *y = NULL, *x = *root;

//     while (x != NULL) {
//         y = x;
//         x->size += 1;                 
//         if (val == x->value) {
//             x->count += 1;           
//             return;
//         } else if (val < x->value) x = x->left;
//         else x = x->right;
//     }

//     Node *z = createNode(val);
//     z->parent = y;

//     if (y == NULL) {
//         *root = z;
//     } else if (val < y->value) {
//         y->left = z;
//     } else {
//         y->right = z;
//     }

//     fixInsert(root, z);
// }
// int countRangeSum(int* nums, int numsSize, int lower, int upper) {
//     Node *root = NULL;

//     insertValue(&root, 0);

//     long long ans = 0;
//     long long prefix = 0;

//     for(int i=0; i<numsSize; i++){
//         prefix += (long long)nums[i];

//         long long l = prefix - (long long)upper;
//         long long r = prefix - (long long)lower;

//         int cr = getRank(root, r);
//         long long cl;
//         if (l == LLONG_MIN) cl = 0; // avoid L-1 overflow
//         else cl = getRank(root, l - 1);

//         ans += (cr-cl);
//         insertValue(&root, prefix);
//     }
//     return (int)ans;
// }

//optimal solution that pass all the test cases
long long mergeCount(long long *prefix, long long *temp,
                     int left, int right,
                     long long lower, long long upper) {

    if (right - left <= 1) {
        return 0;   
    }

    int mid = (left + right) / 2;
    long long count = 0;

    
    count += mergeCount(prefix, temp, left, mid, lower, upper);
    count += mergeCount(prefix, temp, mid, right, lower, upper);

    
    int lowPtr = mid;
    int highPtr = mid;

    for (int i = left; i < mid; i++) {
       
        while (lowPtr < right && prefix[lowPtr] - prefix[i] < lower) {
            lowPtr++;
        }
        
        while (highPtr < right && prefix[highPtr] - prefix[i] <= upper) {
            highPtr++;
        }
        count += (highPtr - lowPtr);
    }

    
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (prefix[i] <= prefix[j]) {
            temp[k++] = prefix[i++];
        } else {
            temp[k++] = prefix[j++];
        }
    }
    while (i < mid) {
        temp[k++] = prefix[i++];
    }
    while (j < right) {
        temp[k++] = prefix[j++];
    }

    
    for (int t = left; t < right; t++) {
        prefix[t] = temp[t];
    }

    return count;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    
    long long *prefix = (long long*)malloc(sizeof(long long) * (numsSize + 1));
    long long *temp   = (long long*)malloc(sizeof(long long) * (numsSize + 1));

    prefix[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }

   
    long long ans = mergeCount(prefix, temp, 0, numsSize + 1,
                               (long long)lower, (long long)upper);

    free(prefix);
    free(temp);

    return (int)ans;
}
