#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    if (cin >> t)
    {
        while (t--)
        {
            int n;
            cin >> n;

            vector<pair<long long, long long>> V;
            for (int i = 0; i < n; i++)
            {
                long long a, b;
                cin >> a >> b;
                V.push_back({a, b});
            }

            sort(V.begin(), V.end());

            long long sum = 0;
            long long start = V[0].first;
            long long end = V[0].second;

            for (int i = 1; i < n; i++)
            {
                if (V[i].first <= end)
                {
                    end = max(end, V[i].second);
                }
                else
                {
                    sum += (end - start);
                    start = V[i].first;
                    end = V[i].second;
                }
            }
            sum += (end - start);

            cout << sum << "\n";
        }
    }

    return 0;
}