/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool helper(long mini, long maxi, struct TreeNode* root){
    if(root==NULL) return true;
    if(root->val <= mini || root->val >= maxi) return false;
    return helper(mini, root->val, root->left) && helper(root->val, maxi, root->right);
}
bool isValidBST(struct TreeNode* root) {
   if(root->left==NULL && root->right==NULL) return true;
   return helper(LONG_MIN, LONG_MAX, root);
}