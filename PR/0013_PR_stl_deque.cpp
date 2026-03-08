#include <bits/stdc++.h>
using namespace std;
void showdq (deque <int> d)
{
    deque <int> :: iterator it;
    if (!d.empty())
    {
        for (it = d.begin(); it != d.end(); ++it)
        {
            cout << *it << " ";
        }
    }
    else
    {
        cout << -1;
    }
    
    
    cout << "\n";
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int m,b;
        int a;
        cin >> m;
        deque <int> de;
        queue <int> re;
        for (int j = 0; j < m; j++)
        {
            cin >> a;
            if (a == 1)
            {
                cin >> b;
                de.push_front(b);
                showdq(de);
            }
            else if (a == 2)
            {
                cin >> b;
                de.push_back(b);
                showdq(de);

            }
            else if (a == 3)
            {
                if (!de.empty())
                {
                    de.pop_front();
                    showdq(de);
                }
                else
                {
                    cout << -1 << "\n";
                }
            }
            else if (a == 4)
            {
                if (!de.empty())
                {
                    de.pop_back();
                    showdq(de);
                }
                else
                {
                    cout << -1 << "\n";
                }
            }
            else if (a == 5)
            {
                if (!de.empty())
                {
                    sort(de.begin(),de.end());          
                    showdq(de);
                }
                else
                {
                    cout << -1 << "\n";
                }
            }
            else if (a == 6)
            {
                while (!de.empty())
                {
                    re.push(de.back());
                    de.pop_back();
                }
                while (!re.empty())
                {
                    de.push_back(re.front());
                    re.pop();
                }
                showdq(de);
            }
            else if (a == 7)
            {
                if (!de.empty())
                {
                    showdq(de);
                }
                else
                {
                    cout << -1 << "\n";
                }
            }
            else if (a == 8)
            {
                cout << de.size() << "\n";
            }
            else if (a == 9)
            {
                if (!de.empty())
                {
                    cout << de.front() << "\n";
                }
                else
                {
                    cout << -1 << "\n";
                }
                
            }
            else if (a == 10)
            {
                if (!de.empty())
                {
                    cout << de.back() << "\n";
                }
                else
                {
                    cout << -1 << "\n";
                }
            }
        }
    }
    return 0;
}