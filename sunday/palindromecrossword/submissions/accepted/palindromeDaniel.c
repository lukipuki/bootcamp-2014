#include <stdio.h>

#define MAXN 100

int N;

char BU[MAXN+10];

// crossword
char A[MAXN][MAXN];

// length of the longest
int L[MAXN][MAXN][MAXN][MAXN];

// where from 1-first coord, 2-second coord
int W[MAXN][MAXN][MAXN][MAXN][2];

int t,k,n,i,j,i1,i2,j1,j2,w;

int bi1,bi2,bj1,bj2,mw;

void priso(int i1,int i2,int j1,int j2) {
	int i3,i4,j3,j4;
	
	if ((i1==j1)&&(i2==j2)) {
		printf("%c",A[i1][i2]);
		return;
	}
	
	if (j1-i1+j2-i2==1) {
		printf("%c%c",A[i1][i2],A[j1][j2]);
		return;		
	}
	i3=i1; i4=i2; j3=j1; j4=j2;
	if (W[i1][i2][j1][j2][0]==1) i3++; else i4++;
	if (W[i1][i2][j1][j2][1]==1) j3--; else j4--;
	
	printf("%c",A[i1][i2]);
	priso(i3,i4,j3,j4);
	printf("%c",A[j1][j2]);		
}

void priso2(int i1,int i2,int j1,int j2) {
	int i3,i4,j3,j4;
	
	if ((i1==j1)&&(i2==j2)) {
		return;
	}
	
	if (j1-i1+j2-i2==1) {
		if (j1-i1) printf("D"); else printf("R");
		return;		
	}
	i3=i1; i4=i2; j3=j1; j4=j2;
	if (W[i1][i2][j1][j2][0]==1) i3++; else i4++;
	if (W[i1][i2][j1][j2][1]==1) j3--; else j4--;
	
	if (W[i1][i2][j1][j2][0]==1) printf("D"); else printf("R");
	priso2(i3,i4,j3,j4);
	if (W[i1][i2][j1][j2][1]==1) printf("D"); else printf("R");		
}

int main() {
	scanf("%d",&k);
	
	for (t=0;t<k;t++) {
		scanf("%d",&N);
		for (i=0;i<N;i++) {
			scanf("%s\n",&BU);
			for (j=0;j<N;j++) A[i][j]=BU[j]; 
		}
		
	    // inicializacia
		for (i1=0;i1<N;i1++) for (i2=0;i2<N;i2++) for (j1=0;j1<N;j1++) for (j2=0;j2<N;j2++) L[i1][i2][j1][j2]=0;	    
	    
	    mw=0; bi1=1; bi2=1; bj1=1; bj2=1;
	    
		for (i1=0;i1<N;i1++) for (i2=0;i2<N;i2++) {
		   L[i1][i2][i1][i2]=1; 
		   
		   j1=i1; j2=i2+1;
		   if (j2<N) {
		     if (A[i1][i2]==A[j1][j2]) {
		     	L[i1][i2][j1][j2]=1; mw=1; bi1=i1; bi2=i2; bj1=j1; bj2=j2;
		     	W[i1][i2][j1][j2][0]=0;
		     	W[i1][i2][j1][j2][1]=0;
		     }
		   }
		   
		   j1=i1+1; j2=i2;
		   if (j1<N) {
		     if (A[i1][i2]==A[j1][j2]) {
		   		L[i1][i2][j1][j2]=1; mw=1; bi1=i1; bi2=i2; bj1=j1; bj2=j2;
		     	W[i1][i2][j1][j2][0]=0;
		     	W[i1][i2][j1][j2][1]=0;  	
		     }
		   }
		}
		
		// vypocet
		
		for (w=2;w<=2*N;w++) {
		  for (i1=0;i1<N;i1++) for (i2=0;i2<N;i2++) {
		  	
		  	for (j1=i1;(j1<=i1+w)&&(j1<N);j1++) {
		  		j2=i2+(w-(j1-i1));
		  		if (j2<N) {
		  			// compute [i1,i2,j1,j2]	
		  			if (A[i1][i2]==A[j1][j2]) {
		  				
		  				if ((i1+1<N)&&(j1-1>=0)&&(L[i1+1][i2][j1-1][j2])) {
		  					L[i1][i2][j1][j2]=1; mw=w; bi1=i1; bi2=i2; bj1=j1; bj2=j2;
		  					W[i1][i2][j1][j2][0]=1;
		  					W[i1][i2][j1][j2][1]=1;
		  				}
		  				if ((i1+1<N)&&(j2-1>=0)&&(L[i1+1][i2][j1][j2-1])) {
		  					L[i1][i2][j1][j2]=1; mw=w; bi1=i1; bi2=i2; bj1=j1; bj2=j2;
		  					W[i1][i2][j1][j2][0]=1;
		  					W[i1][i2][j1][j2][1]=2;
		  				}		  				
		  				if ((i2+1<N)&&(j1-1>=0)&&(L[i1][i2+1][j1-1][j2])) {
		  					L[i1][i2][j1][j2]=1; mw=w; bi1=i1; bi2=i2; bj1=j1; bj2=j2;
		  					W[i1][i2][j1][j2][0]=2;
		  					W[i1][i2][j1][j2][1]=1;
		  				}
		  				if ((i2+1<N)&&(j2-1>=0)&&(L[i1][i2+1][j1][j2-1])) {
		  					L[i1][i2][j1][j2]=1; mw=w; bi1=i1; bi2=i2; bj1=j1; bj2=j2;
		  					W[i1][i2][j1][j2][0]=2;
		  					W[i1][i2][j1][j2][1]=2;
		  				}		  				
		  			}		  			
		  		}
		  	}
		  }
		}
		
		/*
		for (i1=0;i1<N;i1++) {
			for (i2=0;i2<N;i2++) {
				printf("%c",A[i1][i2]);	
			}
			printf("\n");
		}
		*/
		
		priso(bi1,bi2,bj1,bj2);
		printf(" %d %d ",bi1+1,bi2+1);
		priso2(bi1,bi2,bj1,bj2);	
		printf("S\n");	
		// ***************************
		
	}
}
