#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
bool firstline = true;
struct word
{
    string w;
    long long freq;
    word(string w, long long freq) : w(w), freq(freq) {}
};
vector<word> words;
bool compare(word a, word b)
{
    if (a.freq != b.freq)
        return a.freq > b.freq;
    else
        return a.w < b.w;
}
bool isSub(string str, string sub)
{
    if (sub.size() >= str.size())
        return false;
    else
        return str.substr(0, sub.size()) == sub;
}
void init(long long freq, string s)
{
    bool sign = false;
    for (unsigned int j = 0; j < words.size(); j++)
    {
        if (s == words[j].w)
        {
            words[j].freq = max(words[j].freq, freq);
            sign = true;
            break;
        }
    }
    if (!sign)
    {
        word w = word(s, freq);
        words.push_back(w);
    }
}
void output(string t, int k)
{
    vector<word> suggestion;
    for (unsigned int j = 0; j < words.size(); j++)
    {
        if (isSub(words[j].w, t))
            suggestion.push_back(words[j]);
    }
    if (suggestion.empty())
        printf("no suggestion\n");
    else
    {
        sort(suggestion.begin(), suggestion.end(), compare);
        int a = suggestion.size();
        int b = min(a, k);
        for (int j = 0; j < b; j++)
        {
            printf("%s\n", suggestion[j].w.c_str());
            // cout << suggestion[j].w << endl;
        }
    }
}
int main()
{
    int m, n, k;
    scanf("%d %d %d", &n, &m, &k);
    // cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        long long freq;
        // string s;
        char s[100];
        scanf("%lld %s", &freq, s);
        // cin >> freq >> s;
        init(freq, string(s));
    }
    for (int i = 0; i < m; i++)
    {
        if (!firstline)
        {
            printf("\n");
        }
        firstline = false;
        char t[100];
        scanf("%s", t);
        output(string(t), k);
        // string t;
        // cin >> t;
        // output(t, k);
    }
    return 0;
}