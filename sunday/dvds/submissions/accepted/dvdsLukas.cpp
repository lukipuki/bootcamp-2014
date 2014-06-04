//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
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
    int t; scanf("%d", &t);
    rep(cas,0,t)
    {
        int n; scanf("%d", &n);
        int cur = 1;
        rep(i,0,n)
        {
            int x; scanf("%d", &x);
            if (x == cur)
                cur++;
        }
        cout << (n - cur + 1) << endl;
    }
}
