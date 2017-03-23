#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 100

struct clip *build_a_lst();
struct clip *append();
int find_length();
void print_a_lst();
void split_line();

struct clip {
	int views;
	char *user;
	char *id;
	char *title;
	struct clip *next;
} 	*head;

int main(int argc, char **argv) {
	int n;
	head = build_a_lst(*(argv+1));
	//n = find_length(head);./
	print_a_lst(head);		/* prints the table */
	return 0;
}

struct clip *build_a_lst(char *fn) {
	FILE *fp=fopen(fn,"r");;
	struct clip *hp;
	char *fields[5];
	char line[LINE_LENGTH];
	int cnt=0;
	hp=NULL;
	if(fp!=NULL){
		//find out how long the longest line is to effeciently use memory
		//also count up lines as while(!feof()) doubles the last line
		int longestLine=0,tempLLine=0,lines=1;
		while(!feof(fp)){
			if(fgetc(fp)=='\n'){
				tempLLine=0;
				lines++;
			}
			if(tempLLine>longestLine)
				longestLine=tempLLine;
			tempLLine++;	
		}
		fp=fopen(fn,"r");
		for(int i=0;i<lines;i++){
			char line[longestLine];
			fgets(line,longestLine,fp);
			split_line(fields,line);
			hp=append(hp,fields);
		}
		
	}
	else
		printf("File: %s Not Found\n",fn);
	// open fn
	// while no more lines
	// read a line
	// split the line into four substrings/int and store them in a struct
	// append - add the struct at the end of the list
	// return the head pointer holding the list

	return hp;
}

/* fields will have four values stored upon return */
void split_line(char **fields,char *line) {
	int fieldSize=5;
	char *token, *delim;
	delim = ",\n";
	token=strtok(line,delim);
	int i=0;
	while(token!=NULL){
		fields[i]=token;
		token=strtok(NULL,delim);
		i++;
	}
	/* 
		call strtok(line, delim);
		repeat until strtok returns NULL using strtok(NULL, delim);
	*/
}
/* set four values into a clip, insert a clip at the of the list */
struct clip *append(struct clip *hp,char **five) {
	// printf("%d,%d,%d\n",sizeof(five[1]),sizeof(five[0]),sizeof(five[4]));
	// printf("%d,%d,%d\n",strlen(five[1]),strlen(five[0]),strlen(five[4]));
	// printf("%s,\t%s,\t%s\n",five[1],five[0],five[4]);
  	struct clip *cp,*tp;
	//create a new struct to put at the end of the chain provided by hp
	tp=malloc(sizeof(struct clip));
	tp->views=atoi(five[2]);

	tp->user=malloc(strlen(five[1])+1);
	strcpy(tp->user,five[1]);

	tp->title=malloc(strlen(five[0])+1);
	strcpy(tp->title,five[0]);  

	tp->id=malloc(strlen(five[4])+1);
	strcpy(tp->id,five[4]);

	tp->next=NULL;	
	if(hp==NULL){
		hp=tp;
	}
	else{
		cp=hp;
		while(cp->next!=NULL){
			cp=cp->next;
		}
		cp->next=tp;
	}
	/* 
		malloc tp
		set views using atoi(*five)
		malloc for four strings.
		strcpy four strings to tp
		insert tp at the end of the list pointed by hp
		use cp to traverse the list
	*/

  	return hp;
}

void print_a_lst(struct clip *cp) {
	if(cp==NULL){
		printf("Null Head Pointer");
		return;
	}
	struct clip *tp=cp;
	do{
		printf("%s %s %d %s\n",tp->title,tp->user,tp->views,tp->id);
		tp=tp->next;
	} 
	while(tp!=NULL);
	/* 
		use a while loop and the statement below to print the list
	*/
}

/* end */