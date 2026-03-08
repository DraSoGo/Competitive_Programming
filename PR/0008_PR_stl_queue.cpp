#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c;
    char d;
    cin >> a;
    for (int i = 0; i < a; i++)
    {
        queue <int> QU;
        cin >> b;
        for (int j = 0; j < b; j++)
        {
            cin >> d;
            if (d == 'a')
            {
                cin >> c;
                QU.push(c);
            }
            else if (d == 'b')
            {
                if (!QU.empty())
                {
                    cout << QU.front() << " ";
                    QU.pop();
                }
                else
                {
                    cout << -1 << " ";
                }
            }
            else if (d == 'c')
            {
                cout << QU.size() << " ";
            }
            else if (d == 'd')
            {
                if (!QU.empty())
                {
                    cout << QU.front() << " ";
                }
                else
                {
                    cout << -1 << " ";
                }
            }
            else if (d == 'e')
            {
                if (!QU.empty())
                {
                    cout << QU.back() << " ";
                }
                else
                {
                    cout << -1 << " ";
                }
            }
        }
        while (!QU.empty())
        {
            QU.pop();
        }
        cout << "\n";
    }
}