#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_N = 100000;
int Size, clusterSize;

int arr[MAX_N];

int cluster[MAX_N];

void build()
{
    Size = ceil(sqrt(MAX_N));

    clusterSize = ceil((double)MAX_N / Size);

    for (int i = 0; i < MAX_N; i++)
    {
        cluster[i / Size] += arr[i];
    }
}

int query(int l, int r)
{
    int res = 0;

    while (l < r && l % Size != 0)
    {
        res += arr[l++];
    }

    while (l + Size - 1 <= r && l % Size == 0)
    {
        res += cluster[l / Size];
        l += Size;
    }

    while (l <= r)
    {
        res += arr[l++];
    }
    return res;
}

void update(int idx, int val)
{
    arr[idx] = val;

    int l = (idx / Size) * Size;
    int r = min(MAX_N - 1, l + Size - 1);
    int cluster_idx = l / Size;

    cluster[cluster_idx] = 0;

    for (int i = l; i <= r; i++)
    {
        cluster[cluster_idx] += arr[i];
    }
}

int main()
{
    build();
    int n,k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    while (k--)
    {
        int c,a,b;
        cin >> c >> a >> b;
        if (c == 2)
        {
            update(a, b);
        }
        else
        {
            cout << query(a, b) << "\n";
        }
    }
    return 0;
}
/*
INPUT
9 3
5 6 3 9 8 2 6 4 8
1 0 4
2 2 10
1 0 4

OUTPUT
31
38


5 6 3 9 8 2 6 4 8
*       *
5+6+3+9+8 = 31

5 6 10 9 8 2 6 4 8
*       *
5+6+10+9+8 = 38
*/