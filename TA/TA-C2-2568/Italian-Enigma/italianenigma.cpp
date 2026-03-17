/*
Task: Italian-Enigma
Author: DraSoGo
*/
#include <bits/stdc++.h>
using namespace std;

const int mxi = 51;
long long S[mxi + 10];
long long A[mxi + 10];

vector<string> R = {"", "tri", "ppi", "tro", "ppi"};

char enigma(int n, long long m)
{
    if (n == 1)
    {
        return "tri"[m];
    }
    long long left = A[n - 1];
    int idx = (n % 4 == 0) ? 4 : (n % 4);
    long long mid = S[n + 1] * 3;
    if (m < left)
    {
        return enigma(n - 1, m);
    }
    else if (m >= left + mid)
    {
        long long pos = m - left - mid;

        return enigma(n - 1, left - 1 - pos);
    }
    else
    {
        long long offset = m - left;
        return R[idx][offset % 3];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    S[1] = 2;
    S[2] = 1;
    for (int i = 3; i < mxi + 1; i++)
    {
        S[i] = S[i - 1] + S[i - 2];
    }
    A[1] = 3;
    for (int i = 2; i < mxi + 1; i++)
    {
        A[i] = 2 * A[i - 1] + S[i + 1] * 3;
    }
    int T;
    cin >> T;
    while (T--)
    {
        int lv;
        long long X;
        cin >> lv >> X;
        X--;
        cout << enigma(lv, X) << "\n";
    }
    return 0;
}