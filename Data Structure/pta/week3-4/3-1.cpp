#include <iostream>
#include <stack>
#include <queue>
using namespace std;
struct TreeNode
{
    char data;
    TreeNode *left;
    TreeNode *right;
};
TreeNode *BuildExpTree(string s)
{
    int size = s.size();
    stack<TreeNode *> stk;
    for (int i = 0; i < size; i++)
    {
        TreeNode *p = new TreeNode;
        p->data = s[i];
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            p->left = nullptr;
            p->right = nullptr;
        }
        else
        {
            p->right = stk.top();
            stk.pop();
            p->left = stk.top();
            stk.pop();
        }
        stk.push(p);
    }
    return stk.top();
}
int depth(TreeNode *root)
{
    if (root == nullptr)
        return -1;
    int d1 = depth(root->left);
    int d2 = depth(root->right);
    return (d1 > d2) ? d1 + 1 : d2 + 1;
}
void Rexp(TreeNode *root)
{
    queue<TreeNode *> Q;
    if (root != nullptr)
        Q.push(root);
    while (!Q.empty())
    {
        int size = Q.size();
        for (int i = 0; i < size; i++)
        {
            TreeNode *p = Q.front();
            if (i == size - 1)
                cout << p->data;
            Q.pop();
            if (p->left != nullptr)
                Q.push(p->left);
            if (p->right != nullptr)
                Q.push(p->right);
        }
    }
}

int main()
{
    string s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        TreeNode *root = BuildExpTree(s);
        Rexp(root);
        cout << endl;
    }
    return 0;
}