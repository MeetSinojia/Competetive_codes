#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define sortt(v) sort(v.begin(), v.end())
#define sorttd(a) sort(a.begin(), a.end(), greater<int>())
#define fo(i, n) for (i = 0; i < n; i++)
#define pb push_back
#define ff first
#define ss second
#define deb(x) cout << #x << '=' << x << endl
#define input(arr, n) fo(i, n) cin >> arr[i]
typedef vector<int> vi;
typedef vector<ll> vl;
const int mod = 1'000'000'007;

void build(int ind, int low, int high, int arr[], int seg[], bool orr)
{
    if (low == high)
    {
        seg[ind] = arr[low];
        return;
    }

    int mid = (low + high) / 2;
    build(2 * ind + 1, low, mid, arr, seg, !orr);
    build(2 * ind + 2, mid + 1, high, arr, seg, !orr);

    if (orr)
    {
        seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
    }
    else
    {
        seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
    }
}

void update(int ind, int low, int high, int arr[], int seg[], bool orr, int i, int val)
{
    if (low == high)
    {
        seg[ind] = val;
        return;
    }

    int mid = (low + high) / 2;
    // Here we are doing like this becuase in update we don't need to update the whole tree
    if (i <= mid)
    {
        update(2 * ind + 1, low, mid, arr, seg, !orr, i, val);
    }
    else
    {
        update(2 * ind + 2, mid + 1, high, arr, seg, !orr, i, val);
    }

    if (orr)
    {
        seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
    }
    else
    {
        seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
    }
}

void solve()
{
    int m, n, q;
    cin >> m >> q;
    n = 1 << m;
    int vec[n] = {0};

    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }

    // Maximum size of segment tree needed
    int seg[4 * n] = {0};

    if (m % 2 == 0)
    {
        // If n is even we do xor first
        build(0, 0, n - 1, vec, seg, 0);
    }
    else
    {
        // If n is odd we do or first
        build(0, 0, n - 1, vec, seg, 1);
    }

    while (q--)
    {
        int i, val;
        cin >> i >> val;
        // One based indexing
        i--;
        if (m % 2 == 0)
        {
            update(0, 0, n - 1, vec, seg, 0, i, val);
        }
        else
        {
            update(0, 0, n - 1, vec, seg, 1, i, val);
        }

        cout << seg[0] << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    int t;
    t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
        cout << endl;
    }
    return 0;
}