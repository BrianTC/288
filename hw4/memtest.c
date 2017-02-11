#include "stdio.h"
#include "string.h"
void printContentsArgv();
void printAddressArgv();
void printSpaceLine();
void printSpaceLine_addr();
void printContentsCharPtr();
int main(int argc, char* argv[]){
    printSpaceLine_addr("0xffffffffffff");
    printSpaceLine();
    printSpaceLine();
    printContentsArgv(argc,argv,0);
    printSpaceLine();
    printSpaceLine();
    printAddressArgv(argc,argv);
    printSpaceLine();
    printSpaceLine_addr("0x000000000000");
    printf("\n\n\n\n");

    printSpaceLine_addr("0xffffffffffff");
    printSpaceLine();
    printSpaceLine();
    printContentsArgv(argc,argv,1);
    printSpaceLine();
    printSpaceLine();
    printAddressArgv(argc,argv);
    printSpaceLine();
    printSpaceLine_addr("0x000000000000");
    printf("\n");
}

//This function is to create the base 
void printAddressArgv(int argc, char *argv[]){
    for(int i=argc-1;i>=0;i--){
        char loopString[16];
        sprintf(loopString,"Argv+%02d: ",i);
        printContentsCharPtr(loopString,argv[i],&argv[i]);
        printSpaceLine();
    }
        printSpaceLine();
        printSpaceLine();
        printContentsCharPtr("Argv:    ",argv,&argv);
        printSpaceLine();
        printContentsCharPtr("Argc:    ",argc,&argc);
        printSpaceLine();
}

//This function is to make the format for
//Argc:    | 00 | 00 | 00 | 00 | 00 | 05 | 0x7ffe77ea362c
//
void printContentsCharPtr(char *name,char* memloc[],long address){
        char tString[15];
        sprintf(tString,"0x%012lx",(long int) memloc);
        printf("%s",name);
        for(int i=2;i<strlen(tString);i+=2){
            printf("| %c%c ",tString[i],tString[i+1]);
        }
        printf("| 0x%012lx\n",address);
}

//
//Prints out the values contained in argv
//last parameter is to print out ascii characters
//or ascii values ie '61' or 'a'
void printContentsArgv(int argc, char* argv[],int asciiSwitch){
    char* bbb = argv[0];
    int nulls=0;
    int numChars=0;
    int addr_width=6;
    while(nulls<argc){
        numChars++;
        if(*bbb=='\0')
            nulls++;
        bbb+=1;
    }
    //celing division a thing?
    int addr_rows = numChars/addr_width;
    addr_rows+= (numChars%addr_width>0 ? 1 : 0);

    bbb--;
    int offset=addr_rows*addr_width-numChars;
    bbb+=offset;
    for(int i=0;i<addr_rows*addr_width;i++){
        if((i)%addr_width==0)
            printf("%*s",9,"");
        //Pad Phase
        if(i<offset){
             printf("| -- ");
             continue;
        }
        //Print Phase
        char cchar= *(bbb-(i));
        if(asciiSwitch){
            if(cchar=='\0')
                printf("| \\0 ");
            else
                printf("| %2c ",cchar);
        }
        else
            printf("| %02x ",cchar);
        //Finish Row
        if((i+1)%addr_width==0){
            printf("| %p \n",bbb-i);
            printSpaceLine();
        }
    }
}
void printSpaceLine_addr(char* addr_s){
    printf("%*s+----+----+----+----+----+----+ %s\n",9,"",addr_s);
}
void printSpaceLine(){
    printSpaceLine_addr("");
}
