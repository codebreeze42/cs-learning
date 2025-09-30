#include <iostream>
using namespace std;
struct BSTnode
{
    int key;
    BSTnode *left;
    BSTnode *right;
    BSTnode(int K)
    {
        key = K;
        left = right = NULL;
    }
};
bool isBSTnode(BSTnode *root, int lower, int upper)
{
    if (root == nullptr)
        return true;
    int mid = root->key;
    return (isBSTnode(root->left, lower, mid) && isBSTnode(root->right, mid, upper));
}