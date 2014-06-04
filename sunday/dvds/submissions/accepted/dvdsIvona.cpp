#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

long N;

int main() {
    long i,k,t,a;
    
    // input
    scanf("%d",&k);
    
    for (; k>0; k--) {
        scanf("%ld",&N);
        t = 1;
        for (i=0; i<N; i++) {
            scanf("%ld",&a);
            if (a==t) t++;
        }
        printf("%ld\n",N-t+1);
    }
    
    if (DEBUG) scanf("%d",&i);
    return 0;   
}
