#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long n,q;
    cin >> n >> q;
    long long A[n],sz = ceil(sqrt(double(n))),SD[sz];
    fill(SD,SD+sz,INT_MAX);
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++)
    {
        SD[i/sz] = min(A[i],SD[i/sz]);
    }
    while (q--)
    {
        long long a,b,c;
        cin >> c >> a >> b;
        if (c == 2)
        {
            long long ans = INT_MAX;
            a--,b--;
            while (a < b && a % sz != 0)
            {
                ans = min(ans,A[a]);
                a++;
            }
            while (a + sz - 1 <= b && a%sz == 0)
            {
                ans = min(ans,SD[a/sz]);
                a += sz;
            }
            while (a <= b)
            {
                ans = min(ans,A[a]);
                a++;
            }
            cout << ans << "\n";
        }
        else
        {
            a--;
            A[a] = b;
            long long l = (a/sz)*sz,mn = INT_MAX;
            for (int i = l; i < min(l+sz,n); i++)
            {
                mn = min(mn,A[i]);
            }
            SD[l/sz] = mn;
        }
        
    }
    
    return 0;
}
//https://cses.fi/alon/task/1649