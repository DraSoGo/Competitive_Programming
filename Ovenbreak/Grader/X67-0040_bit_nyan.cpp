#include <bits/stdc++.h>
using namespace std;

string sum_b(vector<string>& b)
{
    string ans = "";
    int c = 0;
    int m = b[0].size();
    
    for (int i = m - 1; i >= 0; i--)
    {
        int sum = c;
        for (int j = 0; j < b.size(); j++)
        {
            sum += b[j][i] - '0';
        }
        ans += (sum % 2) + '0';
        c = sum / 2;
    }
    
    while (c > 0) {
        ans += (c % 2) + '0';
        c /= 2;
    }
    
    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n,q;
        cin >> n >> q;
        vector<string> b(n);
        for (int i = 0; i < n; i++)
        {
            string x;
            cin >> x;
            b[i] = x;
        }
        string bsum = sum_b(b),ans = "";
        reverse(bsum.begin(), bsum.end());
        for (int i = 0; i < q; i++)
        {
            ans += bsum[i];
        }
        reverse(ans.begin(), ans.end());
        // cout << "\n";
        cout << ans << "\n";
    }
    return 0;
}
