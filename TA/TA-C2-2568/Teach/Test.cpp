#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long n,q,c,a,b,sz;
    cin >> n >> q;
    sz = ceil(sqrt(double(n)));
    long long A[n],cluster[sz];
    fill(cluster, cluster+sz, INT_MAX);
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++)
    {
        cluster[i/sz] = min(A[i],cluster[i/sz]);
    }
    
    while (q--)
    {
        cin >> c >> a >> b;
        if(c == 1)
        {
            a--;
            A[a] = b;
            long long l = (a/sz)*sz, r = min(n-1,l+sz-1);
            cluster[a/sz] = INT_MAX;
            for (long long i = l; i <= r; i++)
            {
                cluster[a/sz] = min(cluster[a/sz],A[i]);
            }
        }
        else
        {
            a--,b--;
            long long ans = INT_MAX;
            while (a < b && a % sz != 0)
            {
                ans = min(ans,A[a]);
                a++;
            }
            
            while (a+sz-1 <= b && a % sz == 0)
            {
                ans = min(ans,cluster[a/sz]);
                a += sz;
            }
            
            while (a <= b)
            {
                ans = min(ans,A[a]);
                a++;
            }
            cout << ans << "\n";
        }
        // for (int i = 0; i < sz; i++)
        // {
        //     cout << cluster[i] << " ";
        // }
        // cout << "\n";
        
    }
    return 0;
}