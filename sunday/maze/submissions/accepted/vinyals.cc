#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

typedef vector<string> VS;
typedef queue<int> QI;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI;

int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};

int solve(const VS& maze) {
  int a=maze.size();
  int b=maze.front().size();
  VVVI seen(a, VVI(b, VI(8)));
  QI q;
  for (int i=0;i<a;++i) {
    for (int j=0;j<b;++j) {
      if (maze[i][j]=='R') {
        for (int k=0;k<4;++k) {
          q.push(i); q.push(j); q.push(k); q.push(0);
        }
      }
    }
  }
  while(not q.empty()) {
    int i=q.front(); q.pop();
    int j=q.front(); q.pop();
    int d=q.front(); q.pop();
    int t=q.front(); q.pop();
    if (seen[i][j][d]) continue;
    seen[i][j][d]=true;
    if (maze[i][j]=='D') return t;
    for (int k=0; k<4; ++k) {
      if (k==d) continue;
      if (abs(k-(d&3))==2) continue;
      int ii=i+dx[k];
      int jj=j+dy[k];
      if (ii<0 or ii>=a or jj<0 or jj>=b or maze[ii][jj]=='B') continue;
      int dd=k|4;
      if (dd==d) dd=k;
      q.push(ii); q.push(jj); q.push(dd); q.push(t+1);
    }
  }
  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--) {
    int a,b;
    cin >> a >> b;
    VS maze(a);
    for (string& s : maze) cin >> s;
    cout << solve(maze) << endl;
  }
}
