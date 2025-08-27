/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int findHeight(struct TreeNode* root){
    if(root==NULL) return 0;
    int lh = findHeight(root->left);
    int rh =  findHeight(root->right);

    return 1 + (lh>rh?lh:rh);
}

int findBalancefactor(struct TreeNode* root){
    if(root==NULL) return true;

    return findHeight(root->left) - findHeight(root->right);
}

struct TreeNode* createNode(int value){
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if(newNode==NULL) return NULL;

    newNode->val = value;
    newNode->left = newNode->right = NULL;

    return newNode;
}

struct TreeNode* leftRotate(struct TreeNode* x){
    struct TreeNode* y = x->right;
    struct TreeNode* t = y->left;

    y->left = x;
    x->right = t;

    return y;
}

struct TreeNode* rightRotate(struct TreeNode* x){
    struct TreeNode* y = x->left;
    struct TreeNode* t = y->right;

    y->right = x;
    x->left = t;

    return y;
    
}

struct TreeNode* insertInBST(struct TreeNode* root, int value){
    if(root==NULL) return createNode(value);

    if(value<root->val){
        root->left = insertInBST(root->left, value);
    }
    else if(value>root->val){
        root->right = insertInBST(root->right, value);
    }
    else{
        return root;
    }

    int balance = findBalancefactor(root);

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

struct TreeNode* sortedListToBST(struct ListNode* head) {
    struct ListNode* curr = head;
    struct TreeNode* root = NULL;
    while(curr){
        root = insertInBST(root, curr->val);
        curr = curr->next;
    }
    return root;
}