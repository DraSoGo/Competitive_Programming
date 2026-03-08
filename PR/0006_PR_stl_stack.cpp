#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c;
    char d;
    cin >> a;
    for (int i = 0; i < a; i++)
    {
        stack <int> STR;
        cin >> b;
        for (int j = 0; j < b; j++)
        {
            cin >> d;
            if (d == 'a')
            {
                cin >> c;
                STR.push(c);
            }
            else if (d == 'b')
            {
                if (!STR.empty())
                {
                    cout << STR.top() << " ";
                    STR.pop();
                }
                else
                {
                    cout << -1 << " ";
                }
            }
            else if (d == 'c')
            {
                cout << STR.size() << " ";
            }
            else if (d == 'd')
            {
                if (!STR.empty())
                {
                    cout << STR.top() << " ";
                }
                else
                {
                    cout << -1 << " ";
                }
            }

        }
        cout << "\n";
    }
}