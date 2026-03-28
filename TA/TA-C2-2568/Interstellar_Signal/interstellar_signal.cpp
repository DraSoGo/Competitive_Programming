#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int q;
    cin >> q;
    while (q--)
    {
        int t,n,ans = 0;
        cin >> t >> n;
        map<multiset<char>, int> mp;
        while (t--)
        {
            multiset<char> s;
            for (int i = 0; i < n; i++)
            {
                char x;
                cin >> x;
                s.insert(x);
            }
            mp[s]++;
            ans = max(ans, mp[s]);
        }
        cout << ans << "\n";
    }
    return 0;
}