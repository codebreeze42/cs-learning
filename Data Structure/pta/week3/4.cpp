#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct TrieNode
{
    bool isend;
    long long freq;
    vector<TrieNode *> children;
    TrieNode() : children(36, nullptr), isend(false), freq(0) {}
};
int getindex(char a)
{
    if (a >= 'a' && a <= 'z')
        return a - 'a' + 10;
    else
        return a - '0';
}
TrieNode *root = new TrieNode();
void init(string s, long long freq)
{
    TrieNode *cur = root;
    for (int i = 0; i < s.size(); i++)
    {
        int id = getindex(s[i]);
        if (!cur->children[id])
        {
            cur->children[id] = new TrieNode();
        }
        cur = cur->children[id];
    }
    if (freq > cur->freq)
    {
        cur->freq = freq;
    }
    cur->isend = true;
}
void findword(TrieNode *node, string prefix, string &cur, vector<pair<string, long long>> &result)
{
    if (!node)
        return;
    if (node->isend && cur != prefix)
        result.emplace_back(cur, node->freq);
    for (int i = 0; i < 36; i++)
    {
        if (node->children[i])
        {
            char a;
            if (i < 10)
                a = '0' + i;
            else
                a = i + 'a' - 10;
            cur.push_back(a);
            findword(node->children[i], prefix, cur, result);
            cur.pop_back();
        }
    }
}
bool compare(pair<string, long long> a, pair<string, long long> b)
{
    if (a.second != b.second)
        return a.second > b.second;
    else
        return a.first < b.first;
}
void output(string prefix, int k)
{
    vector<pair<string, long long>> result;
    TrieNode *node = root;
    for (int i = 0; i < prefix.size(); i++)
    {
        int id = getindex(prefix[i]);
        if (!node->children[id])
        {
            printf("no suggestion\n");
            return;
        }
        node = node->children[id];
    }
    string cur = prefix;
    findword(node, prefix, cur, result);
    if(result.empty()) {
        printf("no suggestion\n");
        return;
    }
    sort(result.begin(), result.end(), compare);
    int num = (k > result.size()) ? result.size() : k;
    for (int i = 0; i < num; i++)
    {
        printf("%s\n", result[i].first.c_str());
    }
}
bool firstline = true;
int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    char word[21];
    for (int i = 0; i < n; i++)
    {
        long long freq;
        scanf("%lld %s", &freq, word);
        init(string(word), freq);
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%s", word);
        if (!firstline)
            printf("\n");
        firstline = false;
        output(string(word), k);
    }
    return 0;
}