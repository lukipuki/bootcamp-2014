//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <queue>
#include <bitset>
#include <utility>
#include <list>
#include <numeric>

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int main()
{
    int n;
    while (cin >> n)
    {
        if (!n) break;
        vi a(n);
        rep(i,0,n)
            cin >> a[i];

        unordered_map<ll, ll> reachable;
        ll po = 1;
        rep(i,0,(n+1)/2)
            po *= 3;

        rep(k,0,po)
        {
            ll u = k;
            ll sum = 0, non = 0;
            rep(i,0,(n+1)/2)
            {
                int zv = u % 3;
                if (zv == 0)
                    sum += a[i];
                if (zv == 1)
                    sum -= a[i];
                if (zv == 2)
                    non += a[i];
                u /= 3;
            }

            if (reachable.count(sum) == 0)
                reachable[sum] = non;
            else if (reachable[sum] > non)
                reachable[sum] = non;
        }

        ll best = 1LL<<50;
        po = 1;
        rep(i,0,n/2)
            po *= 3;
        rep(k,0,po)
        {
            ll u = k;
            ll sum = 0, non = 0;
            rep(i,(n+1)/2,n)
            {
                int zv = u % 3;
                if (zv == 0)
                    sum += a[i];
                if (zv == 1)
                    sum -= a[i];
                if (zv == 2)
                    non += a[i];
                u /= 3;
            }

            if (reachable.count(sum))
                best = min(best, reachable[sum] + non);
        }

        cout << best << endl;
    }
}
