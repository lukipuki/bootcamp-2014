#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100;

int lis[MAXN], n, bes, sum[MAXN];

void search(int p, int dif, int s) {
  if(dif == 0 && s > bes) {
    bes = s;
//printf("%d\n", sum[n-1] - bes);
  }
  if(p >= 0) {
    if(abs(dif) > sum[p]) return;
    if(s + sum[p] <= bes) return;
    search(p - 1, dif + lis[p], s + lis[p]); 
    search(p - 1, dif - lis[p], s + lis[p]); 
    search(p - 1, dif, s);
  }
}

int Split(int N, int *M){
  n = N;
  for(int i = 0; i < n; ++i) {
    lis[i] = M[i];
    sum[i] = ((i == 0) ? 0 : sum[i-1]) + lis[i];
  }
  bes = 0;
  search(n-1, 0, 0);
//printf("%d\n", sum[n-1] - bes);
  return sum[n-1] - bes;
}

main() {
    int N;
    int M[33];
    int i;
    while(1) {
        scanf("%d", &N);
        if(!N) break;
        for(i = 0; i < N; i++) scanf("%d", M+i);
        i = Split(N,M);
        printf("%d\n", i);
    }
}
