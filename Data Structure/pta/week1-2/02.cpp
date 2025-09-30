#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s, t = "";
    getline(cin, s);
    int n = s.size();
    int point = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] != '}' && s[i] != '{' && s[i] != '<' && s[i] != '>' && s[i] != '#')
        {
            t.insert(point, 1, s[i]);
            point++;
        }
        else if (s[i] == '}')
            point = t.size();
        else if (s[i] == '{')
            point = 0;
        else if (s[i] == '<')
        {
            if (point > 0)
                point--;
        }
        else if (s[i] == '>')
        {
            if (point < t.size())
                point++;
        }
        else if (s[i] == '#')
        {
            if (point > 0)
            {
                t.erase(point - 1, 1);
                point--;
            }
        }
    }
    cout << t;
    return 0;
}