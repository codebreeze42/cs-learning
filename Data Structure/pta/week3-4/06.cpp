#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int max_sum = 0, maxlen = 0;
int maxpath[100] = {0};
int current_sum = 0, current_len = 0;
int current_path[100] = {0};
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
void PreOrder(TreeNode *root)
{

    if (root == nullptr)
        return;
    if (current_sum > 0)
    {
        current_sum += root->data;
        current_len++;
        current_path[current_len - 1] = root->data;
    }
    else
    {
        current_sum = root->data;
        current_len = 1;
        current_path[current_len - 1] = root->data;
    }
    if ((current_sum > max_sum) || (current_sum == max_sum && current_len < maxlen))
    {
        max_sum = current_sum;
        maxlen = current_len;
        copy(begin(current_path), end(current_path), maxpath);
    }
    int temp_sum = current_sum;
    int temp_len = current_len;
    int temp_path[100] = {0};
    copy(begin(current_path), end(current_path), temp_path);
    PreOrder(root->left);
    current_sum = temp_sum;
    current_len = temp_len;
    copy(begin(temp_path), end(temp_path), current_path);
    PreOrder(root->right);
}
int main()
{
    TreeNode *root = CreateBinTree();
    PreOrder(root);
    cout << max_sum << endl;
    for (int i = 0; i < maxlen; i++)
    {

        cout << maxpath[i] << " ";
    }
    cout << endl;
    return 0;
}