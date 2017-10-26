/* 
CS288 HOMEWORK 8
Your program will take in two command-line parameters: n and error
command: jacobi 5 0.0001
command: jacobi 10 0.000001
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define N 100
#define MAX_ITER 10000

int jacobi();
void init();
int convergence();
void srand();
void print_vector();
void print_equation();

float a[N][N], b[N];
float x[N], buf[N];
int n;
float error;

int main(int argc, char **argv){
    int n_iter;			/* number of iterations */
    n = atoi(argv[1]);
    error = atof(argv[2]);

    init();		   /* initalize a, x0 and b - DO not change */
    // a[0][0]=2;
    // a[0][1]=1;
    // a[1][0]=5;
    // a[1][1]=7;
    // x[0]=1;
    // x[1]=1;
    // b[0]=11;
    // b[1]=13;
    int i;
    for(i=0;i<MAX_ITER;i++){
        n_iter = jacobi();
        if(convergence()){
            printf("Converged, %d iterations",i);
            break;
        }
        
    }
    printf("-------------------------------------------------------\n");
    if(i==MAX_ITER&&!convergence()){
        printf("Solution Didn't converge under iterations and error bound'");
        return 0;
    }
    printf("\nSolution Approximation:\n");
    for(i=0;i<n;i++) printf("X_%d=%f\n",i,buf[i]);
    return 0;
}

int jacobi(){
    int i,j,k;
    float sum;
    for(i=0;i<n;i++){
        buf[i]=0;
        for(j=0;j<n;j++){
            sum=0;
            //printf("sum=");
            for(k=0;k<n;k++){
                float d_ = i!=k ? 0 : 1/a[i][k];
                float r_ = j==k ? 0 : -a[k][j]; 
                //printf("%f*%f + ",d_,r_);
                sum+=d_*r_;
            }
            //printf("==%f \n",sum);
            buf[i]+= sum*x[j];
            
            //printf("SUM:%f,X_:%f,BUF:%f\n\n",sum,x[j],buf[i]);
        }
        //printf("%f+%f=%f\n\n",buf[i],b[i]/a[i][i],buf[i]+b[i]/a[i][i]);
        buf[i]+=b[i]/a[i][i];
        //printf("X_%d=%f\n",i,buf[i]);
        
    }
    for(i=0;i<n;i++){
        x[i]=buf[i];
    }
    return 0;
}

// returns 1 if converged else 0
int convergence(int iter){
    int i,j,k,flag=1;
    float sum;
    //printf("\nErrorBound:%f\n",error);
    for(i=0;i<n;i++){
        buf[i]=0;
        for(j=0;j<n;j++){
            sum=0;
            //printf("Tx[%d][%d]=",i,j);
            for(k=0;k<n;k++){
                float d_ = i!=k ? 0 : 1/a[i][k];
                float r_ = j==k ? 0 : -a[k][j]; 
                //printf("%f*%f + ",d_,r_);
                sum+=d_*r_;
            }
            //printf("%f ",Tx[i][j]);
            buf[i]+= sum*x[j];
        }
        buf[i]+=b[i]/a[i][i];
    }
    for(i=0;i<n;i++){
        float diff=x[i]-buf[i];
        //printf("Diff:%f,DiffABS:%f, ErrVal:%d\n",diff,fabs(diff),(error<fabs(diff)));
        if( diff!=0 && (error<fabs(diff)) )
            return 0;
    }
    return 1;
}

// Try not to change this. Use it as is.
void init(){
    int i,j,k,flag=0;
    float sum;
    int seed = time(0) % 100;	/* seconds since 1/1/1970 */
    //int seed =1234;
    srand(seed);
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++) {
            a[i][j] = rand() & 0x7;
            if (rand() & 0x1) a[i][j] = -a[i][j];
            
        }
        if(a[i][i]==0) a[i][i]++;
        sum = 0;
        for (j=0;j<n;j++) if(i!=j) sum = sum + abs(a[i][j]);
        //printf("\nA:%f, SUM:%f\n",a[i][i],sum);
        if (abs(a[i][i]) < sum) a[i][i] = sum*(a[i][i]/abs(a[i][i])) + a[i][i];
    }

    for (i=0;i<n;i++) x[i]=1;

    srand(seed);
    for (i=0;i<n;i++){
        b[i]=rand() & 0x7;
        if (rand() & 0x1) b[i] = -b[i];
    }

    print_equation();

}

void print_equation(){
    int i,j;

    printf("A*x=b\n");
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++) printf("%2d ",(int)(a[i][j]));
            printf(" * x_%d = %d\n",i,(int)(b[i]));
        }
        printf("\n");
    }

void print_vector(float *l){
    int i;
    for (i=0; i<n; i++) printf("%.6f ",l[i]);
    printf("\n");
}

// end of file