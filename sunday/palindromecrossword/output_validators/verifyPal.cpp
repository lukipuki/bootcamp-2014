#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define MAX 105
#define DEBUG 0

int N;
char a[MAX][MAX];

char sssUs[2*MAX];
char sss[2*MAX];
char path[2*MAX];
char pathUs[2*MAX];

int main(int argc, char *argv[]) {
    int k,i,j,ui,uj,t,length;
    FILE *fin,*fout,*ftheir;
    
    if (argc != 4) {
       printf("usage: input official_output their_output\n");
       return 1;
    }
    
    fin = fopen(argv[1],"rt");
    fout = fopen(argv[2],"rt");
    ftheir = stdin;
    //ftheir = fopen(argv[3],"rt");
    std::string judgeout(argv[3]);
    judgeout += "judgemessage.txt";
    freopen(judgeout.c_str(), "w", stdout);
    
    // read input
    fscanf(fin,"%d",&k);
    
    for (; k>0; k--) {
        fscanf(fin,"%d",&N);
        for (i=0; i<N; i++) {
            fscanf(fin,"%s",a[i]);
        }
        
        fscanf(fout,"%s %d %d %s",sssUs,&ui,&uj,path);
        if (fscanf(ftheir,"%s %d %d %s",sss,&i,&j,path)<4) {
           printf("Output of incorrect form, cannot read it\n");
           return 43;
        }
        
        if (i<=0 || i>N || j<=0 || j>N) {
           printf("Problem with starting coordinates: %d,%d\n",i,j);
           return 43;
        }
                              
        if (strlen(sssUs)!=strlen(sss)) {
           printf("Different string lengths: %s (expected) %s (their output)\n",sssUs,sss);
           return 43;
        }
        
        length = strlen(sssUs);
        for (t=0; t<length/2; t++) {
            if (sss[t] != sss[length-1-t]) {
               printf("Not a palindrome: %s\n",sss);
               return 43;
            }    
        }
        
        i--;
        j--;
        for (t=0; t<length-1; t++) {
            if (sss[t] != a[i][j]) {
               printf("The %d-th symbol in %s is %c; position %d,%d contains %c\n",t+1,sss,sss[t],i+1,j+1,a[i][j]);
               return 43;           
            }
            if (path[t] == 'D') i++;
            else if (path[t] == 'R') j++;
            else {
                 printf("Incorrect direction %c\n",path[t]);
                 return 43;
            }
            
            if (i<0 || i>=N || j<0 || j>=N) {
               printf("Directions outside of crossword, sending to position: %d,%d\n",i,j);
               return 43;
            }
        }
        
        if (path[length-1] != 'S') {
           printf("Expecting 'S' at the end of directions\n");
           return 43;                   
        }
        
        if (sss[t] != a[i][j]) {
           printf("The %d-th symbol in %s is %c; position %d,%d contains %c\n",t+1,sss,sss[t],i+1,j+1,a[i][j]);
           return 43;           
        }
        
        if (path[length] != 0) {
           printf("Directions too long\n");
           return 43;                      
        }
    }
    
    printf("OK\n");
    
    if (DEBUG) scanf("%d",&i);
    return 42;   
}
