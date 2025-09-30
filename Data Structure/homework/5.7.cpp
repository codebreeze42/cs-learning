#include <algorithm>
using namespace std;
struct Tree
{
    int data;
    Tree *LeftChild;
    Tree *RightSibling;
};
int depth_tree(Tree *root)
{
    if (root == nullptr)
        return 0;
    else
        return max(depth_tree(root->LeftChild) + 1, depth_tree(root->RightSibling));
}