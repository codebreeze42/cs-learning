// 树的结点
#include <vector>
#include <iostream>
#include <Queue>
#include <Stack>
using namespace std;
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
};
// 遍历
vector<int> v1;
vector<int> preorderTraversal(TreeNode *root)
{

    if (root == nullptr)
        return;
    v1.push_back(root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
    return v1;
}

vector<int> inorderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return v1;
    inorderTraversal(root->left);
    v1.push_back(root->data);
    inorderTraversal(root->right);
    return v1;
}

vector<int> postorderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return v1;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    v1.push_back(root->data);
    return v1;
}

// 层次遍历
void LevelOrder(TreeNode *root)
{
    queue<TreeNode *> Q;
    if (root != nullptr)
        Q.push(root);
    while (!Q.empty())
    {
        Q.pop();
        cout << root->data << endl;
        if (root->left != nullptr)
            Q.push(root->left);
        if (root->right != nullptr)
            Q.push(root->right);
    }
}

// 搜索二叉树中符合数据域条件的结点
TreeNode *Search(TreeNode *root, int k)
{
    if (root = nullptr)
        return nullptr;
    if (root->data == k)
        return root;
    TreeNode *ans = Search(root->left, k);
    if (ans != nullptr)
        return ans;
    return Search(root->right, k);
}

// 在二叉树中搜索给定结点的父结点
TreeNode *FindParent(TreeNode *root, TreeNode *p)
{
    if (root == nullptr || p == root)
        return nullptr;
    if (root->left == p || root->right == p)
        return root;
    TreeNode *ans = FindParent(root->left, p);
    if (ans != nullptr)
        return ans;
    return FindParent(root->right, p);
}

// 计算二叉树结点个数
int Count(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    return Count(root->left) + Count(root->right) + 1;
}

// 计算二叉树的高度
int depth(TreeNode *root)
{
    if (root == nullptr)
        return -1;
    int d1 = depth(root->left);
    int d2 = depth(root->right);
    return (d1 > d2) ? d1 + 1 : d2 + 2;
}

// 删除二叉树
void Del(TreeNode *&root)
{
    if (root == nullptr)
        return;
    Del(root->left);
    Del(root->right);
    delete root;
    root = nullptr;
}

// 删除二叉树的子树
bool DeleteSubTree(TreeNode *&root, TreeNode *p)
{
    if (root == nullptr || p == nullptr)
        return false;
    if (p == root)
    {
        Del(root);
        return true;
    }
    if (DeleteSubTree(root->left, p))
        return true;
    return DeleteSubTree(root->right, p);
}

bool DeleteSubTree2(TreeNode *&root, TreeNode *p)
{
    if (root == nullptr || p == nullptr)
        return false;
    if (p == root)
    {
        Del(root);
        return true;
    }
    TreeNode *par = FindParent(root, p);
    if (par->left == p)
    {
        Del(par->left);
        return true;
    }
    if (par->right == p)
    {
        Del(par->right);
        return true;
    }
}

// 根据带空指针信息的先根序列创建二叉树，其中空指针信息用#表示，如ABD##E##C##
int k = 0;
TreeNode *CreateBinTree(char preorder[])
{
    char ch = preorder[k++];
    if (ch = '#')
        return nullptr;
    TreeNode *root = new TreeNode;
    root->data = ch;
    root->left = CreateBinTree(preorder);
    root->right = CreateBinTree(preorder);
    return root;
}

// 复制二叉树
TreeNode *CopyTree(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;
    TreeNode *newlptr = CopyTree(root->left);
    TreeNode *newrptr = CopyTree(root->right);
    TreeNode *newroot = new TreeNode;
    newroot->data = root->data;
    newroot->left = newlptr;
    newroot->right = newrptr;
    return newroot;
}

// 二叉树先、中、后根序列的首末结点

// 中根序列的第一个结点(往左遍历)
TreeNode *InFirst(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;
    TreeNode *p = root;
    while (p->left != nullptr)
        p = p->left;
    return p;
}
// 中根序列的最后一个结点（往右遍历）
TreeNode *InLast(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;
    TreeNode *p = root;
    while (p->right != nullptr)
        p = p->right;
    return p;
}
// 先根序列的第一个结点
TreeNode *PreF(TreeNode *root)
{
    return root;
}
// 先根序列的最后一个结点（先右后左）
TreeNode *PreL(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;
    TreeNode *p = root;
    while (p != nullptr)
    {
        if (p->right != nullptr)
            p = p->right;
        else if (p->left != nullptr)
            p = p->left;
        else
            return p;
    }
}

// 后根序列的第一个结点（先左后右）
TreeNode *PostF(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;
    TreeNode *p = root;
    while (p != nullptr)
    {
        if (p->left != nullptr)
            p = p->left;
        else if (p->right != nullptr)
            p = p->right;
        else
            return p;
    }
}

// 后根序列的最后一个结点
TreeNode *PostL(TreeNode *root)
{
    return root;
}

// 二叉树的重建（先根序列和中根序列）
int FindRoot(char *inorder, int size, char val)
{
    for (int i = 0; i < size; i++)
    {
        if (inorder[i] == val)
            return i;
    }
    return -1;
}

TreeNode *BuildTree(char *preorder, char *inorder, int size)
{
    if (size <= 0)
        return nullptr;
    TreeNode *root = new TreeNode;
    root->data = preorder[0];
    int k = FindRoot(inorder, size, root->data);
    root->left = BuildTree(&preorder[1], &inorder[0], k);
    root->right = BuildTree(&preorder[k + 1], &inorder[k + 1], size - k - 1);
    return root;
}

// 先根遍历的非递归算法
void PreOrder_NonRec(TreeNode *root)
{
    stack<TreeNode *> s;
    TreeNode *p = root;
    while (true)
    {
        while (p != nullptr)
        {
            cout << p->data;
            s.push(p);
            p = p->left;
        }
        if (s.empty())
            return;
        p = s.top();
        s.pop();
        p = p->right;
    }
}

// 中根遍历的非递归算法
void Inorder_NonRec(TreeNode *root)
{
    stack<TreeNode *> s;
    TreeNode *p = root;
    while (true)
    {
        while (p != nullptr)
        {
            s.push(p);
            p = p->left;
        }
        if (s.empty())
            return;
        p = s.top();
        cout << p->data;
        s.pop();
        p = p->right;
    }
}

// 后根遍历的非递归算法
void Post_NonRec(TreeNode *root)
{
    stack<TreeNode *> s;
    TreeNode *p = root, *pre = nullptr;
    while (true)
    {
        while (p != nullptr)
        {
            s.push(p);
            p = p->left;
        }
        if (s.empty())
            return;
        p = s.top();
        if (p->right == nullptr || p->right == pre)
        {
            s.pop();
            cout << p->data;
            pre = p;
            p = nullptr;
        }
        else
            p = p->right;
    }
}