
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"Dictionary.h"


int main(int argc, char* argv[]){
	Dictionary S = newDictionary(0);


	int n=10;
   Dictionary A = newDictionary(0);
   char* word[] = { "yeet","nah","three","coolkids","five","seven","okay","ooooof","lol","test" };
   VAL_TYPE x;
   VAL_TYPE y;
   for(int i=0; i<n; i++){
      insert(A, word[i], NULL);
   }
   insert(A,"hahahj", NULL);
   insert(A,"neet", NULL);

  // printDictionary(A);
  // x= lookUp("nah");

   //fprintf(stderr,""KEY_FORMAT"\n",x );
   delete(A, "nah");

	
	
}