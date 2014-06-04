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
    int k; scanf("%d", &k);
    printf("%d\n", k);
    rep(j,0,k)
    {
        int n; scanf("%d", &n);
        vector<bool> b(n);
        vi a(n);
        rep(i,0,a.size())
            scanf("%d", &a[i]);

        if (n > 500000)
            n = 500000;
        rep(i,0,n)
            b[i] = true;
        random_shuffle(b.begin(), b.end());

        vi c;
        rep(i,0,a.size()) if (b[i])
            c.push_back(a[i]);
        sort(c.begin(), c.end());
        unordered_map<int, int> d;
        rep(i,0,c.size())
            d[c[i]] = i + 1;

        printf("%d\n", n);
        rep(i,0,a.size()) if (b[i])
            printf("%d ", d[a[i]]);
        printf("\n");
    }
}
