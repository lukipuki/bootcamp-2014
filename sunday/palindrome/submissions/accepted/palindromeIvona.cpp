#include <stdio.h>
#include <stdlib.h>

#define MAX 105
#define DEBUG 0

int N;
char a[MAX][MAX];
int s[MAX][MAX][MAX][MAX];

char contA[MAX][MAX][MAX][MAX];
char contB[MAX][MAX][MAX][MAX];

char sss[2*MAX];
char path[2*MAX];

int findSol(char *sss, char *path, int i, int j, int ii, int jj, int length) {
    int t, ti, tj, tii, tjj;
    
    // printf("i,j,ii,jj = %d %d %d %d\n",i,j,ii,jj);

    for (t=0; t<length; t++) {
        sss[t] = '.';
        if (t<length-1) path[t] = '.';
    }
    
    t = 0;
    while (t < (length-1)/2) {
        // printf("%d %s %s\n",t,sss,path);
        sss[t] = a[i][j];
        sss[length-1-t] = a[i][j];
    
        path[t] = contA[i][j][ii][jj];
        path[length-2-t] = contB[i][j][ii][jj];
        // printf("%d %d %d %d cont: %c %c\n",i,j,ii,jj,contA[i][j][ii][jj],contB[i][j][ii][jj]);
        ti = i;
        tj = j;
        tii = ii;
        tjj = jj;
        if (contA[ti][tj][tii][tjj] == 'D') i++;
        else j++;
        if (contB[ti][tj][tii][tjj] == 'D') ii--;
        else jj--;
           
        t++;
    }
    
    sss[t] = a[i][j];
    if (length%2==0) {
       sss[t+1] = a[i][j];
       path[t] = contA[i][j][ii][jj];                 
    }

    return 0;
}

int main() {
    int k,i,j,ii,jj,di,dj,max,maxi,maxj,maxii,maxjj;
    
    // input
    scanf("%d",&k);
    
    for (; k>0; k--) {
        scanf("%d",&N);
        for (i=0; i<N; i++) {
            scanf("%s",a[i]);
        }

        // s[i][j][ii][jj] = max length of a palindrome that starts at i,j and ends at ii,jj

        // init s to undef.
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                for (ii=i; ii<N; ii++) {
                    for (jj=j; jj<N; jj++) {
                        s[i][j][ii][jj] = 0;
                        contA[i][j][ii][jj] = '.';
                        contB[i][j][ii][jj] = '.';
                    }
                }
            }
        }
        // init palindromes of length 1 and 2
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                s[i][j][i][j] = 1;
                if (i+1<N && a[i][j]==a[i+1][j]) {
                   s[i][j][i+1][j] = 2;
                   contA[i][j][i+1][j] = 'D';
                   contB[i][j][i+1][j] = 'D';
                }
                if (j+1<N && a[i][j]==a[i][j+1]) {
                   s[i][j][i][j+1] = 2;
                   contA[i][j][i][j+1] = 'R';
                   contB[i][j][i][j+1] = 'R';
                }
            }
        }

        // for general i,j,ii,jj
        for (di=0; di<N; di++) {
            for (dj=0; dj<N; dj++) {
                for (i=0; i<N; i++) {
                    for (j=0; j<N; j++) {
                        ii = i+di;
                        jj = j+dj;
                        if (ii<N && jj<N && s[i][j][ii][jj]==0 && a[i][j]==a[ii][jj]) {
                           // s>0 only for cases initialized above, we do not need to deal with them anymore
                           // palindrome can be formed only if the start and end letter agree
                           
                           // try i+1,j -> ii-1,jj
                           if (i+1<N && ii-1>=0 && s[i+1][j][ii-1][jj]>0) {
                              if (s[i][j][ii][jj] < 2+s[i+1][j][ii-1][jj]) {
                                 s[i][j][ii][jj] = 2+s[i+1][j][ii-1][jj];
                                 // printf("A updating %d %d %d %d to %d\n",i,j,ii,jj,s[i][j][ii][jj]);
                                 contA[i][j][ii][jj] = 'D';
                                 contB[i][j][ii][jj] = 'D';
                              }
                           }

                           // try i+1,j -> ii,jj-1
                           if (i+1<N && jj-1>=0 && s[i+1][j][ii][jj-1]>0) {
                              if (s[i][j][ii][jj] < 2+s[i+1][j][ii][jj-1]) {
                                 s[i][j][ii][jj] = 2+s[i+1][j][ii][jj-1];
                                 // printf("B updating %d %d %d %d to %d\n",i,j,ii,jj,s[i][j][ii][jj]);
                                 contA[i][j][ii][jj] = 'D';
                                 contB[i][j][ii][jj] = 'R';
                              }
                           }

                           // try i,j+1 -> ii-1,jj
                           if (j+1<N && ii-1>=0 && s[i][j+1][ii-1][jj]>0) {
                              if (s[i][j][ii][jj] < 2+s[i][j+1][ii-1][jj]) {
                                 s[i][j][ii][jj] = 2+s[i][j+1][ii-1][jj];
                                 // printf("C updating %d %d %d %d to %d\n",i,j,ii,jj,s[i][j][ii][jj]);
                                 contA[i][j][ii][jj] = 'R';
                                 contB[i][j][ii][jj] = 'D';
                              }
                           }

                           // try i,j+1 -> ii,jj-1
                           if (j+1<N && jj-1>=0 && s[i][j+1][ii][jj-1]>0) {
                              if (s[i][j][ii][jj] < 2+s[i][j+1][ii][jj-1]) {
                                 s[i][j][ii][jj] = 2+s[i][j+1][ii][jj-1];
                                 // printf("D updating %d %d %d %d to %d; %c %c\n",i,j,ii,jj,s[i][j][ii][jj],a[i][j],a[ii][jj]);
                                 contA[i][j][ii][jj] = 'R';
                                 contB[i][j][ii][jj] = 'R';
                                 // printf("updating cont: %c %c\n",contA[i][j][ii][jj],contB[i][j][ii][jj]);
                              }
                           }
                        }
                    }
                }                
            }
        }

        // find the max
        max = 0;
        maxi = -1;
        maxj = -1;
        maxii = -1;
        maxjj = -1;                
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                for (ii=i; ii<N; ii++) {
                    for (jj=j; jj<N; jj++) {
                        if (max < s[i][j][ii][jj]) {
                           max = s[i][j][ii][jj];
                           maxi = i;
                           maxj = j;
                           maxii = ii;
                           maxjj = jj;
                        }
                    }
                }
            }
        }        

        // printf("max = %d %d %d %d %d\n",max,maxi,maxj,maxii,maxjj);

        // reconstruct the solution
        sss[max] = 0;
        path[max-1] = 'S';
        path[max] = 0;
        findSol(sss,path,maxi,maxj,maxii,maxjj,max);
        printf("%s %d %d %s\n",sss,maxi+1,maxj+1,path);
    }
    
    if (DEBUG) scanf("%d",&i);
    return 0;   
}
