#include <bits/stdc++.h>
using namespace std;
int main() 
{
    int a,b;
    cin >> a;
    for (int i = 0; i < a; i++)
    {
        cin >> b;
        unordered_set <int> A;
        for (int i = 0; i < b; i++)
        {
            char x;
            int y;
            cin >> x;
            if (x == 'a')
            {
                cin >> y;
                A.insert(y);
            }
            else if (x == 'b')
            {
                cin >> y;
                A.erase(y);
            }
            else if (x == 'c')
            {
                cin >> y;
                auto pos = A.find(y);
                if (pos != A.end())
                {
                    cout << 1;
                }
                else
                {
                    cout << -1;
                }
                cout << " ";
            }
            else if (x == 'd')
            {
                cout << A.size() << " ";
            }
            
        }
        cout << "\n";
    }
    
    return 0;
}