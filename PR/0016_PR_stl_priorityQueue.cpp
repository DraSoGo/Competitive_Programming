#include <bits/stdc++.h>
using namespace std;
void showpq (priority_queue <int> d)
{
    stack <int> STR;
    if (!d.empty())
    {
        while (!d.empty())
        {
            cout << d.top() << " ";
            STR.push(d.top());
            d.pop();
        }
        while (!STR.empty())
        {
            d.push(STR.top());
            STR.pop();
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
        priority_queue <int> pq;
        for (int j = 0; j < m; j++)
        {
            cin >> a;
            if (a == 1)
            {
                cin >> b;
                pq.push(b);
                showpq(pq);
            }
            else if (a == 2)
            {
                cout << pq.top() << "\n";
                pq.pop();
            }
            else if (a == 3)
            {
                cout << pq.top() << "\n";
            }
            else if (a == 4)
            {
                cout << pq.size() << "\n";
            }
            else if (a == 5)
            {      
                showpq(pq);
            }
        }
    }
    return 0;
}