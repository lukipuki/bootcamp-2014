#include <stdio.h>

char S[10000020],T[10000020];
int  R[10000020],W[10000020];

int K,i,j,k,N,Z,t;

int main() {
    scanf("%s %s",S,T);
    //printf("%s|%d\n",BUF1,strlen(BUF1));
    //printf("%s|%d\n",BUF2,strlen(BUF2));		
    N=strlen(S);
    for (i=0;i<N;i++) {
        R[i]=((int)T[i])-((int)S[i]);
        W[i]=0;
        if (R[i]>0) W[i]=+1;
        if (R[i]<0) { W[i]=-1; R[i]=-R[i]; }
    }
    R[N]=0;

    //for (i=0;i<N;i++) printf("%d ",R[i]*W[i]); printf("\n");

    Z=0;
    for (i=0;i<N;i++) {
        if (W[i]!=W[i+1]) {
            Z+=R[i]; //printf("{%d]",R[i]);
        } else {
            if (R[i]>R[i+1]) {
                Z+=(R[i]-R[i+1]); //printf("[%d]",R[i]-R[i+1]);
            }
        }
    }

    printf("%d\n",Z);
}
