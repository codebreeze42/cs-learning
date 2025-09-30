#include <iostream>
using namespace std;
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
};
TreeNode *CreateBinTree()
{
    int k;
    cin >> k;
    if (k == 0)
        return nullptr;
    TreeNode *root = new TreeNode;
    root->data = k;
    root->left = CreateBinTree();
    root->right = CreateBinTree();
    return root;
}
TreeNode *Search(TreeNode *root, int t)
{
    if (root == nullptr)
        return nullptr;
    if (root->data == t)
        return root;
    TreeNode *ans = Search(root->left, t);
    if (ans != nullptr)
        return ans;
    return Search(root->right, t);
}
TreeNode *FindFather(TreeNode *root, TreeNode *p)
{
    if (p == nullptr || p == root || root == nullptr)
        return nullptr;
    if (root->left == p || root->right == p)
        return root;
    TreeNode *ans = FindFather(root->left, p);
    if (ans != nullptr)
        return ans;
    return FindFather(root->right, p);
}
int main()
{
    TreeNode *root = CreateBinTree();
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        TreeNode *p = Search(root, m);
        TreeNode *father = FindFather(root, p);
        if (father == nullptr)
            cout << 0 << endl;
        else
            cout << father->data << endl;
    }
    return 0;
}