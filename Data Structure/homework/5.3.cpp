#include <iostream>
#include <queue>
using namespace std;
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
};
int sign = 1;
bool isComplete(TreeNode *root)
{
    queue<TreeNode *> Q;
    Q.push(root);
    while (!Q.empty())
    {
        TreeNode *node = Q.front();
        Q.pop();
        if (node)
        {
            if (sign = 0)
                return false;
            Q.push(node->left);
            Q.push(node->right);
        }
        else
        {
            sign = 0;
        }
        return true;
    }
}