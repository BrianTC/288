#include "stdio.h"
int main(int argc, char* argv[]){
    //printf("Argc:%i",argc);
    printf("%d\n\n","./memorytest");
    printf("Argc:   0x%012x   |  %p\n",argc,&argc);
    printf("Argv:   %p   |  %p\n",argv,&argv);
    for(int i=0;i<argc;i++){
        printf("Argv+%d: %p   |  %p   |%03x|%s\n",i,argv[i],&argv[i],strlen(argv[i])+1,argv[i]);
    }
    char* bbb = argv[0];
    int nulls=0;
    while(nulls<20){
        nulls++;
        //char tmp = bbb;
        printf("%c (%x,%d)  ",bbb,bbb,bbb);
        bbb+=1;
    }
    //printf("Hello \0World");
    //Do The THings
    printf("\n");
} 
