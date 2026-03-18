#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,a,b;
    vector <pair<int,int>> V;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        V.push_back({a,1});
        V.push_back({b,-1});
    }
    sort(V.begin(),V.end());
    int s = 0,mx = 0;
    for(auto [x,y]:V)
    {
        s += y;
        mx = max(mx,s);
    }
    cout << mx;
    return 0;
}