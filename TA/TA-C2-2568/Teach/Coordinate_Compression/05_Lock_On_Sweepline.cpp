#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, s, e, co = 0, p, ch = 0;
    vector<pair<int, int>> V;
    cin >> n >> p;
    for (int i = 0; i < n; i++)
    {
        cin >> s >> e;
        if (s > e)
        {
            swap(s, e);
        }
        V.push_back({s, 1});
        V.push_back({e, 2});
    }
    sort(V.begin(), V.end());
    int start = -1, end = -1;
    for (auto i : V)
    {
        if (i.second == 1)
        {
            co++;
            if (co == n)
            {
                start = i.first;
            }
        }
        else
        {
            co--;
            if (co == n-1 && start != -1)
            {
                end = i.first;
            }
        }
    }
    start == -1 ? cout << -1 : (p >= start && p <= end ? cout << 0 : cout << min(abs(start - p), abs(end - p)));
}
// https://programming.in.th/tasks/codecube_103