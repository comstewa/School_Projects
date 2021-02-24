//GraphTest.c



#include <stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){
	List S = newList();
	Graph G = newGraph(9);

	fprintf(stdout, "%d\n", getDiscover(G, 8));

	fprintf(stdout, "%d\n", getFinish(G,8));


	for(int i=1; i<=9; i++) {
		append(S, i);
	}

   addArc(G, 1,3);
   addArc(G, 1,4);
   addArc(G, 2,1);
   addArc(G, 2,4);
   addArc(G, 3,8);
   addArc(G, 3,3);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 6,5);
   addArc(G, 6,6);
   addArc(G, 8,4);
   addArc(G, 8,7);

   printGraph(stdout, G);
	DFS(G,S);
	for(int i=1; i<=8; i++){
	      fprintf(stdout, "%d ",  getParent(G, i));
	   }
	fprintf(stdout, "\n");


	Graph T = transpose(G);
	Graph C = copyGraph(G);
	fprintf(stdout, "\n");

	printGraph(stdout, T);
	fprintf(stdout, "\n");

	printGraph(stdout, C);

}