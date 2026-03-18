#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,a,b,idx = 0,ans = 0,sum = 0;
    cin >> n;
    pair<int,int> A[n];
    int tmp[2*n];
    map <int,int> M;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        A[i] = {a, b};
        tmp[i] = a;
        tmp[i+n] = b;
    }
    sort(tmp, tmp + 2*n);
    for (int i = 0; i < 2*n; i++)
    {
        if (M.find(tmp[i]) == M.end())
        {
            M[tmp[i]] = idx;
            // cout << tmp[i] << " " << idx << "\n";
            idx++;
        }
    }
    int qs[idx];
    memset(qs, 0, sizeof(qs));
    for (int i = 0; i < n; i++)
    {
        qs[M[A[i].first]]++;
        qs[M[A[i].second]]--;
    }
    for (int i = 0; i < idx; i++)
    {
        // cout << qs[i] << " ";
        sum += qs[i];
        ans = max(ans, sum);
    }
    // cout << "\n";
    cout << ans;
    return 0;
}
//https://cses.fi/problemset/task/1619/