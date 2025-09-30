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
    int n;
    cin >> n;
    if (n == 0)
        return nullptr;
    TreeNode *root = new TreeNode;
    root->data = n;
    root->left = CreateBinTree();
    root->right = CreateBinTree();
    return root;
}
TreeNode *Search(TreeNode *root, int k)
{
    if (root == nullptr)
        return nullptr;
    if (root->data == k)
        return root;
    TreeNode *ans = Search(root->left, k);
    if (ans != nullptr)
        return ans;
    return Search(root->right, k);
}
void Del(TreeNode *&root)
{
    if (root == nullptr)
        return;
    Del(root->left);
    Del(root->right);
    delete root;
    root = nullptr;
}
void DeleteSubTree(TreeNode *&root, TreeNode *p)
{
    if (root == nullptr || p == nullptr)
        return;
    if (p == root)
    {
        Del(root);
        return;
    }
    DeleteSubTree(root->left, p);
    DeleteSubTree(root->right, p);
    return;
}
void visit(int data)
{
    cout << data << " ";
}
void Inorder(TreeNode *root)
{
    if (root == nullptr)
    {

        return;
    }
    Inorder(root->left);
    visit(root->data);
    Inorder(root->right);
}

int main()
{
    TreeNode *root = CreateBinTree();
    int m, k;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> k;
        TreeNode *p = Search(root, k);
        if (p == nullptr)
            cout << 0;
        else
        {
            DeleteSubTree(root, p);
            Inorder(root);
        }
        cout << endl;
    }
    return 0;
}