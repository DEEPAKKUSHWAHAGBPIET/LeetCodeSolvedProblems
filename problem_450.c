/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* inorderSuccessor(struct TreeNode* root){
    struct TreeNode* curr = root;
    while(curr && curr->left!=NULL) curr = curr->left;
    return curr;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if(root==NULL) return NULL;

    if(key<root->val){
        root->left = deleteNode(root->left, key);
        return root;
    }
    else if(key>root->val){
        root->right = deleteNode(root->right, key);
        return root;
    }
    else{
        if(root->left==NULL){
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        if(root->right==NULL){
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* successor = inorderSuccessor(root->right);
        root->val = successor->val;
        root->right = deleteNode(root->right, successor->val);
    }
    return root;
}