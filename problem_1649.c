
typedef struct Node{
    int val;
    int height;
    int count; // frequency of this node
    int size; //total nodes in the subtree
    struct Node *left, *right;
}Node;

Node* createNode(int value){
    Node *newNode = (Node *)malloc(sizeof(Node));
    if(newNode==NULL) return NULL;

    newNode->val = value;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    newNode->count = newNode->size = 1;

    return newNode;
}


int size(Node *root){
     return root ? root->size : 0;
}

int height(Node *root){
     return root ? root->height : 0;
}

int findBalance(Node* root){
    return root ? height(root->left) - height(root->right) : 0;
}

void update(Node* root){
     int lefthight = height(root->left);
     int righthight = height(root->right);
     root->height = 1 + (lefthight > righthight ? lefthight : righthight);
     root->size = size(root->left) + root->count + size(root->right);
}

int countSmallers(Node *root, int value){
     if(root==NULL) return 0;

     if(value<=root->val){
          return countSmallers(root->left, value);
     }
     else{
          return size(root->left) + root->count + countSmallers(root->right, value);
     }
}

Node* leftRotate(Node *x){
    Node *y = x->right;
    Node *t = y->left;

    x->right = t;
    y->left = x;
    
    update(x);
    update(y);

    return y;
}

Node* rightRotate(Node *x){
    Node* y = x->left;
    Node* t = y->right;

    y->right = x;
    x->left = t;
    
    update(x);
    update(y);

    return y;
}

Node* insertInAVL(Node* root, int value){
    if(root==NULL) return createNode(value);

    if(value<root->val){
        root->left = insertInAVL(root->left, value);
    }
    else if(value>root->val){
        root->right = insertInAVL(root->right, value);
    }
    else{
        root->count++;
        update(root);
        return root;
    }

    update(root);

    int balance = findBalance(root);

    if(balance>1 && value<root->left->val){
        return rightRotate(root);
    }

    if(balance<-1 && value>root->right->val){
        return leftRotate(root);
    }

    if(balance>1 && value>root->left->val){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if(balance<-1 && value<root->right->val){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
int mod = 1e9+7;
int createSortedArray(int* instructions, int instructionsSize){
    Node *root = NULL;
    int cost = 0;
    for(int i=0; i<instructionsSize; i++){
        int value = instructions[i];
        int left = countSmallers(root, value);
        int right = root ? size(root) - countSmallers(root, value+1) : 0;

        cost = (cost + (left<right ? left : right))%mod;
        root = insertInAVL(root, value);
        //printf("%d: [%d, %d]\n", value, left, right);
    }
    return cost;
}