#include <bits/stdc++.h>
using namespace std;

struct Seg
{
    long long l, r, v;
    bool operator<(const Seg &b) const
    {
        return v < b.v;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    if (cin >> t)
    {
        while (t--)
        {
            int n;
            cin >> n;
            Seg A[n];
            long long sum = 0;

            for (int i = 0; i < n; i++)
            {
                cin >> A[i].l >> A[i].r;
                A[i].v = A[i].l + A[i].r;
                sum += A[i].r - A[i].l;
            }

            sort(A, A + n);

            if (n % 2 == 0)
            {
                int k = n / 2;
                long long add = 0;
                for (int i = 0; i < k; i++)
                {
                    add -= A[i].l;
                }
                for (int i = k; i < n; i++)
                {
                    add += A[i].r;
                }

                cout << sum + add << "\n";
            }
            else
            {
                int k = n / 2;

                long long L[n + 1];
                long long R[n + 1];
                memset(L, 0, sizeof(L));
                memset(R, 0, sizeof(R));
                for (int i = 0; i < n; i++)
                {
                    L[i + 1] = L[i] + A[i].l;
                }
                for (int i = n - 1; i >= 0; i--)
                {
                    R[i] = R[i + 1] + A[i].r;
                }

                long long mx_add = INT_MIN;

                for (int m = 0; m < n; m++)
                {
                    long long add = 0;
                    if (m < k)
                    {
                        add = R[k + 1] - (L[k + 1] - A[m].l);
                    }
                    else if (m > k)
                    {
                        add = (R[k] - A[m].r) - L[k];
                    }
                    else
                    {
                        add = R[k + 1] - L[k];
                    }
                    mx_add = max(mx_add, add);
                }
                cout << sum + mx_add << "\n";
            }
        }
    }
    return 0;
}