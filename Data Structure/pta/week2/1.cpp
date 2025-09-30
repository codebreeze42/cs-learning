#include <iostream>
#include <string.h>
using namespace std;
struct AVLnode
{
    int key;
    int height;
    AVLnode *left, *right;
    AVLnode(int K)
    {
        key = K;
        height = 0;
        left = right = NULL;
    }
};
int Height(AVLnode *t) { return (t == NULL) ? -1 : t->height; }
int max(int a, int b) { return (a > b) ? a : b; }
void UpdateHeight(AVLnode *t)
{
    t->height = max(Height(t->left), Height(t->right)) + 1;
}
void LL(AVLnode *&A)
{
    AVLnode *B = A->left;
    A->left = B->right;
    B->right = A;
    UpdateHeight(A);
    UpdateHeight(B);
    A = B;
}
void RR(AVLnode *&A)
{
    AVLnode *B = A->right;
    A->right = B->left;
    B->left = A;
    UpdateHeight(A);
    UpdateHeight(B);
    A = B;
}
void LR(AVLnode *&A)
{
    RR(A->left);
    LL(A);
}
void RL(AVLnode *&A)
{
    LL(A->right);
    RR(A);
}
void ReBalance(AVLnode *&t)
{
    if (t == NULL)
        return;
    if (Height(t->left) - Height(t->right) == 2)
    {
        if (Height(t->left->left) >= Height(t->left->right))
            LL(t);
        else
            LR(t);
    }
    else if (Height(t->right) - Height(t->left) == 2)
    {
        if (Height(t->right->right) >= Height(t->right->left))
            RR(t);
        else
            RL(t);
    }
    UpdateHeight(t);
}
void Insert(AVLnode *&root, int K)
{
    if (root == NULL)
        root = new AVLnode(K);
    else if (K < root->key)
        Insert(root->left, K);
    else if (K > root->key)
        Insert(root->right, K);
    ReBalance(root);
}
void remove(AVLnode *&root, int K)
{
    if (root == NULL)
        return;
    if (K < root->key)
        remove(root->left, K);
    else if (K > root->key)
        remove(root->right, K);
    else if (root->left != NULL && root->right != NULL)
    {
        AVLnode *s = root->right;
        while (s->left != NULL)
            s = s->left;
        root->key = s->key;
        remove(root->right, s->key);
    }
    else
    {
        AVLnode *oldroot = root;
        root = (root->left != NULL) ? root->left : root->right;
        delete oldroot;
    }
    ReBalance(root);
}

void visit(int data)
{
    printf("%d ", data);
}
void Preorder(AVLnode *root)
{
    if (root == NULL)
        return;
    visit(root->key);
    Preorder(root->left);
    Preorder(root->right);
}
void Inorder(AVLnode *root)
{
    if (root == NULL)
        return;
    Inorder(root->left);
    visit(root->key);
    Inorder(root->right);
}
int main()
{
    int T;
    char s[7];
    int k;
    AVLnode *root = nullptr;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        scanf("%s %d", s, &k);
        if (strcmp(s, "Insert") == 0)
        {
            Insert(root, k);
        }
        else if (strcmp(s, "Remove") == 0)
        {
            remove(root, k);
        }
    }
    Inorder(root);
    printf("\n\n");
    Preorder(root);
    return 0;
}