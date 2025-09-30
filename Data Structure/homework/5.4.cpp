#include <iostream>
using namespace std;
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
};
int depth(TreeNode *root)
{
    if (root == nullptr)
        return -1;
    int left = depth(root->left);
    int right = depth(root->right);
    return (left > right) ? left + 1 : right + 1;
}
void longestPath(TreeNode *root)
{
    if (root == nullptr)
        return;
    printf("%d ", root->data);
    int left = depth(root->left);
    int right = depth(root->right);
    if (left >= right)
        longestPath(root->left);
    else
        longestPath(root->right);
}