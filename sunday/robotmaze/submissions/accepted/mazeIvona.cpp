#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

#define MAX 1005
#define MAXSTEPS 2

int m,n,ar,ac,br,bc;

struct xxx {
       // row, column, and direction that entered this location
       // count is how many times went in this direction
       int r,c,d,count;       
};

char board[MAX][MAX];

struct xxx queue[MAX*MAX*4*(MAXSTEPS+1)];
int found[MAX][MAX][4][MAXSTEPS+1];
int dist[MAX][MAX][4][MAXSTEPS+1];

int dirr[4],dirc[4];

void printBoard() {
     int i;
     for (i=0; i<m+2; i++) printf("%s\n",board[i]);     
     printf("\n");
}

int main() {
    int k,i,j,beg,end,mindist,foundTarget,rr,cc,dd,d,s,cnt;
       
    scanf("%d",&k);
    
    for (; k>0; k--) {
        // input
        scanf("%d %d\n",&m,&n);
        
        for (i=1; i<=m; i++) {
            scanf("%s",board[i]+1);
            for (j=1; j<=n; j++) {
                if (board[i][j] == 'R') {
                   ar = i;
                   ac = j;
                   board[i][j] = '.';
                }
                if (board[i][j] == 'D') {
                   br = i;
                   bc = j;
                   board[i][j] = '.';
                }
            }
        }
        
        if (DEBUG) printf("ar,ac = %d,%d  br,bc = %d,%d\n",ar,ac,br,bc);
        
        // create walls around
        for (i=0; i<m+2; i++) {
            board[i][0] = 'X';
            board[i][n+1] = 'X';
            board[i][n+2] = 0; // to make printing out easier
        }
        for (j=0; j<n+2; j++) {
            board[0][j] = 'X';
            board[m+1][j] = 'X';
        }

        if (DEBUG) printBoard();
                
        // possible directions
        dirr[0] = 1; dirc[0] = 0;
        dirr[1] = 0; dirc[1] = 1;
        dirr[2] = -1; dirc[2] = 0;
        dirr[3] = 0; dirc[3] = -1;

        // BFS
        // initialization
        for (i=0; i<m+2; i++) {
            for (j=0; j<n+2; j++) {
                for (d=0; d<4; d++) {
                    for (s=0; s<=MAXSTEPS; s++) {
                        found[i][j][d][s] = 0;
                        dist[i][j][d][s] = -1;
                    }
                }
            }    
        }
        // init starting location
        for (d=0; d<4; d++) {
            queue[d].r = ar;
            queue[d].c = ac;
            queue[d].d = d;
            queue[d].count = 1;
            found[ar][ac][d][1] = 1;
            dist[ar][ac][d][1] = 0;
        }
        beg = 0;
        end = 4;

        foundTarget = 0;
        while (beg<end && !foundTarget) {
              rr = queue[beg].r;
              cc = queue[beg].c;
              dd = queue[beg].d;
              cnt = queue[beg].count;
              
              if (DEBUG) printf("\nBFS: processing %d,%d, direction %d, count %d, distance %d\n",rr,cc,dd,cnt,dist[rr][cc][dd][cnt]);
              
              // go through the neighbors of beg
              for (d=0; d<4; d++) {
                  if ((4+dd-d)%4!=2) {
                     // opposite direction is not allowed

                     if (d==dd) {
                        // continuing in the same direction beyond MAXSTEPS not allowed
                        if (cnt<MAXSTEPS) {
                           if (!found[rr+dirr[d]][cc+dirc[d]][d][cnt+1] && board[rr+dirr[d]][cc+dirc[d]]=='.') {                                                                       
                              queue[end].r = rr+dirr[d];
                              queue[end].c = cc+dirc[d];
                              queue[end].d = d;
                              queue[end].count = cnt+1;
                              found[queue[end].r][queue[end].c][queue[end].d][queue[end].count] = 1;
                              dist[queue[end].r][queue[end].c][queue[end].d][queue[end].count] = dist[rr][cc][dd][cnt]+1;

                              if (rr+dirr[d] == br && cc+dirc[d] == bc) {
                                  foundTarget = 1;
                                  mindist = dist[queue[end].r][queue[end].c][queue[end].d][queue[end].count];
                              }
                              
                              if (DEBUG) printf(" - adding %d,%d dir %d cnt %d dist %d\n",queue[end].r,queue[end].c,queue[end].d,queue[end].count,dist[queue[end].r][queue[end].c][queue[end].d][queue[end].count]);
                              
                              end++;  
                           }            
                        }
                     } else {
                        // a new direction: count resets to 1
                        if (!found[rr+dirr[d]][cc+dirc[d]][d][1] && board[rr+dirr[d]][cc+dirc[d]]=='.') {
                              queue[end].r = rr+dirr[d];
                              queue[end].c = cc+dirc[d];
                              queue[end].d = d;
                              queue[end].count = 1;
                              found[queue[end].r][queue[end].c][queue[end].d][queue[end].count] = 1;
                              dist[queue[end].r][queue[end].c][queue[end].d][queue[end].count] = dist[rr][cc][dd][cnt]+1;

                              if (rr+dirr[d] == br && cc+dirc[d] == bc) {
                                  foundTarget = 1;
                                  mindist = dist[queue[end].r][queue[end].c][queue[end].d][queue[end].count];
                              }
                              
                              if (DEBUG) printf(" - adding %d,%d dir %d cnt %d dist %d\n",queue[end].r,queue[end].c,queue[end].d,queue[end].count,dist[queue[end].r][queue[end].c][queue[end].d][queue[end].count]);

                              end++;  
                        }            
                     }                     
                  }
              }
              beg++;
        }

        if (!foundTarget) {
           printf("-1\n");
        } else {                  
           printf("%d\n",mindist);          
        }
    }
    
    if (DEBUG) scanf("%d",&k);
    return 0;   
}
