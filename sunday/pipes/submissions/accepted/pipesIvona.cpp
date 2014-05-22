#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

#define MAX 10002

int m,n,p;

int boundary[4*MAX];
int board[MAX][MAX];

int dr[4],dc[4];

void printBoard() {
     int i,j;
     for (i=0; i<=m+1; i++) {
         for (j=0; j<=n+1; j++) {
             printf(" %2d",board[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}

void printBoard2() {
     int i,j;
     for (i=0; i<=m+1; i++) {
         for (j=0; j<=n+1; j++) {
             if ((i==0 || i==m+1) && (j==0 || j==n+1)) {
                printf("   ");
                continue;
             } 
             if (j==0 && i>0 && i<=m) {
                printf("%2d|",boundary[i-1]);      
             } else {
                if (i==m+1 && j>0 && j<=n) {
                   printf(" %2d",boundary[m+j-1]);
                } else {
                   if (j==n+1 && i>0 && i<=m) {
                      printf("|%2d",boundary[2*m+n-i]);
                   } else {
                      if (i==0 && j>0 && j<=n) {
                         printf(" %2d",boundary[2*m+2*n-j]);
                      } else {
                         printf(" %2d",board[i][j]);
                      }
                   }
                }
             }
         }
         printf("\n");
         if (i==0 || i==m) {
            for (j=0; j<=n+1; j++) {
                printf("---");    
            }     
            printf("\n");    
         }
     }
     printf("\n");
}

int floodToTheRight(int ar, int ac, int lr, int lc, int br, int bc, int label) {
    int i,j,lastDirr,lastDirc;
    
    // label the current location
    if (board[ar][ac]!=0) return 0;
    board[ar][ac] = label;
    
    // printBoard();
    
    if (ar==br && ac==bc) return 1; // found the destination
    
    // figure out the last direction
    lastDirr = lr-ar;
    lastDirc = lc-ac;
    
    // printf("ar,ac %d,%d, last direction %d,%d\n",ar,ac,lastDirr,lastDirc);
    
    // find the direction in the direction array
    for (i=0; (i<4) && !(dr[i]==lastDirr && dc[i]==lastDirc); i++);
    
    // now try all four directions counterclockwise, i.e. direction i+j for increasing j
    for (j=1; j<4; j++) {
        // printf("trying direction %d,%d\n",dr[(i+j)%4],dc[(i+j)%4]);
        if (floodToTheRight(ar+dr[(i+j)%4],ac+dc[(i+j)%4],ar,ac,br,bc,label)) return 1;
    }
    
    return 0;
}

void findSquare(int a, int &ar, int &ac, int &lr, int &lc) {
     a++; // calculations below assume numbering from the writeup
     
     // find also the "last" square to get a starting direction -> last square is outside of the board

     if (a<=m) {
        ar = a;
        ac = 1;
        lr = ar;
        lc = 0;
        return;          
     }
     if (a<=m+n) {
        ar = m;
        ac = a-m;
        lr = m+1;
        lc = ac;
        return;          
     }
     if (a<=2*m+n) {
        ar = m-(a-m-n)+1;
        ac = n;
        lr = ar;
        lc = n+1;
        return;          
     }
     ar = 1;
     ac = n-(a-2*m-n)+1;
     lr = 0;
     lc = ac;
}

int connect(int a, int b) {
    int ar,ac,br,bc,lr,lc,xr,xc;
        
    // printf("connecting %d with %d\n",a,b);
        
    // find the adjacent squares
    findSquare(a,ar,ac,lr,lc);
    findSquare(b,br,bc,xr,xc);

    // printf("coordinates %d,%d  %d,%d\n",ar,ac,br,bc);
    
    // flood, while holding the walls with right hand
    return floodToTheRight(ar,ac,lr,lc,br,bc,boundary[a]);
}

void printBoundary() {
     int i;
     for (i=0; i<2*(m+n); i++) {
         printf("%d ",boundary[i]);    
     }
     printf("\n");
}

int parenthesize(int left, int right) {
    // left inclusive, right exclusive; try to parenthesize the area [left,right)
    int twin1, twin2;
    
    // find the first location between left and right
    for (twin1=left; twin1<right && boundary[twin1]==0; twin1++);
    
    // if no location -> ok parenthesizing: empty
    if (twin1 >= right) return 1;
    
    for (twin2=twin1+1; twin2<right && boundary[twin1]!=boundary[twin2]; twin2++);
    
    // found twin? -> if not, then no solution
    if (!(twin2<right && boundary[twin1] == boundary[twin2])) return 0;
    
    // solve recursively the left and right subproblem -> if not possible, then no solution
    if (!parenthesize(twin1+1,twin2) || !parenthesize(twin2+1,right)) return 0;
    
    // assume parenthesizing also created pipe connections
    // now need to connect the twins
    
    return connect(twin1,twin2);                          
}

int main() {
    int i,j,k,s,t;
       
    scanf("%d",&k);
    
    for (; k>0; k--) {
        // input
        scanf("%d %d %d",&m,&n,&p);
        // printf("%d %d %d\n",m,n,p);
        
        // init
        for (i=0; i<2*(m+n); i++) {
            boundary[i] = 0;
        }
        
        for (i=0; i<=m+1; i++) {
            for (j=0; j<=n+1; j++) {
                board[i][j] = 0;        
            }
        }
        
        // init boundary of the board to inaccessible
        
        for (i=0; i<=m+1; i++) {
            board[i][0] = -1;
            board[i][n+1] = -1;    
        }
        
        for (j=0; j<=n+1; j++) {
            board[0][j] = -1;
            board[m+1][j] = -1;    
        }
        
        // init directions, counterclockwise
        
        dr[0] = 1; dc[0] = 0;
        dr[1] = 0; dc[1] = 1;
        dr[2] = -1; dc[2] = 0;
        dr[3] = 0; dc[3] = -1;
        
        // rest of the input
        for (i=0; i<p; i++) {
            scanf("%d %d",&s,&t);
            boundary[s-1] = i+1;
            boundary[t-1] = i+1;
        }
        
        // printBoundary();
        
        // check parenthesizing, along the way fill in the pipe connections
        if (!parenthesize(0,2*(m+n))) printf("NO\n");
        else printf("YES\n");      
        
        // printBoard2();
    }
    
    if (DEBUG) scanf("%d",&i);
    return 0;   
}
