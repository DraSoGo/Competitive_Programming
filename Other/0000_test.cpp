// charprint
#include <bits/stdc++.h>
#define en '\n'
#define sp ' '
#define ll long long
using namespace std;

const int N = 3e5 + 5;
int mode, n;
string s, t;
map<char, queue<int>> mp;
ll tree[N], a[N];

void update(int idx, int val)
{
    for (; idx <= n; idx += (idx & -idx))
        tree[idx] += val;
}

ll query(int idx)
{
    ll ans = 0;
    for (; idx; idx -= (idx & -idx))
        ans += tree[idx];
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> mode >> s >> t;
    n = s.size();
    for (int i = 0; i < n; i++)
    {
        mp[s[i]].push(i + 1);
        a[i + 1] = 1;
        update(i + 1, 1);
    }
    ll ans = 0;
    if (!mode)
    {
        for (int i = 0; i < t.size(); i++)
        {
            if (mp[t[i]].empty())
            {
                cout << -1;
                return 0;
            }
            ans += mp[t[i]].front();
            mp[t[i]].pop();
        }
        cout << ans;
        return 0;
    }
    for (int i = 0; i < t.size(); i++)
    {
        if (mp[t[i]].empty())
        {
            cout << -1;
            return 0;
        }
        int idx = mp[t[i]].front();
        ans += query(idx);
        update(idx, -1);
        a[idx] = 0;
        mp[t[i]].pop();
    }
    cout << ans;
    return 0;
}