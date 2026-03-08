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
        set <int> s;
        for (int j = 0; j < m; j++)
        {
            cin >> a;
            if (a == 'a')
            {
                cin >> b;
                s.insert(b);
            }
            else if (a == 'b')
            {
                set <int> :: iterator itr;
                for (itr = s.begin(); itr != s.end();++itr)
                {
                    cout << *itr << " ";
                }
            }
            else if (a == 'c')
            {
                cin >> b;
                s.erase(b);
            }
            else if (a == 'd')
            {
                cin >> b;
                auto pos = s.find(b);
                if (pos != s.end())
                    cout << 1 << " ";
                else
                    cout << -1 << " ";
                
            }
            else if (a == 'e')
            {
                cout << s.size() << " ";
            }
        }
        cout << "\n";
    }
}