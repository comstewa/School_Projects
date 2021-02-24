//Connor Stewart
//Comstewa
//CSE 101
//graph.c implements the graph header
//

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

typedef struct GraphObj{
	List* L;			
	int* color;//0 white,1 grey, 2 black, basic  123 				
	int* parent;				
	int* Dist;				
	int Order;					
	int size;					
	int source;
	int* Discover; 
	int* Finish;		
}GraphObj;

Graph newGraph(int n){	
	Graph G = malloc(sizeof(GraphObj));		
	G->L = calloc(n+1, sizeof(List));	
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->Dist = calloc(n+1, sizeof(int));
	G->Discover = calloc(n+1, sizeof(int));
	G->Finish = calloc(n+1, sizeof(int));

	for(int i = 0 ; i < (n+1) ; i++){
		G->L[i] = newList();
		G->color[i] = 0;
		G->Dist[i] = INF;
		G->parent[i] = NIL;
		G->Discover[i]=UNDEF;
		G->Finish[i]= UNDEF;
	}

	G->Order = n;
	G->size = 0;
	G->source = 0;
	

	return G;
}

void freeGraph(Graph* pG){
	Graph del = *pG;
	for(int i = 0 ; i < getOrder(*pG) + 1 ; i++){
		freeList(&(del->L[i]));
	}
	free(del->L);
	free(del->color);
	free(del->parent);
	free(del->Dist);
	free(del->Discover);
	free(del->Finish);
	free(*pG);
	*pG = NULL;
}
int getDiscover(Graph G, int u){
	if(u < 1 || u > getOrder(G)){			//check u is valid int
		return UNDEF;
	}
	return(G->Discover[u]);
} /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
	if(u < 1 || u > getOrder(G)){			//check u is valid int
		return UNDEF;
	}
	return(G->Finish[u]);
} /* Pre: 1<=u<=n=getOrder(G) */
int getOrder(Graph G){
	return (G->Order);		
}
int getSize(Graph G){
	return(G->size);		
}
int getSource(Graph G){
	if(G->source == 0){
		return NIL;
	}else{
		return(G->source);
	}
}
int getParent(Graph G, int u){

	 if(u < 1 || u > getOrder(G)){			
		return NIL;
	}
	return(G->parent[u]);
}
int getDist(Graph G, int u){
	if(u < 1 || u > getOrder(G)){			//check u is valid int
		return NIL;
	}
	if(G->source == 0){						//if BFS not run yet
		return NIL;
	}
	return(G->Dist[u]);
}
void getPath(List L, Graph G, int u){

	if(u < 1 || u > getOrder(G)){			
		append(L, NIL);
		return;
	}
	else if(getSource(G) == NIL){
		append(L, NIL);
		return;
	}
	else if(getSource(G) == u){
		append(L, u);
		return;
	}
	else if(getParent(G, u) == NIL){
		append(L, NIL);
		return;
	}
	else{
		getPath(L, G, getParent(G, u));
		append(L, u);
		return;
	}
}
void makeNull(Graph G){	
	for(int i = 0 ; i < getOrder(G); i++){
		clear(G->L[i-1]);
	}
	G->size = 0;
}
void addEdge(Graph G, int u, int v){
	if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)){
		return;
	}
	(G->size)++;	
	moveFront(G->L[u]);
	moveFront(G->L[v]);
	int p=0;
	int ugh=0;
	while(p<length(G->L[u])&&(ugh==0)){
	//	printf("breaking here?");
		if(get(G->L[u]) > v){
			insertBefore(G->L[u], v);
			ugh=1;
		}
		if(get(G->L[u]) == back(G->L[u])){
			append(G->L[u], v);
			ugh=1;
		}
		moveNext(G->L[u]);
		p++;
	}
	if(length(G->L[u]) == 0){
		prepend(G->L[u], v);	
	}
	int q=0;
	ugh=0;
	while(q<length(G->L[v])&&(ugh==0)){
		if(get(G->L[v]) > u){
			insertBefore(G->L[v], u);
			ugh=1;
		}
		if(get(G->L[v]) == back(G->L[v])){
			append(G->L[v], u);
			ugh =1;
		}
		moveNext(G->L[v]);
		q++;
	}

	if(length(G->L[v]) == 0){
		prepend(G->L[v], u);
	}

}

