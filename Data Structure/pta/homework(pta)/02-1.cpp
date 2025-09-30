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
void visit(int data)
{
    cout << data << ' ';
}
void Preorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    visit(root->data);
    Preorder(root->left);
    Preorder(root->right);
}

void Inorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    Inorder(root->left);
    visit(root->data);
    Inorder(root->right);
}

void Postorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    Postorder(root->left);
    Postorder(root->right);
    visit(root->data);
}

int main()
{
    TreeNode *root = CreateBinTree();
    Preorder(root);
    cout << endl;
    Inorder(root);
    cout << endl;
    Postorder(root);
    cout << endl;
}