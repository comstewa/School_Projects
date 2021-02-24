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
	//int i=0;
	//int n=1;
	//while(n>0){ 
	//	n=fscanf(in,"%s",wordset[i]);
	//	i++;

	//}cor

	while(fgets(wordset, MAX_STRING_LENGTH, in) != NULL){	//read lines from in
		//printf("%s\n",wordset );
		//strcpy(betbb[count],wordset);
		count++;
		//printf("%s\n",betbb[count] );

	
	//	printf(stderr,"%s",wordset);
	}

	char *stringsA[count][MAX_STRING_LENGTH];	
	//for(i;i>0;i--){
	//	stringsA[i]=wordset[i];
	//}
	//count = 0;		
	rewind(in);								//reset wordCount
	//while(fgets(wordset, MAX_STRING_LENGTH, in) != NULL){
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
  	//fprintf(out,"PRE\n" );
  	
  	printDictionary(out, A, "pre");
  	fprintf(out,"\n");
  	fprintf(out,"\n");

  	//fprintf(out,"IN\n" );
  	printDictionary(out, A, "in");
  	fprintf(out,"\n");
  	fprintf(out,"\n");
  	
  //	fprintf(out,"POST\n" );
  	printDictionary(out, A, "post");

	 //for(x=beginForward(A); currentVal(A)!=VAL_UNDEF; x=next(A)){
	 	//y=currentKey(A);
    //  fprintf(out,KEY_FORMAT"\n", y);
   //}	
   freeDictionary(&A);
	//}
	//from here on out gotta code new stuff!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




/*

	append(outlist,0);
	//moveFront(outlist);
	int r=count;

	for(int i=1;i<r;i++){
		moveFront(outlist);
		
		int y=0;
		while (y==0){
			
			if((strcmp(stringsA[i],stringsA[get(outlist)])<=0)){
				insertBefore(outlist,i);
				
				y++;
			}if(get(outlist)==-1){
				append(outlist,i);
				
				y++;
			}
			moveNext(outlist);
	

		}
		//while((strcmp(stringsA[i],stringsA[index(outlist)])<=0)&&y<length(outlist)){
		//	moveNext(outlist);
		//	y++;
		//}
		//insertAfter(outlist,i);

		//printf("%s\n",stringsA[i] );

		//int p=0;
		//while(p==0){
		//for(int q=0; q<length(outlist);q++){
		//	if((strcmp(stringsA[i],stringsA[get(outlist)])<=0)){
		//		insertBefore(outlist,i);
		//		p=1;
		//	}else if(stringsA[i+1]==NULL){
		//		prepend(outlist,i);
		//		p=1;
		//	}else{
		//		moveNext(outlist);
		//	}

		//}
	}
	//printList(out,outlist);
	moveFront(outlist);
	for(int i = 0 ; i<length(outlist) ; i++){
		fprintf(out, "%s", stringsA[(get(outlist))]);	//print corresponding string
		moveNext(outlist);				//move cursor to next node
	}

*/
	fclose(in);
	fclose(out);			//close out of files

	return (EXIT_SUCCESS);	
	

}