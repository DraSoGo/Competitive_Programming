#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long k,q,ans;
    vector<long long> fib;
    fib.push_back(1);
    fib.push_back(1);
    cin >> q;
    while (q--)
    {
        ans = 0;
        cin >> k;
        while (k > fib.back())
        {
            fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
        }
        long long x = fib.size()-1;
        while(k != 0)
        {
            if (k >= fib[x])
            {
                k -= fib[x];
                ans++;
            }
            else
            {
                x--;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}