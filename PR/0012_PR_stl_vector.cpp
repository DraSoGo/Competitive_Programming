#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int m,b;
        char a;
        cin >> m;
        vector <int> s;
        queue <int> re;
        for (int j = 0; j < m; j++)
        {
            cin >> a;
            if (a == 'a')
            {
                cin >> b;
                s.push_back(b);
            }
            else if (a == 'b')
            {
                sort(s.begin(),s.end());
            }
            else if (a == 'c')
            {
                while (!s.empty())
                {
                    re.push(s.back());
                    s.pop_back();
                }
                while (!re.empty())
                {
                    s.push_back(re.front());
                    re.pop();
                }
            }
            else if (a == 'd')
            {
                cout << s.size() << " ";
            }
            else if (a == 'e')
            {
                for (int i = 0; i < s.size(); i++)
                {
                    cout << s[i] << " ";
                }
                
            }
            else if (a == 'f')
            {
                sort(s.begin(),s.end(),greater<int>());
            }
        }
        cout << "\n";
    }
}