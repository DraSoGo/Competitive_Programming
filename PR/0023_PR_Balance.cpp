#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    long long a;
    if (!(cin >> a)) return;
    
    if (a == 0) {
        cout << 0 << endl;
        return;
    }

    vector<int> coefficients;
    while (a != 0) {
        int rem = a % 3;
        a /= 3;

        if (rem == 2) {
            rem = -1;
            a += 1;
        } else if (rem == -2) {
            rem = 1;
            a -= 1;
        } else if (rem == 1 && a < 0 && (a * 3 + rem) != (a * 3 + 1)) {
             // Handling negative adjustments if necessary
        }

        if (rem > 1) {
            rem -= 3;
            a += 1;
        } else if (rem < -1) {
            rem += 3;
            a -= 1;
        }

        coefficients.push_back(rem);
    }

    for (int i = coefficients.size() - 1; i >= 0; --i) {
        cout << coefficients[i] << (i == 0 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    while (n--) {
        solve();
    }
    return 0;
}