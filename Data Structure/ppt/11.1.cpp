#include <iostream>
using namespace std;
// 线索二叉树
struct TreeNode
{
    int data;
    int LThread;
    int RThread;
    TreeNode *left;
    TreeNode *right;
};

// 找中根序列的最后一个结点
TreeNode *LastInOrder(TreeNode *root)
{
    TreeNode *p = root;
    while (p->RThread == 0)
    {
        p = p->right;
    }
    return p;
}
// 在中序线索二叉树中，查找结点p的中根前驱结点
TreeNode *PreInOrder(TreeNode *p)
{
    if (p->LThread == 1)
        return p->left;
    else
        return LastInOrder(p->left);
}

// 找中根序列的第一个结点
TreeNode *FirstInOrder(TreeNode *root)
{
    TreeNode *p = root;
    while (p->LThread == 0)
    {
        p = p->left;
    }
    return p;
}
// 在中序线索二叉树中，查找结点p的中根后继结点
TreeNode *NextInOrder(TreeNode *p)
{
    if (p->RThread == 1)
        return p->right;
    else
        return FirstInOrder(p->right);
}
// 中序线索二叉树的中根遍历
void InOrder(TreeNode *root)
{
    for (TreeNode *p = FirstInOrder(root); p != nullptr; p = NextInOrder(p))
    {
        cout << p->data;
    }
}