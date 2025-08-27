typedef enum {red, black} Color;

typedef struct Node{
    int value;
    int size;
    Color color;
    struct Node *left, *right, *parent;
}Node;

typedef struct {
    Node *root;
} MedianFinder;

Node* createNode(int value){
    Node *newNode = (Node *)malloc(sizeof(Node));
    if(newNode==NULL) return NULL;

    newNode->value = value;
    newNode->size = 1;
   
    newNode->color = red;
    newNode->left = newNode->right = newNode->parent = NULL;

    return newNode;
}

int getSize(Node *root){
    return root ? root->size : 0;
}

void updateSize(Node *root){
    if(root==NULL) return;
    root->size = getSize(root->left) + 1 + getSize(root->right);
}

void leftRotate(MedianFinder *mf, Node *x){
    if(x==NULL || x->right==NULL) return;
    Node *y = x->right;
    x->right = y->left;

    if(y->left!=NULL){
        y->left->parent = x;
    }

    if(x->parent==NULL){
        mf->root = y;
    }
    else if(x==x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;

    updateSize(x);
    updateSize(y);
}

void rightRotate(MedianFinder *mf, Node *x){
    if(x==NULL || x->left==NULL) return;
    Node *y = x->left;
    x->left = y->right;

    if(y->right!=NULL){
        y->right->parent = x;
    }

    if(x->parent==NULL){
        mf->root = y;
    }
    else if(x==x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;

    updateSize(x);
    updateSize(y);
}

void fixInsert(MedianFinder *mf, Node *z){
    while(z->parent && z->parent->color==red){
        Node *parent = z->parent;
        Node *grandParent = parent->parent;

        if(grandParent && parent==grandParent->left){
            Node *uncle = grandParent->right;
            if(uncle && uncle->color==red){
                uncle->color = black;
                parent->color = black;
                grandParent->color = red;

                z = grandParent;
            }
            else{
                if(z==parent->right){
                    z = parent;
                    leftRotate(mf, z);
                }

                parent->color = black;
                grandParent->color = red;
                rightRotate(mf, grandParent);
            }
        }
        else{
            Node* uncle = grandParent->left;
            if(uncle && uncle->color==red){
                uncle->color = black;
                parent->color = black;
                grandParent->color = red;

                z = grandParent;
            }
            else{
                if(z==parent->left){
                    z = parent;
                    rightRotate(mf, z);
                }
                parent->color = black;
                grandParent->color = red;

                leftRotate(mf, grandParent);
            }
        }
    }
    if(mf->root!=NULL)
     mf->root->color = black;
}

void insertValue(MedianFinder *mf, int val){
    Node *prev = NULL;
    Node *curr = mf->root;

    while(curr){
        prev = curr;
        curr->size++;
        if(val<curr->value){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }

    Node *z = createNode(val);
    z->parent = prev;
    if(prev==NULL){
        mf->root = z;
    }
    if(prev!=NULL){
        if(val<prev->value){
            prev->left = z;
        }
        else{
            prev->right = z;
        }
    }

    fixInsert(mf, z);
}

Node *findKthLargest(Node *root, int k){
    if(root==NULL) return NULL;

    int leftsize = getSize(root->left);
    if(leftsize+1 == k) return root;
    if(k<=leftsize) return findKthLargest(root->left, k);
    else
        return findKthLargest(root->right, k-leftsize-1);
}


MedianFinder* medianFinderCreate() {
    MedianFinder *mf = (MedianFinder *)malloc(sizeof(MedianFinder));
    if(mf==NULL) return NULL;

    mf->root = NULL;
    return mf;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    insertValue(obj, num);
}

double medianFinderFindMedian(MedianFinder* obj) {
    int totalsize = getSize(obj->root);
    if(totalsize%2 == 1){
        Node *temp = findKthLargest(obj->root, (totalsize+1)/2);
        return (double)temp->value;
    }
    else{
        Node *n1 = findKthLargest(obj->root, totalsize/2);
        Node *n2 = findKthLargest(obj->root, totalsize/2 + 1);
        double n1value = 0;
        double n2value = 0;
        if(n1!=NULL){
            n1value = (double)n1->value;
        }
        if(n2!=NULL){
            n2value = (double)n2->value;
        }
        return (n1value+n2value)/2.0;
    }
}

void freetree(Node* root){
    if(root==NULL) return;

    freetree(root->left);
    freetree(root->right);
}

void medianFinderFree(MedianFinder* obj) {
    freetree(obj->root);
    free(obj);
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 
 * double param_2 = medianFinderFindMedian(obj);
 
 * medianFinderFree(obj);
*/