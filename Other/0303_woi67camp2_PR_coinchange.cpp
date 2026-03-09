#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,co,idx = 8,q;
    int A[9] = {1,2,5,10,20,50,100,500,1000};
    cin >> q;
    while (q--)
    {
        co = 0;
        cin >> n;
        for (int i = idx; i >= 0; i--)
        {
            if (A[i] <= n)
            {
                co += (n/A[i]);
                n %= A[i];
            }
        }
        cout << co << "\n";
    }
    return 0;
}