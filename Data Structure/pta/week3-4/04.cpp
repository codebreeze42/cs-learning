#include <iostream>
#include <string>
using namespace std;
char ch[26] = {0};
int freq[26] = {0};
bool appear[26] = {false};
int index_ch = 0;
int cnt = 0;
struct HuffmanNode
{
    char data;
    int weight;
    HuffmanNode *left;
    HuffmanNode *right;
};
void createArray(char ch[], int freq[], string s)
{
    int size = s.size();
    for (int i = 0; i < size; i++)
    {
        freq[s[i] - 'a']++;
        if (!appear[s[i] - 'a'])
        {
            ch[index_ch++] = s[i];
            appear[s[i] - 'a'] = true;
            cnt++;
        }
    }
}

HuffmanNode *H[26];
void sort(HuffmanNode *H[], int cnt)
{
    for (int i = 1; i < cnt; i++)
    {
        HuffmanNode *current = H[i];
        int j = i - 1;
        while (j >= 0 && H[j]->weight > current->weight)
        {
            H[j + 1] = H[j];
            j--;
        }
        H[j + 1] = current;
    }
}
int getIndex(char c)
{
    for (int i = 0; i < cnt; i++)
    {
        if (ch[i] == c)
            return i;
    }
    return -1;
}
void CreateHuffmanNode(char ch[], int freq[], int cnt)
{
    for (int i = 0; i < cnt; i++)
    {
        H[i] = new HuffmanNode;
        H[i]->data = ch[i];
        H[i]->weight = freq[ch[i] - 'a'];
        H[i]->left = H[i]->right = nullptr;
    }
    sort(H, cnt);
}
bool isSingle(HuffmanNode *node)
{
    if (node->left == nullptr && node->right == nullptr)
        return true;
    else
        return false;
}
bool order(HuffmanNode *a, HuffmanNode *b)
{
    if (a->weight != b->weight)
        return a->weight < b->weight;
    bool a_single = isSingle(a);
    bool b_single = isSingle(b);
    if (a_single != b_single)
        return a_single;
    else if (a_single && b_single)
        return getIndex(a->data) < getIndex(b->data);
    else
        return true;
}
HuffmanNode *BuildHuffmanTree(HuffmanNode *H[], int cnt)
{
    for (int i = 0; i < cnt - 1; i++)
    {
        HuffmanNode *t = new HuffmanNode;
        t->left = H[i];
        t->right = H[i + 1];
        t->weight = t->left->weight + t->right->weight;
        int j = i + 2;
        while (j < cnt && order(H[j], t))
        {
            H[j - 1] = H[j];
            j++;
        }
        H[j - 1] = t;
    }
    return H[cnt - 1];
}
string code = "";
string codes[26] = {""};
void huffmanCode(HuffmanNode *root, string code)
{
    if (root == nullptr)
        return;
    if (root->left == nullptr && root->right == nullptr)
        codes[root->data - 'a'] = code;
    huffmanCode(root->left, code + "0");
    huffmanCode(root->right, code + "1");
}

string decodeHuffmanCode(HuffmanNode *root, string s)
{
    int size = s.size();
    string result = "";
    HuffmanNode *current = root;
    for (int i = 0; i < size; i++)
    {
        if (s[i] == '0')
        {
            if (current->left != nullptr)
                current = current->left;
            else
                return "INBALID";
        }
        else
        {
            if (current->right != nullptr)
                current = current->right;
            else
                return "INVALID";
        }
        if (current->left == nullptr && current->right == nullptr)
        {
            result += current->data;
            current = root;
        }
    }
    if (current != root)
        return "INVALID";
    return result;
}

int main()
{
    string s, temp1, temp2;
    cin >> s;
    cin >> temp1;
    cin >> temp2;
    int s_bytes = s.size();
    createArray(ch, freq, s);
    CreateHuffmanNode(ch, freq, cnt);
    char ch2[26] = {0};
    for (int i = 0; i < cnt; i++)
    {
        ch2[i] = H[i]->data;
    }
    HuffmanNode *root = BuildHuffmanTree(H, cnt);
    huffmanCode(root, code);
    long long codes_bits = 0;
    for (int i = 0; i < cnt; i++)
    {
        int length = codes[ch[i] - 'a'].size();
        codes_bits += freq[ch[i] - 'a'] * length;
    }
    long long codes_bytes = (codes_bits % 8 == 0) ? codes_bits / 8 : codes_bits / 8 + 1;
    cout << s_bytes << " " << codes_bytes << endl;
    for (int i = 0; i < cnt; i++)
    {

        cout << ch2[i] << ":" << codes[ch2[i] - 'a'] << endl;
    }
    string result1 = decodeHuffmanCode(root, temp1);
    cout << result1 << endl;
    string result2 = decodeHuffmanCode(root, temp2);
    cout << result2 << endl;
    return 0;
}