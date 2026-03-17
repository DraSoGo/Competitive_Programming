#include <bits/stdc++.h>
using namespace std;
 
const int sz = 1e3 + 1;
int n, m;
int di[4] = {0,0,1,-1};
int dj[4] = {1,-1,0,0};
pair<int, int> st, ed,par[sz][sz];
char T[sz][sz];
vector <pair<int,int>> V;
bool vis[sz][sz];
queue <pair<int,int>> Q;
 
bool chek(int i,int j)
{
    if (T[i][j] == '#' || i < 0 || j < 0 || i >= n || j >= m || vis[i][j])
    {
        return 0;
    }
    return 1;
}
 
int BFS()
{
    Q.push({st.first,st.second});
    int lvq = 0;
    while (!Q.empty())
    {
        int sq = Q.size();
        while (sq--)
        {
            auto [ii,jj] = Q.front();
            Q.pop();
            if (ii == ed.first && jj == ed.second)
            {
                // cout << ii << "," << jj << " " << par[ii][jj].first << "," << par[ii][jj].second << "\n";
                while (par[ii][jj].first != ii || par[ii][jj].second != jj)
                {
                    V.push_back({ii,jj});
                    // cout << ii << " " << jj << " " << par[ii][jj].first << " " << par[ii][jj].second << " , ";
                    int a = par[ii][jj].first,b = par[ii][jj].second;
                    ii = a;
                    jj = b;
                    // cout << ii << " " << jj << "\n";
                    // cout << a << " " << b << "\n";
                }
                V.push_back({ii,jj});
                return lvq;
            }
            if (vis[ii][jj])
            {
                continue;
            }
            vis[ii][jj] = 1;
            for (int k = 0; k < 4; k++)
            {
                int ni = ii + di[k];
                int nj = jj + dj[k];
                if (chek(ni,nj))
                {
                    Q.push({ni,nj});
                    // cout << ni << " " << nj << "\n";
                    par[ni][nj] = {ii,jj};
                }
            }
        }
        // cout << "\n";
        lvq++;
    }
    return -1;
}
 
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> T[i][j];
            par[i][j] = {i,j};
            if (T[i][j] == 'A')
            {
                st = {i, j};
            }
            else if (T[i][j] == 'B')
            {
                ed = {i, j};
            }
        }
    }
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << par[i][j].first << "," << par[i][j].second << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";
    int step = BFS();
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << par[i][j].first << "," << par[i][j].second << " ";
    //     }
    //     cout << "\n";
    // }
    
    if (step == -1)
    {
        cout << "NO";
        return 0;
    }
    cout << "YES\n" << step;
    // cout << par[2][1].first << " " << par[2][1].second; 
    return 0;
}