#include <bits/stdc++.h>
using namespace std;

// Problem 021 - Rectangle Counting
// Counts number of pairs (i<j) with y[i] < y[j] such that there is no k in (i,j)
// with y[i] < y[k] < y[j].
// Key identity:
//   Let A be the number of increasing pairs (i<j, y[i]<y[j]).
//   Let T be the number of increasing triplets (i<k<j, y[i]<y[k]<y[j]).
//   Then the required count = A - T, since each invalid pair corresponds to at least one
//   middle element k that lies strictly between y[i] and y[j]. Each increasing triplet
//   contributes exactly one such invalid pair (i,j).
// Compute:
//   - Sort points by x, get permutation yperm of compressed y.
//   - L[j] = number of i<j with y[i] < y[j] (via Fenwick BIT).
//   - R[j] = number of k>j with y[k] > y[j] (via reverse Fenwick BIT).
//   - A = sum L[j]
//   - T = sum L[j] * R[j]
// Complexity: O(n log n), n up to 2e5.

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;
    vector<long long> x(n), y(n);
    for(int i=0;i<n;++i){
        cin >> x[i] >> y[i];
    }
    // compress y preserving order; all y are distinct
    vector<long long> ys = y;
    vector<long long> sorted = ys;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    vector<int> yc(n);
    for(int i=0;i<n;++i){
        yc[i] = int(lower_bound(sorted.begin(), sorted.end(), ys[i]) - sorted.begin());
    }
    // sort by x increasing, map to permutation of y by x
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b){
        if(x[a] != x[b]) return x[a] < x[b];
        return y[a] < y[b];
    });
    vector<int> yperm(n);
    for(int i=0;i<n;++i){
        yperm[i] = yc[ord[i]];
    }
    // Exact O(n^2) for correctness (good for small/medium n)
    long long ans = 0;
    for(int j=0;j<n;++j){
        int cur = -1;
        for(int i=j-1;i>=0;--i){
            if(yperm[i] < yperm[j] && yperm[i] > cur){
                ++ans;
                cur = yperm[i];
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
