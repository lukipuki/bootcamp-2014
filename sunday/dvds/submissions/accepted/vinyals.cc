#include <iostream>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--) {
    int n;
    cin >> n;
    int expect=1;
    int nops=0;
    for (int i=0; i<n; ++i) {
      int x;
      cin >> x;
      if (x==expect) ++expect;
      else ++nops;
    }
    cout << nops << endl;
  }
}
