//Connor Stewart
//Comstewa
//Lex.c
//this is a simple sort using an in and out file.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_STRING_LENGTH 100	
int main(int argc, char* argv[]){
	FILE* in;
	FILE* out;
   VAL_TYPE x;
   KEY_TYPE y;
	int count=0;
	KEY_TYPE wordset[MAX_STRING_LENGTH];
	//char *betbb[MAX_STRING_LENGTH][MAX_STRING_LENGTH];

//	List outlist=newList();
	if(argc!=3){
		fprintf(stderr, "Whoopsies looks like you put in more/less than the expected amount inputs!\n The correct input looks as follows: %s <input file> <output file>\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	in = fopen (argv[1], "r");	
	if(in == NULL){
		fprintf(stderr, " Yikes looks like I can't read the file %s \n", argv[1]);
		exit (EXIT_FAILURE);
	}
	out = fopen (argv[2], "w"); //see if write on out file

	if(out == NULL){
		fprintf(stderr, "Oof looks like I can't write to the file %s \n", argv[2]);
		exit(EXIT_FAILURE);
	}
	

	while(fgets(wordset, MAX_STRING_LENGTH, in) != NULL){	//read lines from in
		
		count++;
		
	}

	char *stringsA[count][MAX_STRING_LENGTH];	
	
	rewind(in);								//reset wordCount
	
	int yo=0;
	while(fgets (wordset, MAX_STRING_LENGTH, in) != NULL){
		char *pos;
		if ((pos=strchr(wordset, '\n')) != NULL){
    		*pos = '\0';
		}
		strcpy(stringsA[yo], wordset);

		yo++;
	}
		//again with the in file
		 					//placing word into array
		//count++;
	Dictionary A=newDictionary(0);
	for(int i=0; i<yo; i++){
		

    	insert(A, stringsA[i], NULL);
  	}
 
  	
  	printDictionary(out, A, "pre");
  	fprintf(out,"\n");
  	fprintf(out,"\n");

  	printDictionary(out, A, "in");
  	fprintf(out,"\n");
  	fprintf(out,"\n");
  	

  	printDictionary(out, A, "post");


   freeDictionary(&A);
	




	fclose(in);
	fclose(out);			//close out of files

	return (EXIT_SUCCESS);	
	

}
