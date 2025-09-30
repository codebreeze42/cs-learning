#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
bool firstline = true;
map<string, long long> wordmap;
map<string, vector<pair<string, long long>>> prefix_map;
// struct word
// {
//     string w;
//     long long freq;
//     word(string w, long long freq) : w(w), freq(freq) {}
// };
// vector<word> words;
bool compare(pair<string, long long> a, pair<string, long long> b)
{
    if (a.second != b.second)
        return a.second > b.second;
    else
        return a.first < b.first;
}
// bool compare(word a, word b)
// {
//     if (a.freq != b.freq)
//         return a.freq > b.freq;
//     else
//         return a.w < b.w;
// }
bool isSub(string str, string sub)
{
    if (sub.size() >= str.size())
        return false;
    int len = sub.size();
    for (int i = 0; i < len; i++)
    {
        if (str[i] != sub[i])
            return false;
    }
    return true;
}
void init(long long freq, string s)
{
    // bool sign = false;
    if (wordmap.find(s) == wordmap.end())
    {
        wordmap[s] = freq;
    }
    else
        wordmap[s] = max(wordmap[s], freq);
    // for (unsigned int j = 0; j < words.size(); j++)
    // {
    //     if (s == words[j].w)
    //     {
    //         words[j].freq = max(words[j].freq, freq);
    //         sign = true;
    //         break;
    //     }
    // }
    // if (!sign)
    // {
    //     word w = word(s, freq);
    //     words.push_back(w);
    // }
}
void output(string t, int k)
{
    vector<pair<string, long long>> suggestion;
    // vector<word> suggestion;
    // suggestion.reserve(k);
    if (prefix_map.find(t) != prefix_map.end())
    {
        vector<pair<string, long long>> list = prefix_map.find(t)->second;
        if (list.empty())
        {
            printf("no suggestion\n");
        }
        else
        {
            int a = list.size();
            int b = min(a, k);
            for (int j = 0; j < b; j++)
            {
                printf("%s\n", list[j].first.c_str());
            }
        }
    }
    else
    {
        for (map<string, long long>::const_iterator it = wordmap.begin(); it != wordmap.end(); it++)
        {
            if (isSub(it->first, t))
                suggestion.emplace_back(*it);
        }
        // int cnt = 0;
        // for (unsigned int j = 0; j < words.size(); j++)
        // {
        //     if (isSub(words[j].w, t))
        //     {
        //         suggestion.push_back(words[j]);
        //         cnt++;
        //         if (cnt == k)
        //             break;
        //     }
        // }

        if (suggestion.empty())
        {
            prefix_map[t] = suggestion;
            printf("no suggestion\n");
        }
        else
        {
            sort(suggestion.begin(), suggestion.end(), compare);
            prefix_map[t] = suggestion;
            int a = suggestion.size();
            int b = min(a, k);
            for (int j = 0; j < b; j++)
            {
                printf("%s\n", suggestion[j].first.c_str());
                // cout << suggestion[j].w << endl;
            }
        }
    }
}
int main()
{
    int m, n, k;
    scanf("%d %d %d", &n, &m, &k);
    // cin >> n >> m >> k;
    // words.reserve(n);
    for (int i = 0; i < n; i++)
    {
        long long freq;
        // string s;
        char s[21];
        scanf("%lld %s", &freq, s);
        // cin >> freq >> s;
        init(freq, string(s));
    }
    // sort(words.begin(), words.end(), compare);
    for (int i = 0; i < m; i++)
    {
        if (!firstline)
        {
            printf("\n");
        }
        firstline = false;
        char t[21];
        scanf("%s", t);
        output(string(t), k);
        // string t;
        // cin >> t;
        // output(t, k);
    }
    return 0;
}