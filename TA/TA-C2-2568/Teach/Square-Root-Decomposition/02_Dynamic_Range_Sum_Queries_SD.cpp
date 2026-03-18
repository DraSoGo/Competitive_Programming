#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long n,q,c,a,b,sz,cs,ans;
    cin >> n >> q;
    sz = ceil(sqrt(double(n)));
    cs = ceil(double(n)/sz);
    long long A[n],SD[sz];
    memset(SD,0,sizeof(SD));
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++)
    {
        SD[i/sz] += A[i];
    }
    while (q--)
    {
        cin >> c >> a >> b;
        if (c == 2)
        {
            a--,b--;
            int ans = 0;
            while (a < b && a % sz != 0)
            {
                ans += A[a];
                a++;
            }
            while (a + sz - 1 <= b && a % sz == 0)
            {
                ans += SD[a/sz];
                a += sz;
            }
            while (a <= b)
            {
                ans += A[a];
                a++;
            }
            cout << ans << "\n";
        }
        else
        {
            a--;
            SD[a/sz] += b-A[a];
            A[a] = b;
        }
    }
    
    return 0;
}
//https://cses.fi/alon/task/1648