void addArc(Graph G, int u, int v){
	if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)){
		return;
	}

	(G->size)++;						
	if(length(G->L[u]) == 0){
		prepend(G->L[u], v);
		return;	
	}
	moveFront(G->L[u]);

	int p=0;

	while(p<length(G->L[u])){// for loop would be better here
	//	printf("breaking here?12");
		if(get(G->L[u]) > v){
			insertBefore(G->L[u], v);
			return;
		}
		if(get(G->L[u]) == back(G->L[u])){
			append(G->L[u], v);
			return;
		}
		moveNext(G->L[u]);
		p++;
	}
	if(length(G->L[u]) == 0){
		prepend(G->L[u], v);	
	}
	return;
}
void DFS(Graph G, List S){// still confussed what list S is will have to change code based on wtf it is. i think its a list of indexes in order tho. 

	if(length(S) != getOrder(G)){	//bruv they aint the same my man
		return;
	}
	else if(S == NULL){
		return;
	}
	else if(G == NULL){
		return;
	}
	for(int i = 1 ; i < getOrder(G) + 1 ; i++){// goes through and makes em all undiscovered
		G->color[i] = 0;			
		G->Discover[i] = UNDEF;
		G->Finish[i] = UNDEF;
		G->parent[i] = NIL;
	}
	int time=0;
	//List stack=newList();
	List yeha=copyList(S);
	moveFront(yeha);
	//moveFront(S);
	for(int i=0; i<length(yeha); i++){
		Visit(G,get(yeha),&time,S);
		moveNext(yeha);
	}// free s
	//S=copyList(stack);
	for(int i = 1 ; i < getOrder(G) + 1 ; i++){
		deleteBack(S);
	}
}
void Visit(Graph G,int q ,int* time, List S){
	if(G->color[q]!=0){
		return;
	}
	G->color[q]=1;
	G->Discover[q]=++(*time);
	
	moveFront(G->L[q]);
	
	while(index(G->L[q])>=0){//for(int i=1; i<=length(G->L[q]);i++){
		if(G->color[get(G->L[q])]==0){
		G->parent[get(G->L[q])]=q;}
		Visit(G,get(G->L[q]),time,S);
		moveNext(G->L[q]);
	}

	G->Finish[q]=++(*time);
	
	G->color[q]=2;
//	moveFront(G->L[q]);get(G->L[q])
	prepend(S,q);
	return;
}

Graph transpose(Graph G){
	if(G==NULL){
		return;
	}
	Graph QTPIE=newGraph(getOrder(G));
	for(int i=1; i<=getOrder(QTPIE);i++){
		moveFront(G->L[i]);
		//while(index(G->L[i])>=0){
		for(int p=0; p<length(G->L[i]);p++){
			addArc(QTPIE,get(G->L[i]),i);// first index, secound value
			moveNext(G->L[i]);
	}
	}
	return QTPIE;
}
Graph copyGraph(Graph G){
	if(G==NULL){
		return;
	}

	Graph QTPIE = newGraph(getOrder(G));

	
	for(int i=1;i <= getOrder(G);i++){
		moveFront(G->L[i]);
		while(index(G->L[i]) >= 0){
			addArc(QTPIE, i, get(G->L[i]));
			moveNext(G->L[i]);
		}
		QTPIE->color[i]=G->color[i];
		QTPIE->parent[i]=G->parent[i];
		QTPIE->Dist[i]=G->Dist[i];
		QTPIE->Discover[i]=(G->Discover[i]);
		QTPIE->Finish[i]=(G->Finish[i]);
		
	}
	return QTPIE;
}
void BFS(Graph G, int s){


	for(int i = 1 ; i < getOrder(G) + 1 ; i++){// goes through and makes em all undiscovered
		G->color[i] = 0;			
		G->Dist[i] = INF;
		G->parent[i] = NIL;
	}
	G->source = s;
	G->color[s] = 1;				
	G->Dist[s] = 0;
	G->parent[s] = NIL;
	List queue = newList();
	append(queue, s);// add the first enment to the queue  even though we will immidiatly deque it
	int temp;
	while(length(queue) > 0 ){// while a que exists
		temp = front(queue);// get ready to deque
		deleteFront(queue);// deque
		List TList = G->L[temp];// gives us the node and list of vertex 
		moveFront(TList);
		while(get(TList) != -1){
			int tempv = get(TList);	
			if(G->color[tempv] == 0){//checks if it has already been discovered or nah
				G->color[tempv] = 1;			
				(G->Dist[tempv])++;
				G->parent[tempv] = temp;
				append(queue, tempv);		
			}
			moveNext(TList);			
		}
		G->color[temp] = 2;			
	}
	freeList(&queue);			
}

void printGraph(FILE* out, Graph G){

	if(G == NULL){
		return;
	}
	List  temp;
	for(int i = 1 ; i <= getOrder(G) ; i++){
		fprintf(out, "%d: ", i);
		temp=G->L[i];			
		printList(out, temp);
		fprintf(out, "\n");			
	}
}