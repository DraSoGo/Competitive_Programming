#include <bits/stdc++.h>
using namespace std;

int const sz = 4010;
int DP[sz][sz];
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, ans = 0, id = 0;
    cin >> n;
    int B[n], A[n];
    map<int, int> MP;
    for (int i = 0; i < n; i++)
    {
        cin >> B[i];
        if (MP.find(B[i]) == MP.end())
        {
            MP[B[i]] = id;
            id++;
        }
    }
    int m = MP.size();
    for (int i = 0; i < n; i++)
    {
        A[i] = MP[B[i]];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int u = A[i], v = j;
            if (u == v)
            {
                DP[v][v]++;
                ans = max(ans, DP[v][v]);
            }
            else if (DP[u][v] > 0)
            {
                DP[v][u] = DP[u][v] + 1;
                ans = max(ans, DP[v][u]);
            }
            else if (DP[v][v] > 0)
            {
                DP[v][u] = 2;
                ans = max(ans, DP[v][u]);
            }
        }
    }
    cout << ans;
    return 0;
}