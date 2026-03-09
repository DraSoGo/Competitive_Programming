#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,k;
    cin >> n >> k;
    int A[n],DP[n+1];
    memset(DP, 0, sizeof(DP));
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }
    DP[0] = 0;
    for (int i = 1; i <= k; i++)
    {
        DP[i] = max(DP[i-1],A[i-1]);
    }
    for (int i = k+1; i <= n; i++)
    {
        DP[i] = max(DP[i-1],DP[i-k-1]+A[i-1]);
    }
    cout << DP[n];
    return 0;
}