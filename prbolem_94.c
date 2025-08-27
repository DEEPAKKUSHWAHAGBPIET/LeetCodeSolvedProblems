/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void solve(struct TreeNode* root, int *ans, int *count){
    if(root==NULL) return;
    
    solve(root->left, ans, count);
    ans[*count] = root->val;
    *count += 1;
    solve(root->right, ans, count);
}
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int *ans = malloc(sizeof(int)*101);
    int count = 0;
    solve(root, ans, &count);
    *returnSize = count;
    return ans;

}