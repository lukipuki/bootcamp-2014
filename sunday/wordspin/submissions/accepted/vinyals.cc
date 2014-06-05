#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;

int main() {
  ios::sync_with_stdio(false);
  string a,b;
  cin >> a >> b;
  int n = a.size();
  VI x(n+2);
  VI who(n+2);
  for (int i=0; i<n; ++i) x[i+1]=b[i]-a[i];
  int ret=0;
  for (int i=1; i<=n; ++i) {
    int cost=abs(x[i]);
    if (x[i] * x[i-1] > 0) {
      int q=abs(x[i])-abs(x[i-1]);
      if (q>=0) cost=min(cost,q);
      else cost=0;
    }
    ret += cost;
  }
  cout << ret << endl;
}
