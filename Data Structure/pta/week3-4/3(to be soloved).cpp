#include <iostream>
#include <stack>
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
void Rexp(string s)
{
    TreeNode *root = BuildExpTree(s);
    int dep = depth(root);
    int count = 0;
    TreeNode *p = root;
    TreeNode *pre = nullptr;
    cout << p->data;
    while (true)
    {
        if (p == nullptr || count == dep)
            break;

        if (p->right != nullptr)
        {
            pre = p;
            p = p->right;
            cout << p->data;
            // pre = p;
            count++;
        }
        else
        {
            p = pre->left;
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
        Rexp(s);
        cout << endl;
    }
    return 0;
}