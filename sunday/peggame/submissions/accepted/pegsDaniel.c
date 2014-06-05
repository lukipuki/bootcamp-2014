#include <stdio.h>

#define MN 25

#define BAD 10000

// najvacsie mnozstvo striktne nad ciarou
// zacinajucou na b1 ... b2 b3
int A[MN][MN][MN][MN][MN][MN];
// najvacsie mnozstvo striktne pod ciarou
// zacinajucou na b1 ... b2 b3
int B[MN][MN][MN][MN][MN][MN];


int N;
int V[MN][MN];

// hodnote striktne pod a nad bodom
int WA[MN][MN],WB[MN][MN];

// hodnota striktne pod a nad, prve indexy sa lisia of >=1 
// oba koncove body su zaratane
int VA[MN][MN][MN][MN],VB[MN][MN][MN][MN];

// hodnota v stlcoch
int ST[MN][MN],STT[MN];

// minimalna hodnota striktne pod a nad, prve indexy sa lisia of >=1 
// oba koncove body su zaratane
int BVA[MN][MN][MN][MN],BVB[MN][MN][MN][MN];

int main() {
    int k,s1,s2,s3,t1,t2,t3,i,j,t,p1,p2,Q,BEST,W,r1,r2,Q2,Q3,TU,TO;
    
    scanf("%d",&k);
    
    for (i=0;i<k;i++) {
        scanf("%d",&N);
        for (s1=0;s1<N;s1++) for (s2=0;s2<N;s2++) { scanf("%d",&(V[s1][s2])); V[s1][s2]=2*V[s1][s2]-1; }
        
        // vypocitaj pod/nad bodmi
        for (s1=0;s1<N;s1++) for (s2=0;s2<N;s2++) {
           WA[s1][s2]=0; WB[s1][s2]=0;
           for (t=0;t<s2;t++) WB[s1][s2]+=V[s1][t];
           for (t=s2+1;t<N;t++) WA[s1][s2]+=V[s1][t];
        }
        
        // vypocitaj pod/nad useckami
        for (s1=0;s1<N;s1++) for (s2=0;s2<N;s2++) for (t1=s1+1;t1<N;t1++) for (t2=0;t2<N;t2++) {
           VA[s1][s2][t1][t2]=WA[s1][s2]+WA[t1][t2]; 
           VB[s1][s2][t1][t2]=WB[s1][s2]+WB[t1][t2];
           
           for (p1=s1+1;p1<t1;p1++) for (p2=0;p2<N;p2++) {
             Q = p2*t1-p2*s1-s2*t1+t2*s1-t2*p1+s2*p1;
             if (Q>0) VA[s1][s2][t1][t2]+=V[p1][p2];
             if (Q<0) VB[s1][s2][t1][t2]+=V[p1][p2];              
           }
           
           BVA[s1][s2][t1][t2]=VA[s1][s2][t1][t2];
           BVB[s1][s2][t1][t2]=VB[s1][s2][t1][t2];
        } 
          
        // vypocitaj sucty v stlpcoch    
        for (s1=0;s1<N;s1++) {
          STT[s1]=0; 
          for (s2=0;s2<N;s2++) STT[s1]+=V[s1][s2];
        }      
        for (s1=0;s1<N;s1++) 
          for (t1=s1;t1<N;t1++) {
            ST[s1][t1]=0;
            for (p1=s1;p1<=t1;p1++) ST[s1][t1]+=STT[p1];
          }   
          
         /*
         printf("-----------------------\n");
         
         for (s2=N-1;s2>=0;s2--) {
           for (s1=0;s1<N;s1++)
             printf("%3d ",V[s1][s2]); 
           printf("\n");
         }
         
         */
         
        //printf("\n\n %d %d\n\n",BVA[0][0][19][0],BVB[0][0][19][0]);
         
        // inicialny stav 
        for (s1=0;s1<N;s1++) for (s2=0;s2<N;s2++) for (p1=s1+1;p1<N;p1++) for (p2=0;p2<N;p2++) for (t1=p1+1;t1<N;t1++) for (t2=0;t2<N;t2++) {
          Q = p2*t1-p2*s1-s2*t1+t2*s1-t2*p1+s2*p1;
          
          A[s1][s2][p1][p2][t1][t2] = BAD;
          B[s1][s2][p1][p2][t1][t2] = BAD; 
          
          if (Q>=0) {
            A[s1][s2][p1][p2][t1][t2] = VA[s1][s2][p1][p2] + VA[p1][p2][t1][t2] - WA[p1][p2]; 
            if (A[s1][s2][p1][p2][t1][t2]<BVA[s1][s2][t1][t2]) BVA[s1][s2][t1][t2]=A[s1][s2][p1][p2][t1][t2];
          }
          if (Q<=0) {
            B[s1][s2][p1][p2][t1][t2] = VB[s1][s2][p1][p2] + VB[p1][p2][t1][t2] - WB[p1][p2];
            if (B[s1][s2][p1][p2][t1][t2]<BVB[s1][s2][t1][t2]) BVB[s1][s2][t1][t2]=B[s1][s2][p1][p2][t1][t2];
          }
        }
        
        //printf("!!!!%d!!!!\n",BVA[0][3][4][2]);
        
        // dynamicke programovanie
        
        for (W=2;W<N;W++) {
          for (s1=0;s1<N-W;s1++) {
            t1=s1+W;
            for (s2=0;s2<N;s2++) if (V[s1][s2]==1) for (p1=s1+1;p1<t1;p1++) for (p2=0;p2<N;p2++) if (V[p1][p2]==1) 
			for (t2=0;t2<N;t2++) if (V[t1][t2]==1) {
              Q = p2*t1-p2*s1-s2*t1+t2*s1-t2*p1+s2*p1;
              if (Q>=0) {
                for (r1=s1+1;r1<p1;r1++) 
                  for (r2=0;r2<N;r2++) if (V[r1][r2]==1) {
                      Q2 = r2*p1-r2*s1-s2*p1+p2*s1-p2*r1+s2*r1;
                      Q3 = p2*t1-p2*r1-r2*t1+t2*r1-t2*p1+r2*p1;
                      if ((Q2>=0)&&(Q3>=0)) {
                         TU=A[s1][s2][r1][r2][p1][p2]+VA[p1][p2][t1][t2]-WA[p1][p2];
                         if (TU<A[s1][s2][p1][p2][t1][t2]) {
                           A[s1][s2][p1][p2][t1][t2]=TU;
                           if (TU<BVA[s1][s2][t1][t2]) BVA[s1][s2][t1][t2]=TU;                           
                         }
                      }
                  }      
              }
              if (Q<=0) {
                for (r1=s1+1;r1<p1;r1++) 
                  for (r2=0;r2<N;r2++) if (V[r1][r2]==1) {
                      Q2 = r2*p1-r2*s1-s2*p1+p2*s1-p2*r1+s2*r1;
                      Q3 = p2*t1-p2*r1-r2*t1+t2*r1-t2*p1+r2*p1;
                      if ((Q2<=0)&&(Q3<=0)) {
                         TU=B[s1][s2][r1][r2][p1][p2]+VB[p1][p2][t1][t2]-WB[p1][p2];
                         if (TU<B[s1][s2][p1][p2][t1][t2]) {
                           B[s1][s2][p1][p2][t1][t2]=TU;
                           if (TU<BVB[s1][s2][t1][t2]) BVB[s1][s2][t1][t2]=TU;                         
                         }
                      }
                  }                          
              }            
            }  
          }        
        }
        
        
        // finalny vypocet
        BEST=0;
        
        // iba stlpec
        for (s1=0;s1<N;s1++) {
          for (s2=0;s2<N;s2++) for (s3=s2;s3<N;s3++) {
              Q=0;
              for (t=s2;t<=s3;t++) Q+=V[s1][t];
              if (Q>BEST) BEST=Q; 
          }        
        }
        
        // sirsia vec; [s1,s2] do [t1,t2] a potom [s1,s3] so [t1,t3] 
        for (s1=0;s1<N;s1++) for (t1=s1+1;t1<N;t1++) {
          for (s2=0;s2<N;s2++) for (s3=s2;s3<N;s3++) for (t2=0;t2<N;t2++) for (t3=t2;t3<N;t3++) 
		
		  if ((V[s1][s2]==1)&&(V[t1][t2]==1)&&(V[s1][s3]==1)&&(V[t1][t3]==1))
		  
		  {
            Q=ST[s1][t1]-BVA[s1][s3][t1][t3]-BVB[s1][s2][t1][t2];
            if (Q>BEST) { BEST=Q; 
            
          /*   
              printf("\n");
              printf("above: %d %d %d %d %d\n",s1,s3,t1,t3,BVA[s1][s3][t1][t3]); 
              printf("below: %d %d %d %d %d\n",s1,s2,t1,t2,BVB[s1][s2][t1][t2]);
              */
            }
          } 
        }
        
        printf("%d\n",BEST);
    } 
}
