#include <cstring>
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int n;
vector<string> board;
short dp[100][100][100][100];
char dir1[100][100][100][100];
char dir2[100][100][100][100];

int dx[] = {1,0,0};
int dy[] = {0,1,0};
char dname[] = "DR";

int get(int a, int b, int c, int d) {
  if (a<0 or b<0) return -1;
  if (c>=n or d>=n) return -1;
  short& x=dp[a][b][c][d];
  if (x!=-1) return x;
  if (board[a][b]!=board[c][d]) return x=-2;
  char& d1=dir1[a][b][c][d];
  char& d2=dir2[a][b][c][d];
  x=0;
  d1=d2=2;
  for (int k1=0;k1<2;++k1) {
    int aa=a-dx[k1];
    int bb=b-dy[k1];
    for (int k2=0;k2<2;++k2) {
      int cc=c+dx[k2];
      int dd=d+dy[k2];
      if (get(aa,bb,cc,dd)>x) {
        x=get(aa,bb,cc,dd);
        d1=k1;
        d2=k2;
      }
    }
  }
  if(a!=c or b!=d) ++x;
  return ++x;
}

void reconstruct(int a, int b, int d) {
  int aa=a,bb=b,cc=a+dx[d],dd=b+dy[d];
  deque<char> pali(1,board[aa][bb]);
  deque<char> dir;
  if (d!=2) {
    pali.push_back(board[cc][dd]);
    dir.push_back(dname[d]);
  }
  while(true) {
    int d1=dir1[aa][bb][cc][dd];
    if (d1==2) break;
    int d2=dir2[aa][bb][cc][dd];
    aa-=dx[d1];
    bb-=dy[d1];
    cc+=dx[d2];
    dd+=dy[d2];
    pali.push_front(board[aa][bb]);
    pali.push_back(board[cc][dd]);
    dir.push_front(dname[d1]);
    dir.push_back(dname[d2]);
  }
  for (char c : pali) cout << c;
  cout << " " << aa+1 << " " << bb+1 << " ";
  for (char c: dir) cout << c;
  cout << "S" << endl;
}

int main() {
  int k;
  cin >> k;
  while(k--) {
    memset(dp,-1,sizeof(dp));
    cin >> n;
    board.resize(n);
    for (string& s : board) cin >> s;
    int mxi,mxj,mxd,mx=0;
    for (int i=0; i<n; ++i) {
      for (int j=0; j<n; ++j) {
        for (int d=0; d<3; ++d) {
          int ii=i+dx[d];
          int jj=j+dy[d];
          if (get(i,j,ii,jj)>=mx) {
            mx=get(i,j,ii,jj);
            mxi=i;
            mxj=j;
            mxd=d;
          }
        }
      }
    }
    reconstruct(mxi,mxj,mxd);
  }
}
