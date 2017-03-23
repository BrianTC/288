/* HW6 read cafefully and follow all the instructions/comments
   this program compiles and runs as is although it's not doing much.
   DO NOT CHANGE THE SEED. Changing seed gives a different sequence of
   numbers but we want the same numbers for comparison purposes.

   FLOATING point radix sort requires some substantial changes to this code
   float n, lst[N],tmp[N];	
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
#define NELM 100		/* default 100 elements */
//#define N 1048576		/* 2^30 or 1 meg elements  */
//#define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
#define N 635544320

void selection_sort();
void swap();

void merge_sort();
void msort_recursive();

void int_radix_sort();
void float_radix_sort();
void swap();
void self_check();

int rand(void);
void srand();
int rand_r();
void init_lst();
void print_lst();


// void binaryFromBounds(int a, int b){
// 	int mid = (b+a)/2;
// 	if((b-a)<2){
// 		printf("BASE: A:%i, MID:%i, B:%i\n\n",a,mid,b);
// 		return;
// 	}
// 	printf("A:%i, MID:%i, B:%i\n",a,mid,b);
// 	binaryFromBounds(a,mid);
// 	binaryFromBounds(mid,b);
// }

int n, lst[N], buf[N];
int main(int argc,char **argv) {
	int n;
	long int del_sec,del_msec;
	clock_t diff;
	//  struct timeval tv_s,tv_e;

	if (argc>1) n = atoi(argv[1]);
	else n = NELM;
	printf("n=%d\n",n);
	printf("cps=%ld\n",CLOCKS_PER_SEC);
	//init_lst(lst,n);
	//print_lst(lst,n);

	printf("Selection Sort:\n");
	diff=clock();
	selection_sort(lst,n);
	diff=clock()-diff;
	printf("Time Taken For Selection Sort:%li\n",diff);
	//print_lst(lst,n);
	self_check(lst,n);

	printf("Merge Sort:\n");
	init_lst(lst,n);
	printf("LINIT:\n");	
	diff=clock();
	merge_sort(lst,buf,n);
	diff=clock()-diff;
	printf("Time Taken For Merge Sort:%li\n",diff);
	// print_lst(lst,n);
	self_check(lst,n);

	printf("Raadix Sort:\n");
	init_lst(lst,n);
	diff=clock();
		//print_lst(lst,n);
	int_radix_sort(lst,buf,n);
	diff=clock()-diff;
	printf("Time Taken For Radix Sort:%li\n",diff);
		//print_lst(lst,n);
	self_check(lst,n);

	//  float_radix_sort(lst,tmp,n);
	//  gettimeofday(&tv_e, NULL); 

	//binaryFromBounds(0,9);
	/****
		PRINT elapsed time in sec and milli secs
	****/

	//print_lst(lst,n);
	//self_check();
	return 0;
}

void selection_sort(int lst[],int n){
	int tempInt,tempPos;
	for(int i=0;i<n;i++){
		tempInt=lst[i];
		tempPos=i;
		for(int j=i;j<n;j++){
			if(lst[j]<tempInt){
				tempInt=lst[j];
				tempPos=j;
			}
		}
		lst[tempPos]=lst[i];
		lst[i]=tempInt;
	}
}

void merge_sort(int * lst, int *buf,int n){
	for(int i=0;i<n;i++) buf[i]=lst[i];
    msort_recursive(lst,buf,0,n);   
}
void msort_recursive(int *lst, int *buf, int iBegin, int iEnd )
{
    if(iEnd - iBegin < 2) 
        return;
    int iMiddle = (iEnd + iBegin) / 2;              
    msort_recursive(buf, lst, iBegin,  iMiddle);  
    msort_recursive(buf, lst, iMiddle,    iEnd);  
	//Merge Together
	int i = iBegin, j = iMiddle;
    for (int k = iBegin; k < iEnd; k++) {
        if (i < iMiddle && (j >= iEnd || buf[i] <= buf[j])) {
            lst[k] = buf[i];
            i = i + 1;
        } else {
            lst[k] = buf[j];
            j = j + 1;    
        }
    } 
}

//fix the bucket size to 256. run 4 passes where each pass processes 8 bits
//use lst and tmp only. do not use any more memory of size n.
void int_radix_sort(int *src,int *dst, int n) {
	int MASKSIZE=8;
	int BUCKETSIZE=265;
	int mask=0xFF;
	int	maskShift=0; 
	int tally[BUCKETSIZE];
	int placement[BUCKETSIZE];
	int *tmp;
	
	//int dst[n];
	while(mask!=0){
		////set controll arrays back to zero
		//printf("A\n");
		for(int i=0;i<BUCKETSIZE;i++){
			tally[i]=0;
			placement[i]=0;
		}
		////count the number of ends 
		//printf("B\n");
		for(int i=0;i<n;i++){
			tally[ (int)(src[i] & mask)>>maskShift]++;
			
		}
		////set move to positions
		//printf("C\n");
		int startAt=0;
		for(int i=0;i<BUCKETSIZE;i++){
			placement[i]+=startAt;
			startAt+=tally[i];
		}
		////re arrange array for next round of sorting
		//printf("D\n");
		for(int i=0;i<n;i++){
			dst[ placement[ (int)(src[i] & mask)>>maskShift ]++ ]=src[i];
		}
		tmp = src;
		src = dst;
		dst = tmp; 
		mask=mask<<MASKSIZE;
		maskShift+=MASKSIZE;
	}
}

void print_lst(int *l,int n){
  int i;
  for (i=0; i<n; i++) {
    printf("%d ",l[i]);
  }
  printf("\n");
}

void init_lst(int *l,int n){
  int i;
  //  int seed = time(0) % 100;	/* seconds since 1/1/1970 */
  //  printf ("seed=%d\n", seed);
  srand(1234);			/* SEED */
  for (i=0; i<n; i++) {
    l[i] = rand();
  }
}

void self_check(int *lst,int n) {
  int i,j,flag=OK,*lstp;

  lstp = lst;
  for (i=0;i<n-1;i++)
     if (lstp[i] > lstp[i+1]) { flag = NOK; break; }

  if (flag == OK) printf("sorted\n");
  else printf("NOT sorted at %d\n",i);
}

/* End of file */
