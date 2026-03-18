#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    vector <pair<int,int>> V;
    int n,a,b,sum = 0,mx = INT_MIN;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        V.push_back({a,1});
        V.push_back({b,-1});
    }
    sort(V.begin(),V.end());
    for(auto [x,y]:V)
    {
        sum += y;
        mx = max(mx,sum);
    }
    cout << mx << "\n";
    return 0;
}