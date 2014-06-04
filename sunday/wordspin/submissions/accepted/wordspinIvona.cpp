#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

#define MAX 10000005

long n;

char word1[MAX];
char word2[MAX];

int dif[MAX];

long count;

void printDif() {
    long i;

    for (i=0; i<n; i++) printf(" %2d",dif[i]);
    printf("\n");     
}

// compute the nearest shift, start from position left
int computeNextShift(long &left) {
    long i,j;
    int d,min;

    // find the first position that needs to be shifted
    for (i=left; i<n && dif[i]==0; i++);

    if (i>=n) return 0; // no shift needed

    // shifting up or down?
    if (dif[i]>0) d = 1;
    else d = -1;

    // compute [i,j), the largest interval starting at i where all difs have the same sign
    // also compute the min required shift by any of the letters in the interval
    min = 27;
    for (j=i; j<n && d*dif[j]>0; j++) {
        if (min>d*dif[j]) min = d*dif[j];
    }

    left = i;

    // update the dif by shift by min (in the correct direction)
    for (; i<j; i++) {
        dif[i] -= d*min;
    }

    // return the number of shifts done: min
    return min;     
}

int main() {
    int k,sd;
    long left;

    // input
    scanf("%s %s",word1,word2);

    // compute string difference
    n = 0;
    while (word1[n] > 0) {
        dif[n] = word1[n]-word2[n];
        n++;
    }

    count = 0;
    left = 0;
    sd = 1;

    while (sd > 0) {
        sd = computeNextShift(left);
        count += sd;
    }
    printf("%ld\n",count);

    return 0;   
}
