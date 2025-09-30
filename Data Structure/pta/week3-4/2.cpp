#include <iostream>
using namespace std;
bool isInvalid = false;
struct TreeNode
{
    char data;
    TreeNode *left;
    TreeNode *right;
};
int findroot(string inorder, int size, char val)
{
    for (int i = 0; i < size; i++)
        if (inorder[i] == val)
            return i;
    isInvalid = true;
    return -1;
}
TreeNode *buildTree(string postorder, string inorder, int n)
{
    if (n <= 0 || isInvalid)
    {
        isInvalid = true;
        return nullptr;
    }
    TreeNode *root = new TreeNode;
    root->data = postorder[n - 1];
    int k = findroot(inorder, n, root->data);
    if (isInvalid)
    {
        return nullptr;
    }
    root->left = buildTree(&postorder[0], &inorder[0], k);
    root->right = buildTree(&postorder[k], &inorder[k + 1], n - k - 1);
    return root;
}
void preorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    cout << root->data;
    preorder(root->left);
    preorder(root->right);
}
int depth(TreeNode *root)
{
    if (root == nullptr)
        return -1;
    int d1 = depth(root->left);
    int d2 = depth(root->right);
    return (d1 > d2) ? d1 + 1 : d2 + 1;
}
int main()
{
    string inorder, postorder;
    while (true)
    {
        isInvalid = false;
        getline(cin, postorder);
        if (postorder.empty())
            break;
        getline(cin, inorder);
        int size = inorder.size();
        TreeNode *root = buildTree(postorder, inorder, size);
        if (isInvalid)
        {
            cout << "INVALID" << endl;
        }
        else
        {
            cout << depth(root) << endl;
            preorder(root);
            cout << endl;
        }
    }
    return 0;
}