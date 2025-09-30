#include <iostream>
#include <string.h>
#include <string>
using namespace std;
bool sign = false;
bool firstline = true;
bool havefirst = false;
int pre = -1;
string prestr = "";
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
AVLnode *root1 = nullptr;
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
int getLevel(AVLnode *root, int key)
{
    int level = 0;
    AVLnode *cur = root;
    while (cur != nullptr)
    {
        if (cur->key == key)
            return level;
        if (key < cur->key)
            cur = cur->left;
        else
            cur = cur->right;
        level++;
    }
    return -1;
}
// int getLevel(AVLnode *root, int key, int level = 0)
// {
//     if (root == NULL)
//         return -1;
//     if (root->key == key)
//         return level;
//     int left = getLevel(root->left, key, level + 1);
//     if (left != -1)
//         return left;
//     return getLevel(root->right, key, level + 1);
// }
void output(int k, string s)
{
    havefirst = true;
    if (pre == k && prestr == s)
    {
        printf("Rebalance subtree rooted at node ");
    }
    else
    {
        if (firstline == false)
            printf("\n");
        firstline = false;
        cout << s << " " << k << ": " << "Rebalance subtree rooted at node ";
    }
    prestr = s;
    pre = k;
    sign = true;
}
void ReBalance(AVLnode *&t, int k, string s)
{
    if (t == NULL)
        return;
    int flag = 0;
    if (Height(t->left) - Height(t->right) == 2)
    {
        output(k, s);
        printf("%d", t->key);
        printf(" on level %d ", getLevel(root1, t->key));
        if (Height(t->left->left) >= Height(t->left->right))
        {

            // printf(" on level %d ", Height(t));
            LL(t);
            flag = 1;
        }
        else
        {
            // printf(" on level %d ", Height(t));
            LR(t);
            flag = 2;
        }
    }
    else if (Height(t->right) - Height(t->left) == 2)
    {
        output(k, s);
        printf("%d", t->key);
        printf(" on level %d ", getLevel(root1, t->key));
        if (Height(t->right->right) >= Height(t->right->left))
        {
            // printf(" on level %d ", Height(t));
            RR(t);
            flag = 3;
        }
        else
        {
            // printf(" on level %d ", Height(t));
            RL(t);
            flag = 4;
        }
    }
    UpdateHeight(t);

    if (flag == 1)
        printf("with right rotation. ");
    else if (flag == 2)
        printf("with left rotation and right rotation. ");
    else if (flag == 3)
        printf("with left rotation. ");
    else if (flag == 4)
        printf("with right rotation and left rotation. ");
}

void Insert(AVLnode *&root, int K)
{
    if (root == NULL)
        root = new AVLnode(K);
    else if (K < root->key)
        Insert(root->left, K);
    else if (K > root->key)
        Insert(root->right, K);
    else
        return;
    ReBalance(root, K, "Insert");
}
void remove(AVLnode *&root, int K, int K1)
{
    if (root == NULL)
        return;
    if (K < root->key)
    {
        remove(root->left, K, K1);
        UpdateHeight(root);
        ReBalance(root, K1, "Remove");
    }

    else if (K > root->key)
    {
        remove(root->right, K, K1);
        UpdateHeight(root);
        ReBalance(root, K1, "Remove");
    }

    else if (root->left != NULL && root->right != NULL)
    {
        AVLnode *s = root->right;
        while (s->left != NULL)
            s = s->left;
        root->key = s->key;
        remove(root->right, s->key, K1);

        UpdateHeight(root);
        ReBalance(root, K1, "Remove");

        return;
    }
    else
    {
        AVLnode *oldroot = root;
        root = (root->left != NULL) ? root->left : root->right;
        delete oldroot;
    }
    if (root != nullptr)
    {
        UpdateHeight(root);
        ReBalance(root, K1, "Remove");
    }
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
    int count = 1;
    // scanf("%d", &T);
    while (cin >> T)
    {
        havefirst = false;
        firstline = true;
        sign = false;
        root1 = nullptr;
        if (count != 1)
            printf("\n");
        printf("Case %d:\n", count);
        count++;
        for (int i = 0; i < T; i++)
        {
            scanf("%s %d", s, &k);
            if (strcmp(s, "Insert") == 0)
            {
                Insert(root1, k);
            }
            else if (strcmp(s, "Remove") == 0)
            {
                remove(root1, k, k);
            }
        }
        if (sign == true)
            printf("\n");
        if (havefirst == true)
            printf("\n");
        Inorder(root1);
        printf("\n\n");
        Preorder(root1);
        printf("\n");
    }

    return 0;
}