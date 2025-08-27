/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void inorder(struct TreeNode* root, int *arr, int *size){
    if(root==NULL) return;
    
    inorder(root->left, arr, size);
    arr[(*size)++] = root->val;
    inorder(root->right, arr, size);
}

struct TreeNode* buildbst(int *arr, int start, int end){
    if(start>end) return NULL;

    int mid = start + (end-start)/2;
    struct TreeNode* newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if(newNode==NULL) return NULL;

    newNode->val = arr[mid];
    newNode->left = buildbst(arr, start, mid-1);
    newNode->right = buildbst(arr, mid+1, end);

    return newNode;
}
struct TreeNode* balanceBST(struct TreeNode* root) {
    int arr[10002];
    int size = 0;
    inorder(root, arr, &size);

    return buildbst(arr, 0, size-1);
}